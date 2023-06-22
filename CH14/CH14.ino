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
int currentButtonState = HIGH;
int previousButtonState = HIGH;
int currentMode;

bool toggleMode = false;
unsigned long buttonPressStartTime = 0;

void setup() {
   Serial.begin(115200); //set up serial library baud rate to 115200
   pinMode(ONBOARD_LED, OUTPUT);
   pinMode(ONBOARD_SW, INPUT_PULLUP);

   digitalWrite(ONBOARD_LED, current_LED);    // turn the LED off by making the voltage LOW   
}

void loop() {
   current_LED = (current_LED == HIGH) ? LOW: HIGH;
   digitalWrite(ONBOARD_LED, current_LED);
   

   currentButtonState = digitalRead(ONBOARD_SW);
   if((currentButtonState == LOW) && (previousButtonState == HIGH)) {
     currentMode = (currentMode >= 3) ? 0 : currentMode + 1;
     millis() = 0;
     if (currentButtonState == LOW) {
       buttonPressStartTime = millis();
     } 
     Serial.println(millis());
      if (buttonPressStartTime >= 5000) { 
        toggleMode = !toggleMode; 
        if (toggleMode) {
          currentMode = -1; 
          Serial.println("Toggle Mode");
        } else {
          currentMode = 0; 
          Serial.println("Blinking Mode");
        }
      }
      
   }
  previousButtonState = currentButtonState;
  if(toggleMode) {
    digitalWrite(ONBOARD_LED, currentButtonState);
  } else {
      if(currentMode == 0) {
        current_LED = ((millis() / 1000) % 2 == 0) ? LOW : HIGH;
        // delay(1000);
      } else if(currentMode == 1) {
        current_LED = ((millis() / 500) % 2 == 0) ? LOW : HIGH;
        // delay(500);
      } else if(currentMode == 2) {
        current_LED = ((millis() / 100) % 2 == 0) ? LOW : HIGH;
        // delay(100);
      } else {  // Switch is asserted Low (Active Low)
          current_LED = LOW;
      }
  }
  



  // add another state to hold it to change from toggle mode to static mode
  digitalWrite(ONBOARD_LED, current_LED);
}
                
                