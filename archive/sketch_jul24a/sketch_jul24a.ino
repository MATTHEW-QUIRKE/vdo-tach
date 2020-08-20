// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include <Wire.h>
#include <Adafruit_GFX.h>        // Some graphics functions
#include <Adafruit_SSD1306.h> // OLED driver
#include <U8x8lib.h>
int engh = 1000;
// U8x8 Contructor  
U8X8_SSD1306_128X32_UNIVISION_SW_I2C u8x8(/* clock=*/ 8, /* data=*/ 9, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED

void setup() {
  Wire.begin(0x38);                // join i2c bus with address 
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  u8x8.begin();
  u8x8.setPowerSave(0);  
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  Wire.begin();   
  Wire.onReceive(receiveEvent); // register event
}

void loop() {
  delay(100);
  u8x8.setCursor(1, 0);
  u8x8.print("eng/h"); 
  u8x8.setCursor(10, 0);
  u8x8.print(engh);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    //Serial.println(c);         // print the character
  }
  engh++;
  int x = Wire.read();    // receive byte as an integer
  //Serial.println(x);         // print the integer
  
}
