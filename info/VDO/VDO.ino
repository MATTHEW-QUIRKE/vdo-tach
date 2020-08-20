/* 
   Arduino based VDO display replacement project
   Release 2, January 15th, 2015
   (C) mtech.dk, 2015

   Main unit handling:
    - I2C with VDO unit (input only)
    - Conversion functions from 7 segment VDO memory map to OLED memory map
    - Separate I2C for OLED (output only)
    
  To use:
   1. Import OLED directory as an Arduino library
   2. Create a splash screen, see readme.txt
   3. Select configuration options below
   4. Compile and download this sketch
*/

// Configuration options:
// ----------------------

#define USE_SEGMENTS 1 // use segments
//#define USE_SEGMENTS 0 // use Arial font

// 2. Use comma or dot:
#define USECOMMA 1   // use comma
//#define USECOMMA 0 // use dot as comma

// *** END OF CONFIGURATION SECTION ***

// There should be no need to edit the below code

#include <Wire.h>                // For TWI/I2C
#include <Adafruit_GFX.h>        // Some graphics functions
#include <Adafruit_SSD1306.h> // OLED driver

#include "splashscreen.h"

// Each of the following characters is 16 bits wide

// Arial 1-8:
unsigned const char Numbers_1[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0x78, 0x3C, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x3E, 0x3E, 0x0F, 0x07, 0x07, 0x07, 0x0F, 0xFF, 0xFE, 0xFC, 0xF8, 0x00, 0x00, 0x00, 0x18, 0x1C, 0x1E, 0x1F, 0x07, 0x87, 0x87, 0xCF, 0xFE, 0xFE, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF8, 0x7C, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xC7, 0xC7, 0xC7, 0xC7, 0x87, 0x87, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFC, 0xFE, 0x3E, 0x0F, 0x87, 0x87, 0x8F, 0x9F, 0x1E, 0x1C, 0x18, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xC7, 0xF7, 0xFF, 0xFF, 0x3F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFE, 0xFE, 0xDF, 0x07, 0x07, 0x07, 0x8F, 0xFE, 0xFE, 0xFC, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0x7C, 0x3E, 0x1F, 0x1F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x03, 0x03, 0x07, 0xDF, 0xFE, 0xFE, 0xF8, 0x00, 0x00, 0x00, 0xE0, 0xF8, 0xFC, 0xFF, 0xEF, 0xE3, 0xE0, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xE0, 0x00, 0x00, 0x00, 0x80, 0x83, 0x83, 0x83, 0x01, 0x01, 0x01, 0x01, 0x03, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xDF, 0x07, 0x03, 0x03, 0x07, 0x9F, 0xFF, 0xFE, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFC, 0xFF, 0xFF, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF8, 0xFD, 0xFF, 0x0F, 0x07, 0x07, 0x07, 0x0F, 0xFF, 0xFD, 0xF8, 0xF0, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0F, 0x0F, 0x0F, 0x0F, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x0F, 0x0E, 0x0E, 0x0F, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x0F, 0x0E, 0x0E, 0x0E, 0x0F, 0x07, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x0F, 0x0E, 0x0E, 0x0E, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x0F, 0x0E, 0x0E, 0x0E, 0x0F, 0x07, 0x07, 0x03, 0x01, 0x00
};

// Arial 9-F:
unsigned const char Numbers_2[] PROGMEM = {
0x00, 0x00, 0x00, 0xF8, 0xFC, 0xFE, 0x1F, 0x07, 0x07, 0x07, 0x0F, 0xFE, 0xFE, 0xF8, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0xF8, 0xFE, 0x3E, 0x0F, 0x07, 0x07, 0x0F, 0x3E, 0xFE, 0xF8, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xF0, 0xFE, 0x3E, 0x7E, 0xFE, 0xF8, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFE, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x1E, 0xFC, 0xFC, 0xF0, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF8, 0x3C, 0x1E, 0x0E, 0x0E, 0x0E, 0x0E, 0x1C, 0x7C, 0x38, 0x30, 0x00, 0x00, 0xFE, 0xFE, 0xFE, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x1E, 0x3C, 0xFC, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFE, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFE, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x83, 0x87, 0x8F, 0x9F, 0x1C, 0x1C, 0x1C, 0x0E, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFC, 0xFF, 0x7F, 0x73, 0x70, 0x70, 0x73, 0x7F, 0xFF, 0xFC, 0xE0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0F, 0x1F, 0xFB, 0xF8, 0xE0, 0x00, 0x1F, 0xFF, 0xFF, 0xF1, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xE0, 0xC0, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x01, 0x07, 0x07, 0x0F, 0x0E, 0x0E, 0x0E, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x07, 0x0F, 0x0E, 0x0E, 0x0F, 0x07, 0x07, 0x01, 0x00, 0x00, 0x00, 0x08, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x0F, 0x0F, 0x08, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0F, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x0E, 0x0E, 0x0E, 0x0F, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0F, 0x07, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// ,.:
unsigned const char Comma[] PROGMEM = {0xCF, 0x6F, 0x3F, 0x0F};
unsigned const char Dot[]   PROGMEM = {0x00, 0x0F, 0x0F, 0x0F};

// Segments:
unsigned const char Segments[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFE, 0xFC, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF8, 0xFC, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0xE0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x08, 0x00, 0x00, 0x00, 
0x3C, 0x1F, 0x0F, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x1F, 0x3F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x60, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Segment ,.:
unsigned const char SegmentComma[] PROGMEM = {0xC0, 0x70, 0x30, 0x10};
unsigned const char SegmentDot[]   PROGMEM = {0xE0, 0xE0, 0xE0, 0x00};

unsigned const char Logo[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0xE0, 0xE0, 0xFC, 0xFE, 0xFE, 0xFF, 0xE0, 0xE0, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x03, 0x01, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x39, 0x38, 0x38, 0x38, 0x38, 0x3B, 0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x83, 0x01, 0x00, 0x00, 0x00, 0x01, 0x83, 0x81, 0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x81, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x7C, 0x3E, 0x7F, 0xFF, 0xF3, 0xC1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0F, 0x0F, 0x0E, 0x0E, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x0E, 0x0E, 0x0E, 0x0E, 0x0F, 0x07, 0x06, 0x02, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x0F, 0x0E, 0x0E, 0x0E, 0x0F, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x0F, 0x0E, 0x0E, 0x0E, 0x06, 0x07, 0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0F, 0x0F, 0x0E, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00
};

// OLED definition:
#define SDA_PIN 8
#define SCL_PIN 9
Adafruit_SSD1306 display(SDA_PIN,SCL_PIN);

void LCD2ASCII(unsigned char * input, char * output, char * rawOutput)
// Converts the LCD display memory data received on the I2C bus into ASCII
{
  // First put segments in right order:
  rawOutput[0] = (input[6] & 0xF0) | (input[14] & 0x0F);
  rawOutput[1] = (input[6] << 4)   | (input[14] >> 4);
  rawOutput[2] = (input[7] & 0xF0) | (input[12] & 0x0F);
  rawOutput[3] = (input[7] << 4)   | (input[12] >> 4);
  rawOutput[4] = (input[8] & 0xF0) | (input[11] & 0x0F);
  rawOutput[5] = (input[8] << 4)   | (input[11] >> 4);
  rawOutput[6] = input[10];
  
  // Now rawOutput contains segments with this order: gdbca.fe
  
  char i = 0;
  for (char a = 0; a < 7; a++)
  {
    switch (rawOutput[a] & 0xFB) // ignore dot for now
    {
      case 0x00 : output[i] = ' '; break;
      case 0x7B : output[i] = '0'; break;
      case 0x30 : output[i] = '1'; break;
      case 0xE9 : output[i] = '2'; break;
      case 0xF8 : output[i] = '3'; break;
      case 0xB2 : output[i] = '4'; break;
      case 0xDA : output[i] = '5'; break;
      case 0xDB : output[i] = '6'; break;
      case 0x38 : output[i] = '7'; break;
      case 0xFB : output[i] = '8'; break;
      case 0xFA : output[i] = '9'; break;
      case 0xBB : output[i] = 'A'; break;
      case 0xD3 : output[i] = 'B'; break;
      case 0x4B : output[i] = 'C'; break;
      case 0xF1 : output[i] = 'D'; break;
      case 0xCB : output[i] = 'E'; break;
      case 0x8B : output[i] = 'F'; break;
      default   : output[i] = 'X';
    }
    i++;
 
    // Handle dots:
    if (rawOutput[a] & 0x04)
      if (USECOMMA == 1)
        output[i++] = ',';
      else
        output[i++] = '.';
  }
  output[i++] = 0;
}

char rawLine1[10];
char rawLine2[10];
char line1[10];
char line2[10];
char oldline1[10];

void drawSegmentComma(char dot, char x, char y)
// Draws a segment-font comma or dot
{
  for (int a = 0; a < 4; a++)
    if (dot)
      display.m_pFramebuffer[x+a+128*2] = pgm_read_byte_near(SegmentDot+a);
    else
      display.m_pFramebuffer[x+a+128*2] = pgm_read_byte_near(SegmentComma+a);
}      

void drawDigit(char segments, char x, char y, char value, char rawValue)
// Draws a single digit
// segments selects between Arial font or 7-segment font
// If Arial font has been selected and the character in value is unknown, then rawValue is used
// to print the character in 7-segment font. This means that all unknown characters can be
// shown correctly
{
  uint8_t *bitmap;
  uint8_t ofs;

  if (!segments)
  {  
    if (value == ' ')
      return;
    else if ((value >= '1') && (value <= '8'))
    {
      bitmap = Numbers_1;
      ofs = value - '1';
    }
    else if (value == '9')
    {
      bitmap = Numbers_2;
      ofs = 0;
    }
    else if (value == '0')
    {
      bitmap = Numbers_2;
      ofs = 1;
    }
    else if ((value >= 'a') && (value <= 'f'))
    {
      bitmap = Numbers_2;
      ofs = 2 + value -'a';
    }
    else if ((value >= 'A') && (value <= 'F'))
    {
      bitmap = Numbers_2;
      ofs = 2 + value -'A';
    }
    else if (value == ',')
    {
      for (int a = 0; a < 4; a++)
        display.m_pFramebuffer[x+a+128*2] = pgm_read_byte_near(Comma+a);
      return;
    }
    else if (value == '.')
    {
      for (int a = 0; a < 4; a++)
        display.m_pFramebuffer[x+a+128*2] = pgm_read_byte_near(Dot+a);
      return;
    }
    else
      segments = true; // unknown character, fallback to 7-segment font
  }

  // Do the actual printing:  
  if (segments)
  {
    for (int segment = 0; segment <= 7; segment++)
    {
      if (rawValue & (1 << segment))
        for (int a = 0; a < 16; a++)
          for (int b = 0; b < 3; b++)
            display.m_pFramebuffer[x+a+128*b] = display.m_pFramebuffer[x+a+128*b] | pgm_read_byte_near(Segments+segment*16+a+128*b);
    }
  }
  else
    for (int a = 0; a < 16; a++)
      for (int b = 0; b < 3; b++)
        display.m_pFramebuffer[x+a+128*b] = pgm_read_byte_near(bitmap+ofs*16+a+128*b);
}

void setup()
{
  // Prepare for jumper selected font:
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  
  digitalWrite(2, LOW);
  digitalWrite(4, HIGH);

  // Initialize OLED display:  
  display.initialize(0x7F);     // looks like this oled only has one contrast level

  // Initialize I2C bus:
  Wire.begin(0x38);             // join i2c bus with address 38h
  Wire.onReceive(receiveEvent); // register event

  // Show logo:
  display.clear();
  display.drawBitmap(24, 0, Logo);
  display.update();

  // Clear display buffer:
  for (char a = 0; a < 7; a++)
  {
    oldline1[a] = 0;
//    oldline2[a] = 0;
    line1[a] = 0;
    line2[a] = 0;
  }
}

void receiveEvent(int howMany)
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
// Called once per I2C transaction
{
  char receivedBytes = 0;
  unsigned char buf[100];
  
  while(0 < Wire.available()) // loop through all input data
  {
    char c = Wire.read(); // receive byte as a character

    if (receivedBytes < 100)
      buf[receivedBytes++] = c;    
  }
  
  if (buf[1] == 0xE0) 
    LCD2ASCII(buf, line1, rawLine1);
  else
    LCD2ASCII(buf, line2, rawLine2);
}

long previousMillis = 0;        // will store last time display was updated
char startup = 1; 
unsigned char useSegments = 0xFF;

void loop()
{ 
  unsigned long currentMillis = millis();
  
  if (startup == 1)
  {
#if defined Splash_lines
    if ((currentMillis - previousMillis < 1500) &&
#else
    if ((currentMillis - previousMillis < 5000) &&
#endif    
        (line1[1] != 'C'))
      return;

    if (line1[1] == 'C')
      startup = 0;
    else
    {
#if defined Splash_lines
      display.clear();
      display.drawBitmap(Splash_lines, 0, SplashScreen);
      display.update();
#endif      
      startup = 2;
      return;
    }
  }
  else if (startup == 2)
  {
    if ((currentMillis - previousMillis < 5000) &&
        (line1[1] != 'C'))
      return;

    startup = 0;
  }

  // Select font based on jumper:  
  if (useSegments == 0xFF)
  {
    useSegments = USE_SEGMENTS;
    if (useSegments == 2)
      useSegments = (digitalRead(3) == HIGH) ? 1 : 0;
  }

  // Only execute at 10 Hz rate:
  if(currentMillis - previousMillis > 100)
  {
    char equal = true;
    
    // Check if something new has arrived:
    for (char a = 0; a < 7; a++)
      if (oldline1[a] != line1[a])
        equal = false;
        
    // If something new arrived, then show it, otherwise do nothing
    if (!equal)
    {
      int a = 0;
      int rawOffset = 0;
      int ofs = 0;

      // Output the display buffer:
      display.clear();
      while (line1[a] != 0)
      {
        // Take care of commas (they need special treatment):
        if ((line1[a] == ',') || (line1[a] == '.'))
        {
          if (useSegments)
          {
            drawSegmentComma((line1[a] == '.'), ofs, 0);
            ofs += 6;
          }
          else
          {
            drawDigit(false, ofs, 0, line1[a], rawLine1[rawOffset]);
            ofs += 4;
          }
        }
        else 
        {
          if (useSegments)
            drawDigit(true, ofs, 0, 0, rawLine1[rawOffset]);
          else
            drawDigit(false, ofs, 0, line1[a], rawLine1[rawOffset]);
          rawOffset++;
          ofs += 16;
        }
        a++;
      }

/*
      // Print line 2:
      display.setCursor(64,26);
      display.print(line2); // not sure what this is - could be a trip hour counter?
*/      
      display.update();
      
      for (char a = 0; a < 7; a++)
        oldline1[a] = line1[a];
    }
  }
}
