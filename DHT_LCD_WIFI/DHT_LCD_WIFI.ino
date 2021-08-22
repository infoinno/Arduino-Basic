#include <LiquidCrystal_I2C.h>

#include <DHT.h>
#define pinDHT 12
#define DHTTYPE DHT11
DHT dht(pinDHT, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,16,2);

#include <SoftwareSerial.h> 
#define rxPin 3 
#define txPin 2 
SoftwareSerial esp01(txPin, rxPin); // SoftwareSerial NAME(TX, RX);



int count = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  esp01.begin(9600);  //와이파이 시리얼


  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("210817_DHT_LCD2");
  lcd.setCursor(0,1);
  lcd.print("by B.H Chung");
  delay(2000);
  lcd.clear();
}

void loop() {
  // DHT
  delay(2000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" C   ");
  Serial.println(count);

  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("Humi: ");
  lcd.print(h);
  lcd.print(" %");
  lcd.setCursor(12,1);
  lcd.print(count);

  count += 1;
  if(count > 9999){
    count = 0;
    lcd.clear();
  }

  if (esp01.available()) {       
    Serial.write(esp01.read());  
  }  
  if (Serial.available()) {         
    esp01.write(Serial.read()); 

  
}
