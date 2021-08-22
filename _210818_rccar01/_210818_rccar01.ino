/****************************************************************************
RC car source 
by. B.H Chung
write : 2021. 06. 30
******************************************************************************/
#include <SoftwareSerial.h> //시리얼통신 라이브러리 호출

/* BLUETOOTH SETTING */ 
int blueTx=12;   //Tx (보내는핀 설정)
int blueRx=13;   //Rx (받는핀 설정)
SoftwareSerial btSerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언

/* 모터세팅 */
//모터 1 (왼쪽바퀴)
int EnableA = 3; //  ENPin1 
int IN1_A = 9; // In1Pin
int IN2_A = 4; // In2Pin

//모터 2 (오른쪽바퀴)
int EnableB = 5; // ENPin2 
int IN1_B = 10; // IN3Pin
int IN2_B = 6; // IN4Pin

char command;

void setup() {
  Serial.begin(9600);   //시리얼모니터
  btSerial.begin(9600); //블루투스 시리얼
  
  /* DC MOTOR */
  pinMode(EnableA, OUTPUT);
  digitalWrite(EnableA, LOW); // 모터 제어 불가능 상태
  pinMode(IN1_A, OUTPUT); //In1Pin
  pinMode(IN2_A, OUTPUT); //In2Pin
  pinMode(EnableB, OUTPUT);
  digitalWrite(EnableB, LOW); // 모터 제어 불가능 상태
  pinMode(IN1_B, OUTPUT); //IN3Pin
  pinMode(IN2_B, OUTPUT); //IN4Pin
}

void loop() {
  if (btSerial.available()) {   
    command= btSerial.read();   
    Serial.write(command);  //블루투스측 내용을 시리얼모니터에 출력
    switch(command){
      case '0': // 직진
        forward();
      break;
      case '1': // 후진
        backward();
      break;
      case '2': //좌회전
        turnleft();
      break;
      case '3'://우회전
        turnright();
      break;
      case '4':
        stop();
      break;
    }    
  }
  if (Serial.available()) {         
    command=Serial.read();
    switch(command){
      case '0': // 직진
        forward();
        Serial.write("0");
      break;
      case '1': // 후진
        backward();
        Serial.write("1");
      break;
      case '2': //좌회전
        turnleft();
        Serial.write("2");
      break;
      case '3'://우회전
        turnright();
        Serial.write("3");
      break;
      case '4':
        stop();
        Serial.write("4");
      break;
    }
  }
}

// 직진
void forward(){
  stop();
  delay(10);
  digitalWrite(EnableA, HIGH); // 모터 제어 가능 상태
  digitalWrite(IN2_A, LOW); // 정방향 회전은 HIGH이나 바퀴가 모터와 반대로 조립되어 반대로 수정
  digitalWrite(IN1_A, HIGH); // 최고 속도가 LOW 이나 바퀴가 모터와 반대로 조립되어 반대로 수정
  digitalWrite(EnableB, HIGH); // 모터 제어 가능 상태
  digitalWrite(IN2_B, LOW); // 정방향 회전 HIGH이나 바퀴가 모터와 반대로 조립되어 반대로 수정
  digitalWrite(IN1_B, HIGH); // 최고 속도LOW 이나 바퀴가 모터와 반대로 조립되어 반대로 수정   
  delay(500);
  stop();
}

//멈춤
void stop(){
//   digitalWrite(IN1_A, HIGH); // 속도 0는 LOW이나 모터와 바퀴가 반대로 조립되어 수정됨
//   digitalWrite(IN1_B, HIGH); // 속도 0는 LOW이나 모터와 바퀴가 반대로 조립되어 수정됨
   digitalWrite(EnableA, LOW); // 모터 제어 불가능 상태
   digitalWrite(EnableB, LOW); // 모터 제어 불가능 상태
}

//후진
void backward(){
  stop();  
  delay(10);
  digitalWrite(EnableB, HIGH); // 모터 제어 가능 상태
  digitalWrite(IN2_B, HIGH); // 정방향 회전 HIGH이나 바퀴가 모터와 반대로 조립되어 반대로 수정
  digitalWrite(IN1_B, LOW); // 최고 속도LOW 이나 바퀴가 모터와 반대로 조립되어 반대로 수정 
  digitalWrite(EnableA, HIGH); // 모터 제어 가능 상태
  digitalWrite(IN2_A, HIGH); // 정방향 회전은 HIGH이나 바퀴가 모터와 반대로 조립되어 반대로 수정
  digitalWrite(IN1_A, LOW); // 최고 속도가 LOW 이나 바퀴가 모터와 반대로 조립되어 반대로 수정     
  delay(500);
  stop();
}

//좌회전
void turnleft(){
  stop();  
  delay(10);
  digitalWrite(EnableA, HIGH); // 모터 제어 가능 상태
  digitalWrite(IN2_A, HIGH); // 정방향 회전은 HIGH이나 바퀴가 모터와 반대로 조립되어 반대로 수정
  digitalWrite(IN1_A, LOW); // 최고 속도가 LOW 이나 바퀴가 모터와 반대로 조립되어 반대로 수정
  digitalWrite(EnableB, HIGH); // 모터 제어 가능 상태
  digitalWrite(IN2_B, LOW); // 정방향 회전은 HIGH이나 바퀴가 모터와 반대로 조립되어 반대로 수정
  digitalWrite(IN1_B, HIGH); // 최고 속도가 LOW 이나 바퀴가 모터와 반대로 조립되어 반대로 수정
  delay(100);
  stop();
}

//우회전
void turnright(){
  stop();
  delay(10);
  digitalWrite(EnableA, HIGH); // 모터 제어 가능 상태
  digitalWrite(IN2_A, LOW); // 정방향 회전 HIGH이나 바퀴가 모터와 반대로 조립되어 반대로 수정
  digitalWrite(IN1_A, HIGH); // 최고 속도LOW 이나 바퀴가 모터와 반대로 조립되어 반대로 수정
  digitalWrite(EnableB, HIGH); // 모터 제어 가능 상태
  digitalWrite(IN2_B, HIGH); // 정방향 회전은 HIGH이나 바퀴가 모터와 반대로 조립되어 반대로 수정
  digitalWrite(IN1_B, LOW); // 최고 속도가 LOW 이나 바퀴가 모터와 반대로 조립되어 반대로 수정
  delay(100);
  stop();
}
