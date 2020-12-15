
#include <stdio.h>
#include <IRremote.h>  // 적외선 송수신을 하기 위해서 IRremote 라이브러리를 사용한다.
IRsend irsend;

#define BT (!digitalRead(11))

int BT_pin = 11;
int D_pin1 = 5;              // 딥스위치 1번 22도설정
int D_pin2 = 6;              // 딥스위치 2번 24도설정
int D_pin3 = 7;              // 딥스위치 3번 26도설정
int D_pin4 = 8;              // 딥스위치 4번 28도설정
int ledPin = 13;              // 통신확인 LED
int Relaypin3 = 9;            // FAN 릴레이
int Relaypin4 = 10;           // COMP 릴레이

void setup(){
pinMode(ledPin, OUTPUT);       // 디지털 핀을 출력으로
pinMode(Relaypin3,OUTPUT);     // 릴레이 제어 3번핀을 출력으로 설정
pinMode(Relaypin4,OUTPUT);     // 릴레이 제어 4번핀을 출력으로 설정
digitalWrite (Relaypin3, LOW); // FAN  릴레이 OFF
digitalWrite (Relaypin4, LOW); // COMP 릴레이 OFF
pinMode(BT_pin, INPUT_PULLUP); //내부 풀업저항을 사용한 버튼 연결, 눌렀을 때 0
pinMode(D_pin1, INPUT_PULLUP); //내부 풀업저항을 사용한 버튼 연결, 눌렀을 때 0
pinMode(D_pin2, INPUT_PULLUP); //내부 풀업저항을 사용한 버튼 연결, 눌렀을 때 0
pinMode(D_pin3, INPUT_PULLUP); //내부 풀업저항을 사용한 버튼 연결, 눌렀을 때 0
pinMode(D_pin4, INPUT_PULLUP); //내부 풀업저항을 사용한 버튼 연결, 눌렀을 때 0
Serial.begin(9600);
}

unsigned char data[23];
unsigned int OnDataD22[83] = {8350,4100, 550,1500, 550,1550, 550,500, 500,1550, 550,500, 550,500, 500,500, 550,500, 550,500, 500,1550, 550,500, 550,1550, 500,1550, 500,550, 500,550, 500,500, 550,500, 550,500, 500,550, 500,1550, 550,500, 500,1550, 550,1550, 500,500, 500,1600, 550,500, 500,500, 550,500, 550,500, 550,450, 500,550, 550,500, 550,1500, 550,500, 550,1500, 500,1600, 550,1500, 550,1550, 550,1500, 550,500, 550};  // NEC D0581680
unsigned int OnDataC24[83] = {8350,4100, 550,1550, 500,1550, 600,450, 500,550, 500,500, 550,500, 550,500, 500,550, 500,500, 600,1500, 550,500, 500,1550, 550,1550, 500,500, 550,500, 550,500, 550,500, 500,500, 550,500, 550,1500, 500,1600, 550,500, 500,500, 550,500, 550,1500, 500,550, 550,500, 550,500, 550,450, 550,500, 550,500, 550,450, 500,1600, 550,500, 550,1500, 550,1500, 500,550, 550,500, 550,500, 550,450, 600};  // NEC C0581880
unsigned int OnDataD25[83] = {8300,4100, 550,1550, 500,1550, 550,500, 500,550, 500,500, 550,500, 550,500, 500,550, 500,500, 550,1550, 500,500, 550,1550, 500,1550, 550,500, 500,550, 500,500, 550,500, 550,500, 500,550, 500,1550, 500,1550, 550,500, 550,500, 550,1500, 550,1550, 500,550, 500,500, 550,500, 550,500, 500,500, 550,500, 500,550, 500,1550, 550,500, 550,1500, 550,1550, 500,550, 550,450, 550,500, 500,1550, 550};  // NEC C0581980
unsigned int OnDataC26[83] = {8300,4150, 500,1550, 500,1600, 500,500, 550,500, 500,550, 500,550, 500,500, 550,500, 500,550, 500,1550, 500,550, 500,1550, 550,1550, 500,550, 500,500, 550,500, 500,550, 500,500, 550,500, 500,1550, 550,1550, 500,550, 500,1550, 500,550, 550,1500, 500,550, 550,500, 500,500, 550,500, 500,550, 500,550, 500,500, 550,1550, 500,550, 500,1550, 500,1550, 550,500, 500,550, 500,1550, 550,500, 500};  // NEC C0581A80
unsigned int OnDataD28[83] = {8300,4150, 550,1500, 550,1550, 550,450, 550,1550, 550,500, 500,500, 550,500, 550,500, 550,450, 550,1550, 550,500, 550,1500, 550,1500, 550,500, 550,500, 550,500, 550,450, 550,500, 550,500, 550,1500, 550,1550, 550,1500, 550,500, 550,500, 500,1550, 550,500, 500,550, 500,500, 550,500, 550,500, 500,550, 500,500, 550,1550, 500,1550, 550,500, 500,550, 500,550, 500,1550, 550,500, 500,550, 500};  // NEC D0581C80
unsigned int OffData[83] = {8300,4150, 550,1500, 550,1500, 550,1550, 550,500, 550,450, 550,500, 550,500, 550,500, 550,450, 550,1550, 550,450, 550,1550, 550,1500, 550,500, 550,500, 550,500, 500,500, 550,500, 550,500, 500,1550, 550,500, 550,1550, 500,1550, 500,550, 500,550, 500,500, 550,500, 550,500, 500,550, 500,500, 550,500, 550,500, 500,550, 500,1550, 550,500, 500,500, 550,1550, 550,1500, 550,1550, 550,450, 550};  // NEC E0581600
unsigned char rxIdx = 0, rxFlg=0, comp = 0, fan = 0, led = 0, sw = 0, dsw = 0, r = 0, dp = 0;
unsigned char tempFlg = 0, swFlg = 0;

void loop(){
  int khz = 38;

  if(BT && !tempFlg){
    tempFlg = 1;  
    swFlg = !swFlg;
  }
  else if(!BT && tempFlg){
    tempFlg = 0;
  }

  if(digitalRead(D_pin1) == LOW){
      dp = 1;
   }else if(digitalRead(D_pin2) == LOW){
      dp = 2;
   }else if(digitalRead(D_pin3) == LOW){
      dp = 3;
   }else if(digitalRead(D_pin4) == LOW){
      dp = 4;
   }else{
      dp = 0;
   }

 //Serial.println(tw);
    
 if(swFlg == 1){
  if(dp == 0){
      if(dsw == 0){
           for (int i = 0; i < 3; i++)
          {
            irsend.sendRaw(OnDataD25, sizeof(OnDataD25) / sizeof(OnDataD25[0]), khz);   //25도 ON
            delay(40);
          }
          dsw = 1;
      }else if(dsw == 1){
           for (int i = 0; i < 3; i++)
          {
            irsend.sendRaw(OffData, sizeof(OffData) / sizeof(OffData[0]), khz);   // OFF
            delay(40);
          }   
        dsw = 0;
      }
      swFlg = 0;
    }
    else if(dp == 1){
      if(dsw == 0){
           for (int i = 0; i < 3; i++)
          {
             irsend.sendRaw(OnDataD22, sizeof(OnDataD22) / sizeof(OnDataD22[0]), khz);   //22도 ON
            delay(40);
          }
          dsw = 1;
      }else if(dsw == 1){
           for (int i = 0; i < 3; i++)
          {
            irsend.sendRaw(OffData, sizeof(OffData) / sizeof(OffData[0]), khz);   // OFF
            delay(40);
          }   
        dsw = 0;
      }
      swFlg = 0;
    }
    else if(dp == 2){
      if(dsw == 0){
           for (int i = 0; i < 3; i++)
          {
            irsend.sendRaw(OnDataC24, sizeof(OnDataC24) / sizeof(OnDataC24[0]), khz);   //24도 ON
            delay(40);
          }
        dsw = 1;
      }else if(dsw == 1){
           for (int i = 0; i < 3; i++)
          {
           irsend.sendRaw(OffData, sizeof(OffData) / sizeof(OffData[0]), khz);   // OFF
            delay(40);
          }   
        dsw = 0;
      }
      swFlg = 0;
    }else if(dp == 3){
      if(dsw == 0){
           for (int i = 0; i < 3; i++)
          {
            irsend.sendRaw(OnDataC26, sizeof(OnDataC26) / sizeof(OnDataC26[0]), khz);   //26도 ON
            delay(40);
          }
        dsw = 1;
      }else if(dsw == 1){
           for (int i = 0; i < 3; i++)
          {
            irsend.sendRaw(OffData, sizeof(OffData) / sizeof(OffData[0]), khz);   // OFF
            delay(40);
          }   
        dsw = 0;
      }
      swFlg = 0;
    }else if(dp == 4){
      if(dsw == 0){
           for (int i = 0; i < 3; i++)
          {
            irsend.sendRaw(OnDataD28, sizeof(OnDataD28) / sizeof(OnDataD28[0]), khz);   //28도 ON
            delay(40);
          }
        dsw = 1;
      }else if(dsw == 1){
           for (int i = 0; i < 3; i++)
          {
            irsend.sendRaw(OffData, sizeof(OffData) / sizeof(OffData[0]), khz);   // OFF
            delay(40);
          }   
        dsw = 0;
      }
      swFlg = 0;
    }
  }

 
  while(Serial.available()){
    led = 1;
    data[rxIdx++] = Serial.read();
    if(rxIdx >= 23) rxFlg = 1;
  }

  if(led == 1){
    digitalWrite(ledPin, HIGH);
    delay(50);
    led = 0;
  }
  else digitalWrite(ledPin, LOW);
  
  if(rxFlg){
/*    if(data[2] == 38 && data[5] >= 1){ // fan 상태 변경
      fan = 1;
      }else if(data[2] == 38 && data[5] == 0){
        fan = 0;
        }
*/
    if(data[2] == 22 && data[15] >= 1){ // fan 상태 변경
      fan = 1;
      }else if(data[2] == 22 && data[15] == 0){
        fan = 0;
        }


        
    if(data[2] == 22 && data[14] >= 1){ // comp 상태 변경
      comp = 1;
      }else if(data[2] == 22 && data[14] == 0){
        comp = 0;
        }
    rxIdx = 0;
    rxFlg = 0;
  }  
  if(fan == 1){
    digitalWrite (Relaypin3, HIGH); // 3번 릴레이 ON
   }else{
    digitalWrite (Relaypin3, LOW); // 3번 릴레이 OFF
   }
  if(comp == 1){
    digitalWrite (Relaypin4, HIGH); // 4번 릴레이 ON
    }else{
      digitalWrite (Relaypin4, LOW); // 4번릴레이 OFF
    }
    
  //Serial.print(fan); // fan 상태 출력
  //Serial.print(comp); // comp 상태 출력
  
  /*
    if(rxFlg){  // 상태 출력
    for(int i=0; i<23; i++){
      sprintf(str,"%02X ", data[i]);    
      Serial.print(str);
    }
    Serial.println(' ');
    rxIdx = 0;
    rxFlg = 0;
  }
  */
 
}
