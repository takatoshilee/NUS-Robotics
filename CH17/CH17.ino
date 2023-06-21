/* 
 *  Ex_17 - Arduino Libraries
 *  Printing text to OLED Display
 *  Random color display on Neopixels
 *  
 *  I2C 
 *  --  GP18 (SDA) 
 *  --  GP19 (SCL) 
 *    
 *  
 *  NeoPixel
 *  -- GP20
 */
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#define I2C1_SDA 18
#define I2C1_SCL 19

#define SR04_I2CADDR 0x57
#define OLED_I2CAADR 0x3C

#define NEO_PIXEL 20
#define LED_COUNT 3

Adafruit_NeoPixel strip(LED_COUNT, NEO_PIXEL, NEO_GRB + NEO_KHZ800);
SSD1306AsciiWire oled(Wire1);

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
    }
    else {
        return -1;
    }
}

void setup() {
    Wire1.setSDA(I2C1_SDA);
    Wire1.setSCL(I2C1_SCL);
    Wire1.begin(); 
    
    oled.begin(&Adafruit128x32, OLED_I2CAADR); 
 
    Serial.begin(115200); //set up serial library baud rate to 115200
    delay(2000);
    Serial.println("Range Sensor & OLED Test");
    
    strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
    strip.show();            // Turn OFF all pixels ASAP
    strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
    randomSeed(analogRead(0));
  
    oled.setFont(Adafruit5x7);
    oled.clear();
    oled.println("Range + OLED");
}

void loop() {
    int uDistance = ping_mm();
    if (uDistance > 0) {
        Serial.print("Range <-> Distance(mm): ");
        Serial.println(ping_mm());
    }

    strip.setPixelColor(0, strip.Color(random(255),random(255),random(255)));
    strip.setPixelColor(1, strip.Color(random(255),random(255),random(255)));
    strip.setPixelColor(2, strip.Color(random(255),random(255),random(255)));
    strip.show(); // This sends the updated pixel color to the hardware.
  
    delay(500);
}
              
                