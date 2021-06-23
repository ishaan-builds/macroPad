#include <HID-Project.h>                    //include HID_Project library
#include <HID-Settings.h>

#define REVERSED true                      //if your controller is reversed change it to true

int val = 0;
int previousval = 0;
int val2 = 0;

int potValComp;
int potPin = A3;
int potVal;
int rawPotVal;
int oldpotVal = -1;

void setup() {
  delay(5000);                              //wait for computer to connect
  Serial.begin(9600);
  Consumer.begin();                         //initialize computer connection
  for(int a = 0; a < 52; a++) {
    Consumer.write(MEDIA_VOLUME_DOWN);      //set the volume to 0
    delay(2);
  }
}

void loop() {
  vol();
  
  val = potValComp;                      //read potentiometer value
  val = map(val, 0, 1023, 0,100);          //map it to 102 steps
//  val = map(val, 0, 37, 0,31);
//  val = map(val, 38, 985, 32,71);
//  val = map(val, 986, 1023, 72,100);
  
  if(REVERSED) {
    val = 100 - val;
  }
  if(abs(val - previousval) > 2) {          //check if potentiometer value has changed
    previousval = val;
    val /= 2;                               //divide it by 2 to get 51 steps
    while(val2 < val) {
      Consumer.write(MEDIA_VOLUME_UP);      //turn volume up to appropiate level
      val2++;
      delay(2);
    }
    while(val2 > val) {
      Consumer.write(MEDIA_VOLUME_DOWN);    //turn volume down to appropiate level
      val2--;
      delay(2);
    }
  }
  delay(100);                               //wait at least 300ms between changing volume levels
  Serial.print(rawPotVal);   //I just wrot these serial.prints so that I could see the progressive filtering of the potentometr value that would then be used to change the volume
  Serial.print(" , ");
  Serial.print(potVal);
  Serial.print(" , ");
  Serial.print(potValComp);
  Serial.print(" , ");
  Serial.println(val);
}                                          


void vol()    //This bunch of code is for claning out the signal given from the potentiometer
{
  rawPotVal = analogRead(potPin); //This makes it so that the final value dosent change when only a minute change in made to the potentiometer, this reduces moments of rapid fluctuation of the volume
  
  if (rawPotVal - potVal <-3 || rawPotVal - potVal >3){
     potVal = rawPotVal;
  }
  
  if (potVal <= 44)
  {
    potValComp = map(potVal, 0, 44, 0, 255); // bottom 25% of pot remapped to 0 to 25% of 1023
  }
  if (potVal > 44 && potVal < 975)
  {
    potValComp = map(potVal, 45, 974, 255, 767); // 50% middle of pot remapped to 25% to 75%% of 1023
  }
  if (potVal >= 975 )
  {
    potValComp = map(potVal, 975, 1023, 767, 1023); // top 25% of pot remapped to 75% to 100%% of 1023
  }
  if (potVal != oldpotVal) // check and print if potVal has changed
  {
    oldpotVal = potVal;
  }
}
