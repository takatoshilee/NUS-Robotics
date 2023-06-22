                    
/* 
 *  Ex_18 - NEC Decoder
 *  Decode incoming infrared Signal on the Robot
 *   
 *  I2C 
 *  --  GP18 (SDA) c  
 *  --  GP19 (SCL) 
 *  
 *  LED
 *  -- GP12
 *  
 *  IR_RECV
 *  -- GP6
 *  
 *  NeoPixel
 *  -- GP20
 */
                    
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#define I2C1_SDA 18
#define I2C1_SCL 19

#define PEXP_I2CADDR 0x23
#define OLED_I2CAADR 0x3C

#define NEO_PIXEL 20
#define LED_COUNT 3

#define LED 12
#define IR_RECV 6

SSD1306AsciiWire oled(Wire1);

uint8_t LEDState = LOW;

//Just some variables to hold temporary data
char text[10];
uint8_t  i, nec_state = 0; 
unsigned int command, address;

static unsigned long nec_code;
static boolean nec_ok = false;
static unsigned long timer_value_old;
static unsigned long timer_value;

#define MotorA_1 8
#define MotorA_2 9
#define MotorB_1 10
#define MotorB_2 11

void motorMoveControl(unsigned short motor, unsigned short direction, unsigned short speed) {    
  analogWrite((motor == 0) ? MotorA_1 : MotorB_1, (direction == 0) ? 0 : ((speed > 0) && (speed < 100)? speed +150 : 0));
  analogWrite((motor == 0) ? MotorA_2 : MotorB_2, (direction == 1) ? 0 : ((speed > 0) && (speed < 100)? speed +150 : 0));
}


void irISR() {
    
    timer_value = micros() - timer_value_old;       // Store elapse timer value in microS
    
    switch(nec_state){
        case 0:   //standby:                                      
            if (timer_value > 67500) {          // Greater than one frame...
                timer_value_old = micros();     // Reset microS Timer
                nec_state = 1;                  // Next state: end of 9ms pulse + LeadingSpace 4.5ms
                i = 0;
            }
        break;

        // Leading Mark = Leading pulse + leading space = 9000 + 4500 = 13500
        // max tolerance = 1000
        case 1:   //startPulse:
            if (timer_value >= (13500 - 1000) && timer_value <= (13500 + 1000)) { //its a Leading Mark
                i = 0;
                timer_value_old = micros();
                nec_state = 2;
            }
            else 
                nec_state = 0;
        break;

        //Bit 0 Mark length = 562.5µs pulse + 562.5µs space = 1125
        //Bit 1 Mark length = 562.5µs pulse + 3 * 562.5µs space = 2250
        //max tolerance = (2250 - 1125)/2 = 562.5 
        case 2:   //receiving:
            if (timer_value < (1125 - 562) || timer_value > (2250 + 562)) nec_state = 0; //error, not a bit mark
            else { // it's M0 or M1
                  nec_code = nec_code << 1; //push a 0 from Right to Left (will be left at 0 if it's M0)
                  if(timer_value >= (2250 - 562)) nec_code |= 0x01; //it's M1, change LSB to 1
                  i++;
                  
                  if (i==32) { //all bits received
                      nec_ok = true;
//                    detachInterrupt(IR_RECV);   // Optional: Disable external interrupt to prevent next incoming signal
                      nec_state = 0;
                      timer_value_old = micros();
                  }
                  else {
                      nec_state = 2; //continue receiving
                      timer_value_old = micros();
                  }
              }
        break;
      
        default:
            nec_state = 0;
        break;
    }
}

void setup() {
    Wire1.setSDA(I2C1_SDA);
    Wire1.setSCL(I2C1_SCL);
    Wire1.begin();  
    
    oled.begin(&Adafruit128x32, OLED_I2CAADR); 
    Serial.begin(115200); //set up serial library baud rate to 115200
    delay(2000);
                    
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LEDState);
    pinMode(IR_RECV, INPUT);
    delay(2000);
    
    oled.setFont(Adafruit5x7);
    oled.clear();
    oled.println("NEC Decoder!");

    pinMode(MotorA_1, OUTPUT);
    pinMode(MotorA_2, OUTPUT);
    pinMode(MotorB_1, OUTPUT);
    pinMode(MotorB_2, OUTPUT);
    digitalWrite(MotorA_1, LOW);
    digitalWrite(MotorA_2, LOW);
    digitalWrite(MotorB_1, LOW);
    digitalWrite(MotorB_2, LOW);
    
    attachInterrupt(IR_RECV, irISR, FALLING);  //Settig IR detection on FALLING edge.


}

void loop() {
    if(nec_ok) {                                     // If a good NEC message is received
        nec_ok = false;                             // Reset decoding process
        
        LEDState = (LEDState == LOW) ? HIGH: LOW;   // Toggle LED to show new IR result
        digitalWrite(LED, LEDState);

        oled.clear();
        oled.println("NEC IR Received:");
        
        oled.print("Addr: ");
        address = nec_code >> 16;
        command = (nec_code & 0xFFFF) >> 8;         // Remove inverted Bits
        sprintf(text, "%04X", address);
        oled.println(text);                             // Display address in hex format

        oled.print("Cmd: ");
        sprintf(text, "%02X", command);
        oled.println(text);                             // Display command in hex format


        if(command == 0x88) {
          oled.println("UP");
          motorMoveControl(1,1,40);
          motorMoveControl(0,0,40);
        } else if(command == 0x98) {
          oled.println("BACK");
          motorMoveControl(0,0,40);
          motorMoveControl(1,1,40);
        } else if(command == 0x28) {
          oled.println("LEFT");
          motorMoveControl(0,1,40);
          motorMoveControl(1,0,40);
        } else if(command == 0x68) {
          oled.println("RIGHT");
          motorMoveControl(1,0,40);
          motorMoveControl(0,1,40);
        } else if(command == 0xA8) {
          oled.println("STOP");
          motorMoveControl(0,0,40);
          motorMoveControl(0,0,40);
        } 
            

//      attachInterrupt(IR_RECV, irISR, FALLING);  //Setting IR detection on FALLING edge.
    }   
}
            