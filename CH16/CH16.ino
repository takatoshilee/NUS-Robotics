/* 
 *  Ex_16 - i2C Range Sensor
 *  Retrieve Range information from the i2C Ultrasonic Sensor
 *  Todo: Add in the VL6180X library & code
 *  
 *    LEDs 
 *    --  GP12
 *    
 *    
 *    I2C 
 *    --  GP18 (SDA) 
 *    --  GP19 (SCL) 
 *    
 */

#include <Wire.h>

// I2C address
#define SR04_I2CADDR 0x57
#define OLED_I2CAADR 0x3C

#include "pitches.h"


#define I2C1_SDA 18
#define I2C1_SCL 19
#define LED 12

#define SPK_OUT   22 

void playTone(unsigned int frequency, unsigned int duration){
    tone(SPK_OUT, frequency, duration - 10); 
    delay(duration);
}

// Code to read the range information from the UltraSonic sensor
int ping_mm()
{
    unsigned long distance = 0;
    byte i;   
    byte ds[3];
    long timeChecked;
    
    Wire1.beginTransmission(SR04_I2CADDR);
    Wire1.write(1);          //1 = cmd to start measurement.
    Wire1.endTransmission();

    delay(200); // Delay 200ms

    i = 0;
    Wire1.requestFrom(0x57,3);  //read distance       
    while (Wire1.available())
    {
     ds[i++] = Wire1.read();
    }        
    
    distance = (unsigned long)(ds[0] << 16);
    distance = distance + (unsigned long)(ds[1] << 8);
    distance = (distance + (unsigned long)(ds[2])) / 1000;
    //measured value between 10 mm (1 cm) to 6 meters (600 cm)
    if ((10 <= distance) && (6000 >= distance)) {
        return (int)distance;
    }  else {
        return -1;
    }
}

void setup() {
    Wire1.setSDA(I2C1_SDA);
    Wire1.setSCL(I2C1_SCL);
    Wire1.begin(); 
    pinMode(LED, OUTPUT);
    delay(2000);
    
    Serial.begin(115200);
    Serial.println("Range Sensor Demo");

    
}


void loop() {
    int uDistance = ping_mm();
    if (uDistance > 0) {
        Serial.println("Range <->");
        Serial.print("Distance(mm): "); 
        Serial.println(ping_mm());
        delay(500);
    }  
    if(uDistance <= 10) {
      playTone(NOTE_F4, 500);
      playTone(NOTE_F4, 500);
      playTone(NOTE_F4, 500);
    }
}
                    
                    
                