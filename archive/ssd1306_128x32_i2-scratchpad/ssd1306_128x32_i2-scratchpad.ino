/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x32 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

void setup()   {                
  
  Serial.begin(9600);
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();

  // Initialize I2C bus:
  Wire.begin(0x38);             // join i2c bus with address 38h
  Wire.onReceive(receiveEvent); // register event

}

void receiveEvent(int howMany)

{
  char receivedBytes = 0;
  unsigned char buf[100];
  
  while(0 < Wire.available()) // loop through all input data
  {
    char c = Wire.read(); // receive byte as a character

    if (receivedBytes < 100)
      buf[receivedBytes++] = c;    
  }
  
}

void loop() {

  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  display.println("  Matylda ");
  display.println("----------");
  display.display();
  delay(5000);
  display.clearDisplay();


 // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  display.println("hrs 2022.2");
  display.println("trip  22.2");
  display.display();
  delay(3000);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("tmp/c 63.0");
  display.println("oil/p 23.0");
  display.display();
  delay(3000); 
  display.clearDisplay(); 
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("volts 14.4");
  display.println("amps +23.6");
  display.display();
  delay(3000); 
  display.clearDisplay();

}
