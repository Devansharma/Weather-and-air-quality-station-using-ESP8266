#include <BMP280_DEV.h>                           
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <MQUnifiedsensor.h>

#define pin A0    
#define type 135

const char* server="api.thingspeak.com";
unsigned long cID= 905283;
const char * writeapiKey = "AVXHQM7UPOUC3OS0";

MQUnifiedsensor MQ135(pin, type);
float CO, Alcohol, CO2, Tolueno, NH4, Acetona;
float temperature, pressure, altitude;       
BMP280_DEV bmp280;                           

const char *ssid="Devansh mobile hotspot";
const char *password="123123123"; 

WiFiClient client;

void setup() 
{
  Serial.begin(115200);                      
  delay(10);
  Wire.begin();
 
 
  Serial.print(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("");
  Serial.println("");
  ThingSpeak.begin(client);

  
  bmp280.begin(0x76);                                 // Default initialisation, place the BMP280 into SLEEP_MODE 
  //bmp280.setPresOversampling(OVERSAMPLING_X4);    // Set the pressure oversampling to X4
  //bmp280.setTempOversampling(OVERSAMPLING_X1);    // Set the temperature oversampling to X1
  //bmp280.setIIRFilter(IIR_FILTER_4);              // Set the IIR filter to setting 4
  bmp280.setTimeStandby(TIME_STANDBY_2000MS);     // Set the standby time to 2 seconds
  bmp280.startNormalConversion();                 // Start BMP280 continuous conversion in NORMAL_MODE  
  
  MQ135.inicializar();
}

void loop() 
{
//  WiFiClient client = server.available();
  float Temprature, Pressure, Altitude;
  float Carbonmono, Carbondioxo, ammonium;
  
    if (bmp280.getMeasurements(temperature, pressure, altitude))    
  {
    Serial.print(temperature);                       
    Temprature = temperature+17;
    Pressure = pressure+1000;    
    Altitude = altitude+290;  
    delay(10000);
    
  }
  MQ135.update();
  Carbonmono =  MQ135.readSensor("CO"); 
  Carbondioxo =  MQ135.readSensor("CO2");
  ammonium =  MQ135.readSensor("NH4"); 
  CO=Carbonmono,2;
  CO2=Carbondioxo,2;
  NH4=ammonium,2;
  Serial.println("*****************************************");
  Serial.print("Volt: ");Serial.print(MQ135.getVoltage(false));Serial.println(" V"); 
  Serial.print("R0: ");Serial.print(MQ135.getR0());Serial.println(" Ohm"); 
  Serial.print("CO: ");Serial.print(CO,2);Serial.println(" ppm");
  Serial.print("CO2: ");Serial.print(CO2,2);Serial.println(" ppm");
  Serial.print("NH4: ");Serial.print(NH4,2);Serial.println(" ppm");
  Serial.print("Temprature: ");Serial.print(Temprature);Serial.println(" *C");
  Serial.print("Pressure: ");Serial.print(Pressure);Serial.println(" hPa");
  Serial.print("Altitude: ");Serial.print(Altitude);Serial.println(" m");
  delay(1000);
  Serial.println("*****************************************");
  
  if(isnan(Temprature)|| isnan(Pressure)|| isnan(Altitude)){
    Serial.println("Failed to read data from BMP280 sensor");
    return;
    }
    
  if(isnan(CO)|| isnan(CO2)|| isnan(NH4)){
    Serial.println("Failed to read data from MQ135 sensor");
    return;
    }
  if(client.connect(server,80)){
    ThingSpeak.setField(1,Temprature+17);
    ThingSpeak.setField(2,Pressure+1000);
    ThingSpeak.setField(3,Altitude+290);
    ThingSpeak.setField(4,CO2);
    ThingSpeak.setField(5,CO);
    ThingSpeak.setField(6,NH4);
    ThingSpeak.writeFields(cID,writeapiKey);
    Serial.println("Data sent to cloud");
    }
    client.stop();
    Serial.print("Waiting for other data....");
    delay(10000);

   
}
