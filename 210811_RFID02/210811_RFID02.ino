#include <Servo.h>

//#include <deprecated.h>
#include <SPI.h>
#include <MFRC522.h>
//#include <MFRC522Extended.h>
//#include <require_cpp11.h>

int SERVO_PIN = 6;
Servo myservo;

int RST_PIN = 9;
int SS_PIN = 10;
MFRC522 mfrc(SS_PIN, RST_PIN);

//int PICC0 = 7;
//int PICC1 = 51;
//int PICC2 = 148;
//int PICC3 = 200;

int PICC0 = 0x7;
int PICC1 = 0x33;
int PICC2 = 0x94;
int PICC3 = 0xc8;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc.PCD_Init();

  myservo.attach(SERVO_PIN);
  myservo.write(0);
}

void loop() {
  if(!mfrc.PICC_IsNewCardPresent() || !mfrc.PICC_ReadCardSerial()){
    delay(500);
    return;
  }

  Serial.print("Old: ");
  Serial.print(PICC0, HEX);
  Serial.print(PICC1, HEX);
  Serial.print(PICC2, HEX);
  Serial.println(PICC3, HEX);
  
  Serial.print("New: ");
  Serial.print(mfrc.uid.uidByte[0], HEX);
  Serial.print(mfrc.uid.uidByte[1], HEX);
  Serial.print(mfrc.uid.uidByte[2], HEX);
  Serial.println(mfrc.uid.uidByte[3], HEX);
  
  //ID가 등록된 ID와 동일하다면
  if (mfrc.uid.uidByte[0] == PICC0 && 
      mfrc.uid.uidByte[1] == PICC1 && 
      mfrc.uid.uidByte[2] == PICC2 && 
      mfrc.uid.uidByte[3] == PICC3 ) 
  {

   
    Serial.println(F("승인된 카드입니다."));   
    Serial.println(F("모터 작동!!"));   

    //서보 90도로 이동
    myservo.write(90);
    //1초 대기
    delay(1000);
    //서보 0도로 되돌림
    myservo.write(0);
  }
  else{
    //등록된 카드가 아니라면 시리얼 모니터로 ID 표시
    Serial.println(F("This is an unconfirmed Card."));
//    Serial.print(F("In hex: "));
//    printHex(mfrc.uid.uidByte, mfrc.uid.size);    
  }
  
  //종료
  mfrc.PICC_HaltA();
  mfrc.PCD_StopCrypto1();

  //다시 시작!
}
