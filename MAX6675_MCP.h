// this library is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include <Adafruit_MCP23017.h>

class MAX6675_MCP {
 public:
  MAX6675_MCP(Adafruit_MCP23017 &_mcp, int8_t SCLK, int8_t CS, int8_t MISO);

  double readCelsius(void);
  double readFahrenheit(void);
  // For compatibility with older versions:
  double readFarenheit(void) { return readFahrenheit(); }
 private:
  int8_t sclk, miso, cs;
  Adafruit_MCP23017 mcp;
  uint8_t spiread(void);
};
