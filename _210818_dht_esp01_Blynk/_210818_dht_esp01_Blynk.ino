#define BLYNK_PRINT Serial
#define DHTTYPE DHT11
#define DHTPIN 11

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
#include <DHT.h>

#define ESP8266_BAUD 9600
 
DHT dht(DHTPIN, DHTTYPE);
 
SoftwareSerial EspSerial(2, 3); // RX, TX
 
char auth[] = "8up7lG-e2xwo6usYDkR7SM082G9YVRFr";
char ssid[] = "infoinno";
char pass[] = "yjys6826!";
 
float h;
float t;
 
ESP8266 wifi(&EspSerial);
 
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
  delay(2000);
  Blynk.run();
  h = dht.readHumidity();
  t = dht.readTemperature();
 
  Serial.print(h);
  Serial.print(" ");
  Serial.println(t);
}
