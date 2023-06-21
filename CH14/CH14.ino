/* 
 *  Ex_14 - Physical Computing
 *  Revisit Input & Output
 *  
 *  LED 
 *  -- GP12
 *  Switch
 *  -- GP7
 *  
 */

#define ONBOARD_LED 12    // LED GP12
#define ONBOARD_SW  7    // Switch GP7

int current_LED = LOW;

void setup() {
   Serial.begin(115200); //set up serial library baud rate to 115200
   pinMode(ONBOARD_LED, OUTPUT);
   pinMode(ONBOARD_SW, INPUT_PULLUP);

   digitalWrite(ONBOARD_LED, current_LED);    // turn the LED off by making the voltage LOW   
}

void loop() {
   current_LED = (current_LED == HIGH) ? LOW: HIGH;
   digitalWrite(ONBOARD_LED, current_LED);
   
   if (digitalRead(ONBOARD_SW) == LOW) {  // Switch is asserted Low (Active Low)
      delay(1);
   }
   else {
      delay(50);
   }
}
                    
                