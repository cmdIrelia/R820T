#include <Wire.h>

void setup(void) {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  Wire.begin(); // join i2c bus (address optional for master)
}

unsigned char reverseByte(unsigned char code)
{
  unsigned char rtn=0;
  for(int i=0;i<8;i++){
    rtn<<=1;
    rtn|=(code&0x1);
    code>>=1;
  }
  return rtn;
}

void loop(void) {
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
  
  Wire.beginTransmission(0x1a);
  Wire.write(0x05);
  Wire.write(0x06);
  Wire.write(0x02);
  char error = Wire.endTransmission(false);
  Serial.write(error);         // print the character
  
  Wire.requestFrom(0x1a,7);
  for ( int i=0;Wire.available() && i<10;i++){
    unsigned char c = Wire.read();    // receive a byte as character
    Serial.write(reverseByte(c));         // print the character
  }
  
  digitalWrite(13, HIGH);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
  
}
