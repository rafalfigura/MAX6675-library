// this library is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266)
  #include <pgmspace.h>
#endif
//#include <util/delay.h>
#include <stdlib.h>
#include "MAX6675_MCP.h"
#include <Adafruit_MCP23017.h>

MAX6675_MCP::MAX6675_MCP(Adafruit_MCP23017 &_mcp, int8_t SCLK, int8_t CS, int8_t MISO) {
  sclk = SCLK;
  cs = CS;
  miso = MISO;
  mcp = _mcp;
  //define pin modes
  mcp.pinMode(cs, OUTPUT);
  mcp.pinMode(sclk, OUTPUT); 
  mcp.pinMode(miso, INPUT);

  mcp.digitalWrite(cs, HIGH);
}
double MAX6675_MCP::readCelsius(void) {

  uint16_t v;
  
  mcp.digitalWrite(cs, LOW);
  delay(1);

  v = spiread();
  v <<= 8;
  v |= spiread();

  mcp.digitalWrite(cs, HIGH);

  if (v & 0x4) {
    // uh oh, no thermocouple attached!
    return NAN; 
    //return -100;
  }

  v >>= 3;

  return v*0.25;
}

double MAX6675_MCP::readFahrenheit(void) {
  return readCelsius() * 9.0/5.0 + 32;
}

byte MAX6675_MCP::spiread(void) { 
  int i;
  byte d = 0;

  for (i=7; i>=0; i--)
  {
    mcp.digitalWrite(sclk, LOW);
    delay(1);
    if (mcp.digitalRead(miso)) {
      //set the bit to 0 no matter what
      d |= (1 << i);
    }

    mcp.digitalWrite(sclk, HIGH);
    delay(1);
  }

  return d;
}
