/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define DHTTYPE DHT11
#define DHTPIN 13

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

#include <DHT.h> 
DHT dht(DHTPIN, DHTTYPE);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "9qzjfs3A6Lt3KgxLV7TFVwAKH9HQUdim";  // 이메일로 받은 auth code 입력

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "infoinno";  // 와파 이름
char pass[] = "yjys6826!"; //와파 비번
 
float h;
float t;

void setup()
{
  // Debug console
  Serial.begin(115200);
  dht.begin();

  Blynk.begin(auth, ssid, pass);
}

void sendValue(){ 
//  float h = dht.readHumidity(); 
  int h = dht.readHumidity(); 
//  float t = dht.readTemperature(); 
  int t = dht.readTemperature(); 
  if ( isnan(h) || isnan(t) ) { 
    Serial.println("Failed to load DHT Sensor Data"); 
    delay(1000); 
    return; 
  }
    Blynk.virtualWrite(V2, t);  //폰에서 세팅 V0 으로 바꿔줘야함
    Blynk.virtualWrite(V3, h);  //폰에서 세팅 V1
}

void loop()
{
  Blynk.run();
  sendValue();
}
