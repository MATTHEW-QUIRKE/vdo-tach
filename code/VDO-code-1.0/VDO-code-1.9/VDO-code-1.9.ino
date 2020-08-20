#include <Wire.h>
#include <Adafruit_GFX.h>       
#include <Adafruit_SSD1306.h> 
#include <U8x8lib.h>

char output[10];
char mangle[10];
char line[100];
bool resettrip=true;
float meter;
float trip;
float tripdelta;
float temp;
float psi;

U8X8_SSD1306_128X32_UNIVISION_SW_I2C u8x8(/* clock=*/ 8, /* data=*/ 9, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED

void setup() {
  
  Wire.begin(0x38);    // **** 0x38 is VDO dst address - OLED u8x8 also uses 0x38 ****         
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);          
  
  u8x8.begin();
  u8x8.setPowerSave(0);  
  u8x8.setFont(u8x8_font_chroma48medium8_r);
}


void display() {

  u8x8.setCursor(1, 0);
  u8x8.print("eng/h"); 

  u8x8.setCursor(10, 0);
  u8x8.print(meter,1);

  u8x8.setCursor(1, 2);
  u8x8.print("trip"); 

  u8x8.setCursor(10, 2);
  u8x8.print(trip,1);

  u8x8.setCursor(1, 0);
  u8x8.print("tmp/C"); 

  u8x8.setCursor(10, 0);
  u8x8.print(temp,1);

  u8x8.setCursor(1, 2);
  u8x8.print("oil/p"); 

  u8x8.setCursor(10, 2);
  u8x8.print(psi,1);

}

void tripmeter() {

     if (resettrip) {
       trip = 0;
       tripdelta = meter;
       resettrip = false;
       }
     else 
       trip = (meter - tripdelta);
}

void i2c2float(int *input)
{ 
  // First put segments in right order:
  mangle[0] = (input[6] & 0xF0) | (input[14] & 0x0F);
  mangle[1] = (input[6] << 4)   | (input[14] >> 4);
  mangle[2] = (input[7] & 0xF0) | (input[12] & 0x0F);
  mangle[3] = (input[7] << 4)   | (input[12] >> 4);
  mangle[4] = (input[8] & 0xF0) | (input[11] & 0x0F);
  mangle[5] = (input[8] << 4)   | (input[11] >> 4);
  mangle[6] = input[10];
   
  // Now mangle contains segments with this order: gdbca.fe
  
  int i = 0;
  for (int a = 0; a < 7; a++)
  {
    switch (mangle[a] & 0xFB) 
    
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

     // 6 is a magic number
     if (i == 6)
     {
       output[i] = '.';
       i++;
     }           
 } 
   //convert char array to meter float.2
   strncpy(line, output, 8);
   meter = atof(line);

   Serial.print(meter);
   Serial.println("");

}

void loop() {

  delay(1000); 

  tripmeter();

  display();
   
}

void receiveEvent(int howMany)
{
  int buffer[100];
  int receivedBytes = 0;
  
  while(0 < Wire.available()) // loop through all input data

  {
    buffer[receivedBytes++] = Wire.read(); // receive byte as a character
  }
  
  if (buffer[1] == 0xE0) 
    i2c2float(buffer);
}
 
