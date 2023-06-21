/* 
 *  Ex_11 - Conditional
 *  Simple communication through the Serial monitor.
 *  
 */
String rcvString = "";
int height = 0;
int weight = 0;
float BMI = 0.0;

void setup() {
   Serial.begin(115200); // set up serial library baud rate to 115200
   delay(2000);
   Serial.println("Enter weight?");
}

void loop() {
  if (Serial.available()) {
    rcvString = Serial.readString();

    if(rcvString == "\n") {
      if(weight == 0) {
         weight = rcvString.toFloat();
         rcvString = "";
      }
      Serial.println("Enter height in meters");
    } else {
      height = rcvString.toFloat();
      rcvString = "";
      BMI = weight / sq(height);
      if (BMI < 16) {
        Serial.println("Severely Underweight");
      } else if (BMI <= 18.4) {
        Serial.println("Underweight");
      } else if (BMI <= 24.9) {
        Serial.println("Normal");
      } else if (BMI <= 29.9) {
        Serial.println("Overweight");
      } else if (BMI <= 34.9) {
        Serial.println("Moderately Obese");
      } else if (BMI <= 39.9) {
        Serial.println("Severely Obese");
      } else {
        Serial.println("Morbidly Obese");
      }
    }
  }
}
