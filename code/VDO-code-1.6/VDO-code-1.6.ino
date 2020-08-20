#include <Wire.h>
#include <Adafruit_GFX.h>       
#include <Adafruit_SSD1306.h> 
#include <U8x8lib.h>

char rawline[10];
char line[100]="0000.0";
char receivedBytes = 0;
char buf[100];
char data[100];

U8X8_SSD1306_128X32_UNIVISION_SW_I2C u8x8(/* clock=*/ 8, /* data=*/ 9, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED

void setup() {
  
  Wire.begin(0x38);    // **** 0x38 is VDO dst address - OLED u8x8 also uses 0x38 ****         
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);          
  
  u8x8.begin();
  u8x8.setPowerSave(0);  
  u8x8.setFont(u8x8_font_chroma48medium8_r);
}

void lcd2ascii(unsigned char * input, char * output, char * rawOutput)
// Converts the LCD display memory data received on the I2C bus into ASCII
{
  memset(output, 0, sizeof(output));

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
      case 0x00 : output[i] = '*'; break;
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
      default   : output[i] = 'x';
    }

    i++;
    if (rawOutput[a] & 0x04)
        output[i++] = '.';
  }
}
void loop() {

  delay(1500);
//u8x8.clear();
  u8x8.setCursor(1, 0);
  u8x8.print("eng/h"); 

  u8x8.setCursor(8, 0);
  u8x8.print(line);
  
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
  
  if (buf[1] == 0xE0) 
    lcd2ascii(buf, line, rawline);
}
 
