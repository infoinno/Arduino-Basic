#define BLYNK_PRINT Serial
#define DHTTYPE DHT11
#define DHTPIN 11
 
// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600
 
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
#include "DHT.h"
 
SoftwareSerial EspSerial(2, 3); // RX, TX

char auth[] = "B_diwKdyDMx27KX2Yw8AnuYnmcZi1WX-";
char ssid[] = "infoinno";
char pass[] = "yjys6826!";
 
float h;
float t;
 
ESP8266 wifi(&EspSerial);
 
DHT dht(DHTPIN, DHTTYPE);
 
void setup()
{
  Serial.begin(9600);
 
  delay(10);
 
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
 
  Blynk.begin(auth, wifi, ssid, pass);
  dht.begin();
}
 
BLYNK_READ(V1)
{
  Blynk.virtualWrite(V1, h);
}
 
BLYNK_READ(V0)
{
  Blynk.virtualWrite(V0, t);
}
 
void loop()
{
  Blynk.run();
  h = dht.readHumidity();
  t = dht.readTemperature();
 
  Serial.print(h);
  Serial.print(" ");
  Serial.println(t);
}
