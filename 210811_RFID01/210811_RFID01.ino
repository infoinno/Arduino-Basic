//#include <deprecated.h>
#include <SPI.h>
#include <MFRC522.h>
//#include <MFRC522Extended.h>
//#include <require_cpp11.h>

int RST_PIN = 9;
int SS_PIN = 10;

MFRC522 mfrc(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc.PCD_Init();
}

void loop() {
  if(!mfrc.PICC_IsNewCardPresent() || !mfrc.PICC_ReadCardSerial()){
    delay(500);
    return;
  }
  
//  Serial.print(F("PICC type: "));
//  //PICC 타입 읽어오기
//  MFRC522::PICC_Type piccType = mfrc.PICC_GetType(mfrc.uid.sak);
//  Serial.println(mfrc.PICC_GetTypeName(piccType));
//  //MIFARE 방식이 아니라면 더이상 진행하지 말고 빠져나감
//  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
//    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
//    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
//    Serial.println(F("Your tag is not of type MIFARE Classic."));
//    return;
//  }

  Serial.print("Card UID: ");

  for(byte i=0; i<4; i++){
    Serial.print(mfrc.uid.uidByte[i]);
    Serial.print(" ");
  }
  Serial.println();
}
