#include <Wire.h>
#include <CD74HC4067.h>
#include <Keyboard.h>


CD74HC4067 my_mux(A0,15,14,16);

const int g_common_pin = 10;
int stage = 1;
int oldStage = 1;
int temp = 0;
int buttonSpace = 300;

unsigned long previousMillis = 0;


void setup(){
  delay(5000);
  Keyboard.begin();
  uint8_t error = 0;
  pinMode(g_common_pin, INPUT_PULLUP);
  pinMode(2,INPUT_PULLUP);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  Serial.begin(9600);
  blinkAll();
  delay(200);
  blinkAll();
}

void loop(){
  for (int i = 0; i < 9; i++) {
        my_mux.channel(i);
        Serial.print(digitalRead(g_common_pin)); //this outputs all button readings
        Serial.print(",");
        if (digitalRead(g_common_pin)==0){
          if (stage==1){
            Keyboard.press(KEY_LEFT_SHIFT);
          }if (stage==2){
            Keyboard.press(KEY_LEFT_ALT);
          }if (stage==3){
            Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press(KEY_LEFT_ALT);
          }
          if (i==0){                // There's definitly a way better way to do this
            Keyboard.press(KEY_F16);
            delay(buttonSpace);
            break;
          }if (i==1){
            Keyboard.press(KEY_F17);
            delay(buttonSpace);
            break;
          }if (i==2){
            Keyboard.press(KEY_F18);
            delay(buttonSpace);
            break;
          }if (i==3){
            Keyboard.press(KEY_F19);
            delay(buttonSpace);
            break;
          }if (i==4){
            Keyboard.press(KEY_F20);
            delay(buttonSpace);
            break;
          }if (i==5){
            Keyboard.press(KEY_F21);
            delay(buttonSpace);
            break;
          }if (i==6){
            Keyboard.press(KEY_F22);
            delay(buttonSpace);
            break;
          }if (i==7){
            Keyboard.press(KEY_F23);
            delay(buttonSpace);
            break;
          }if (i==8){
            Keyboard.press(KEY_F24);
            delay(buttonSpace);
            break;
          } 
        }
        Keyboard.releaseAll();
  }
  Serial.print(digitalRead(2));
  if (digitalRead(2)==0){
    if (millis() - previousMillis >= 3000){
     lightSwap();
    }else{
      if (stage < 3){
      stage=stage+1;
      }else{
      stage=1;
      }
    }
    
  }
  if (oldStage != stage){
    lightSwap();
  }
  if (millis() - previousMillis >= 3000){
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
  }
  Serial.println(stage);
}


void lightSwap(){
  if (stage==1){
      digitalWrite(6,HIGH);
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      delay(250);
    }if (stage==2){
      digitalWrite(6,LOW);
      digitalWrite(7,HIGH);
      digitalWrite(8,LOW);
      delay(250);
    }if (stage==3){
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(8,HIGH);
      delay(250);
    }
    oldStage = stage;
    previousMillis = millis();
}

void blinkAll(){
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  delay(200);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
}
