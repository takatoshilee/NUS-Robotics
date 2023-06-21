/* 
 *  Ex_12 - Loops
 *  Meet the FlintStones
 *  
 */

void setup() {
   Serial.begin(19200); //set up serial library baud rate to 115200
   delay(2000);

   for(int i = 1; i <= 30; i++) {
     bool prime = true;
     for(int j = 2; j < i; j++) {
       if(i % j == 0) {
         prime = false;
       }
     }
     if(prime) {
       Serial.println(i);
     }
   }
}

void loop() { // <- Loop() is a forever while loop in disguise.
   
}
                    
                