/* 
 *  Ex_15 - Of Motion & Sound
 *  Playing simple tone from the on-board Piezo Speaker
 *  & Control the Motor too!
 *  
 *    LEDs 
 *    --  GP12
 *    
 *    SPK
 *    --  GP22
 *    
 *    MotorA
 *    --  GP8,9
 *    
 *    MotorB
 *    --  GP10,11
 *    
 *    Switch
 *    --  GP7
 *    
 *    External Switch
 *    --  GP27
 *    --  GP28
 *    
 */

#include "pitches.h"

#define ONBOARD_SW 7
#define ENDSTP_SW_A 27
#define ENDSTP_SW_B 28

#define LED 12
#define SPK_OUT   22 

#define MotorA_1 8
#define MotorA_2 9
#define MotorB_1 10
#define MotorB_2 11

#define MOTOR_A_PIN_1 8
#define MOTOR_A_PIN_2 9
#define MOTOR_B_PIN_1 10
#define MOTOR_B_PIN_2 11



bool isRobotSpinning = false;

void playTone(unsigned int frequency, unsigned int duration){
    tone(SPK_OUT, frequency, duration - 10); 
    delay(duration);
}
                    
                    
// // Direction 0: forward | 1: backward
// // Speed = from 0 to 100
// // Motor  0: Motor A | 1: MOtor B
void motorMoveControl(unsigned short motor, unsigned short direction, unsigned short speed) {    
            analogWrite((motor == 0) ? MotorA_1 : MotorB_1, (direction == 0) ? 0 : ((speed > 0) && (speed < 100)? speed +150 : 0));
            analogWrite((motor == 0) ? MotorA_2 : MotorB_2, (direction == 1) ? 0 : ((speed > 0) && (speed < 100)? speed +150 : 0));
}



void setup() {
    pinMode(ENDSTP_SW_A, INPUT_PULLUP);
    pinMode(ENDSTP_SW_B, INPUT_PULLUP);
    pinMode(ONBOARD_SW, INPUT_PULLUP);

    pinMode(LED, OUTPUT);
    pinMode(SPK_OUT, OUTPUT);
    noTone(SPK_OUT);
    
    pinMode(MotorA_1, OUTPUT);
    pinMode(MotorA_2, OUTPUT);
    pinMode(MotorB_1, OUTPUT);
    pinMode(MotorB_2, OUTPUT);
    digitalWrite(MotorA_1, LOW);
    digitalWrite(MotorA_2, LOW);
    digitalWrite(MotorB_1, LOW);
    digitalWrite(MotorB_2, LOW);
    

    delay(500);
    
    Serial.begin(115200);
    Serial.println("Tone & Motor Test");
    
    playTone(NOTE_E5, 90);
    delay(100);
    playTone(NOTE_D5, 90);
    delay(100);
    playTone(NOTE_FS4, 90);
    delay(100);
    noTone(SPK_OUT);
}


void loop() {
  if (digitalRead(ONBOARD_SW) == LOW) {
    isRobotSpinning = !isRobotSpinning;
    
    for(int i = 0; i < 10; i++) {
       playTone(NOTE_A7, 50);
        delay(50);
    }
    
    
    
    
    
    
    
    
    
    
    
    
      //BabyShark Theme
    // playTone(NOTE_D5, 400);
    // playTone(NOTE_E5, 400);
    // playTone(NOTE_G5, 250);
    // playTone(NOTE_G5, 250);
    // playTone(NOTE_G5, 250);     
    // playTone(NOTE_G5, 125);
    // playTone(NOTE_G5, 250);
    // playTone(NOTE_G5, 125);
    // playTone(NOTE_G5, 250);
    
    // playTone(NOTE_D5, 250);
    // playTone(NOTE_E5, 250);
    // playTone(NOTE_G5, 250);
    // playTone(NOTE_G5, 250);
    // playTone(NOTE_G5, 250);     
    // playTone(NOTE_G5, 125);
    // playTone(NOTE_G5, 250);
    // playTone(NOTE_G5, 125);
    // playTone(NOTE_G5, 250); 

    // playTone(NOTE_D5, 250);
    // playTone(NOTE_E5, 250);
    // playTone(NOTE_G5, 250);
    // playTone(NOTE_G5, 250);
    // playTone(NOTE_G5, 250);     
    // playTone(NOTE_G5, 125);
    // playTone(NOTE_G5, 250);
    // playTone(NOTE_G5, 125);
    // playTone(NOTE_G5, 250);
    // playTone(NOTE_A5, 250);
    // playTone(NOTE_G5, 255);
    // playTone(NOTE_FS5, 1000);
    
    //Old McDonalds
//     {F4,500} {F4,500} {F4,500} {C4,500}{D4,500} {D4,500} {C4,1000}
// {A4,500} {A4,500} {G4,500} {G4,500} {F4,1500} {C4,500} 
// {F4,500} {F4,500} {F4,500} {C4,500}{D4,500} {D4,500} {C4,1000} 
// {A4,500} {A4,500} {G4,500} {G4,500} {F4,1500} 
    // playTone(NOTE_F4, 500);
    // playTone(NOTE_F4, 500);
    // playTone(NOTE_F4, 500);
    // playTone(NOTE_C4, 500);
    // playTone(NOTE_D4, 500);     
    // playTone(NOTE_D4, 500);
    // playTone(NOTE_C4, 1000);

    // playTone(NOTE_A4, 500);
    // playTone(NOTE_A4, 500);
    // playTone(NOTE_G4, 500);
    // playTone(NOTE_G4, 500);
    // playTone(NOTE_F4, 500);
    // playTone(NOTE_C4, 1000);

    // playTone(NOTE_F4, 500);
    // playTone(NOTE_F4, 500);
    // playTone(NOTE_F4, 500);
    // playTone(NOTE_C4, 500);     
    // playTone(NOTE_D4, 500);
    // playTone(NOTE_D4, 500);
    // playTone(NOTE_C4, 1000);

    // playTone(NOTE_A4, 500);
    // playTone(NOTE_A4, 500);
    // playTone(NOTE_G4, 500);
    // playTone(NOTE_G4, 500);
    // playTone(NOTE_F4, 1500);


  } else if (digitalRead(ENDSTP_SW_A) == LOW) {
      // if (isRobotSpinning) {
      //     digitalWrite(MotorA_1, LOW);
      //     digitalWrite(MotorA_2, HIGH);
      //     digitalWrite(MotorB_1, HIGH);
      //     digitalWrite(MotorB_2, LOW);
      // } else {
      //     digitalWrite(MotorA_1, LOW);
      //     digitalWrite(MotorA_2, HIGH);
      //     digitalWrite(MotorB_1, LOW);
      //     digitalWrite(MotorB_2, HIGH);
      // }

      if (isRobotSpinning) {
          motorMoveControl(0,0,50);
          motorMoveControl(1,1,50);
      } else {
          motorMoveControl(0,0,50);
          motorMoveControl(1,0,50);
      }

        
  } else if (digitalRead(ENDSTP_SW_B) == LOW) {
    // if(isRobotSpinning) {
    //       digitalWrite(MotorA_1, HIGH);
    //       digitalWrite(MotorA_2, LOW);
    //       digitalWrite(MotorB_1, LOW);
    //       digitalWrite(MotorB_2, HIGH);
    //   } else {
    //       digitalWrite(MotorA_1, HIGH);
    //       digitalWrite(MotorA_2, LOW);
    //       digitalWrite(MotorB_1, HIGH);
    //       digitalWrite(MotorB_2, LOW);
    //   }
    if (isRobotSpinning) {
          motorMoveControl(0,0,50);
          motorMoveControl(1,1,50);
      } else {
          motorMoveControl(0,0,50);
          motorMoveControl(1,0,50);
      }
  } else {
      digitalWrite(MotorA_1, LOW);
      digitalWrite(MotorA_2, LOW);
      digitalWrite(MotorB_1, LOW);
      digitalWrite(MotorB_2, LOW);
      
  }
}
                    
                
                    
                