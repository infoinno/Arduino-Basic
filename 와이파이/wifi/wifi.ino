#include <SoftwareSerial.h> 
#define rxPin 3 
#define txPin 2 
SoftwareSerial esp01(txPin, rxPin); // SoftwareSerial NAME(TX, RX);

void setup() {
  Serial.begin(9600);   //시리얼모니터
  esp01.begin(9600);  //와이파이 시리얼
}

void loop() {
  if (esp01.available()) {       
    Serial.write(esp01.read());  //블루투스측 내용을 시리얼모니터에 출력
  }  
  if (Serial.available()) {         
    esp01.write(Serial.read());  //시리얼 모니터 내용을 블루추스 측에 쓰기
  }
}
