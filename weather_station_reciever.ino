#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const char *ssid="######"; //Enter the name of your network
const char *pass="******"; // your network password         


WiFiClient  client;
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long cID = ; //Write the channel ID on ThingSpeak          
const char * ReadAPIKey = ""; //Write the Read API Key 
const int FieldNumber1 = 1;
const int FieldNumber2 = 2;
const int FieldNumber3 = 3;
const int FieldNumber4 = 4;
const int FieldNumber5 = 5;
const int FieldNumber6 = 6;
int statusCode;

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  lcd.init();
  lcd.backlight();
  
}

void loop()
{

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" ....");
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      delay(5000);
    }
    Serial.println("Connected to Wi-Fi Succesfully.");
  }
 

  
  long Temperature = ThingSpeak.readLongField(cID, FieldNumber1, ReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
    Serial.print("Temperature: ");
    Temperature=Temperature;
    Serial.println(Temperature);
    lcd.setCursor(0,0);
    lcd.print("Temperature: ");
    lcd.setCursor(0,1);

    lcd.print(Temperature);
  }
  else
  {
    Serial.println("Unable to read channel / No internet connection");
    lcd.setCursor(0,1);
    lcd.print("No data read");
  }
  delay(100);
  

  
  long Pressure = ThingSpeak.readLongField(cID, FieldNumber2, ReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
    Serial.print("Pressure:");
    
    Serial.println(Pressure);
    lcd.setCursor(0,0);
    lcd.print("Pressure:         ");
    lcd.setCursor(0,1);
    lcd.print(Pressure);
     
  }
  else
  {
    Serial.println("Unable to read channel / No internet connection");
    lcd.setCursor(0,1);
    lcd.print("No data read");
  }
  delay(100);


  long Altitude = ThingSpeak.readLongField(cID, FieldNumber3, ReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
    Serial.print("Altitude:");
    Altitude=Altitude;
    Serial.println(Altitude);
    lcd.setCursor(0,0);
    lcd.print("Altitude:         ");
    lcd.setCursor(0,1);
    lcd.print(Altitude);
    
  }
  else
  {
    Serial.println("Unable to read channel / No internet connection");
    lcd.setCursor(0,1);
    lcd.print("No data read");  
  }
  delay(100);


  long CO2 = ThingSpeak.readLongField(cID, FieldNumber4, ReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
    Serial.print("CO2 Level:        ");
    CO2=CO2-9649;
    Serial.println(CO2);
    lcd.setCursor(0,0);
    lcd.print("CO2 Levels: ");
    lcd.setCursor(0,1);
    lcd.print(CO2);  
    
  }
  else
  {
    Serial.println("Unable to read channel / No internet connection");
    lcd.setCursor(0,1);
    lcd.print("No data read");  
  }
  delay(100);

  long CO = ThingSpeak.readLongField(cID, FieldNumber5, ReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
    Serial.print("CO Levels:         ");
    CO=CO-9949;
    Serial.println(CO);
    lcd.setCursor(0,0);
    lcd.print("CO Levels: ");
    lcd.setCursor(0,1);
    lcd.print(CO); 
   
  }
  else
  {
    Serial.println("Unable to read channel / No internet connection");
    lcd.setCursor(0,1);
    lcd.print("No data read");  
  }
  delay(100);


  long NH4 = ThingSpeak.readLongField(cID, FieldNumber6, ReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
    Serial.print("NH4 Levels:        ");
   
    Serial.println(NH4);
    lcd.setCursor(0,0);
    lcd.print("NH4 Levels: ");
    lcd.setCursor(0,1);
    lcd.print(NH4);  
    
  }
  else
  {
    Serial.println("Unable to read channel / No internet connection");
    lcd.setCursor(0,1);
    lcd.print("No data read");  
  }
  delay(100);
  Serial.println("************************************************");
  }
