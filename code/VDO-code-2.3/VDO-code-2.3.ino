#include <Wire.h>
#include <Adafruit_GFX.h>       
#include <Adafruit_SSD1306.h> 
#include <U8g2lib.h>
#include <OneWire.h> 
#include <DallasTemperature.h>

bool resettrip = true;
char output[10];
char mangle[10];
char line[100];
const int voltageSensor = A1;
const int nightSensor = A2;
float meter = 0000.0;
float trip = 000.0;
float tripdelta = 0.0;
float night = 100;
float voltage = 00.0;
float amps = 0.0;
float value = 0;
float temp = 00.0;
float psi = 00.0;
float raw = 00.0;
int contrast = 255;

U8X8_SSD1306_128X32_UNIVISION_SW_I2C u8x8(/* clock=*/ 9, /* data=*/8, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED
#define ONE_WIRE_BUS 2 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  
  Wire.begin(0x38);    // **** 0x38 is VDO dst address - OLED u8x8 also uses 0x38 ****         
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);          

  sensors.begin(); 
    
  u8x8.begin();
  u8x8.setPowerSave(0);  
  u8x8.setContrast(contrast);
  
  u8x8.setFont(u8x8_font_profont29_2x3_f);
  u8x8.print(" Matylda");
  delay(5000);
}

void displays() {

  u8x8.clearDisplay();
  u8x8.setFont(u8x8_font_8x13_1x2_r);
  u8x8.setCursor(0, 0);
  u8x8.print("eng");

  u8x8.setFont(u8x8_font_profont29_2x3_f);
  u8x8.setCursor(4, 0);
  u8x8.print(meter,1);
  delay(2000);

  u8x8.clearDisplay();
  u8x8.setFont(u8x8_font_8x13_1x2_r);
  u8x8.setCursor(0, 0);
  u8x8.print("trip");

  u8x8.setFont(u8x8_font_profont29_2x3_f);
  u8x8.setCursor(6, 0);
  u8x8.print(trip,1);
  delay(2000);

  u8x8.clearDisplay();
  u8x8.setFont(u8x8_font_8x13_1x2_r);
  u8x8.setCursor(0, 0);
  u8x8.print("tmp/C");

  u8x8.setFont(u8x8_font_profont29_2x3_f);
  u8x8.setCursor(8, 0);
  u8x8.print(temp,1);
  delay(2000);
  
  u8x8.clearDisplay();
  u8x8.setFont(u8x8_font_8x13_1x2_r);
  u8x8.setCursor(0, 0);
  u8x8.print("volts");

  u8x8.setFont(u8x8_font_profont29_2x3_f);
  u8x8.setCursor(8, 0);
  u8x8.print(voltage,1);
 
  delay(2000);
  
}

void voltagemeter() {
    
  value = analogRead(voltageSensor);
  voltage = ((value * 5.0/1023) * 4.0 );
  
}

void nightlight() {

  night = analogRead(nightSensor);
  
  if(night >= 100){
    contrast = 0;
  }
  else {
    contrast = 255;
  }

  u8x8.setContrast(contrast);
  Serial.println(night,2);
}

void tripmeter() {

     if (resettrip == true ){
       trip = 0.0;
       tripdelta = meter;
       resettrip = false;
     }               
     
     else {
       trip = (meter - tripdelta);
    }
}

void tempmeter() {
  
    sensors.requestTemperatures();
    temp = sensors.getTempCByIndex(0);
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
}

void loop() {

  displays();

  tripmeter();

  voltagemeter();

  tempmeter();

  nightlight();
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
 
