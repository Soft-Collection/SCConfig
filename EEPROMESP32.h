#ifndef EEPROMESP32_h
#define EEPROMESP32_h

#include "Arduino.h"
#include "EEPROM.h"
#include "EEPROMRW.h"

class EEPROMESP32 : public EEPROMRW {
public:
  EEPROMESP32();
  virtual ~EEPROMESP32();
  bool begin(int eepromSize);
  //-----------------------------------
  void Save_I8(int address, int8_t value);
  void Save_UI8(int address, uint8_t value);
  void Save_I16(int address, int16_t value);
  void Save_UI16(int address, uint16_t value);
  void Save_I32(int address, int32_t value);
  void Save_UI32(int address, uint32_t value);
  void Save_String(int address, String str, int maxLength);
  //-----------------------------------
  int8_t Load_I8(int address);
  uint8_t Load_UI8(int address);
  int16_t Load_I16(int address);
  uint16_t Load_UI16(int address);
  int32_t Load_I32(int address);
  uint32_t Load_UI32(int address);
  String Load_String(int address, int maxLength);
  //-----------------------------------
};

#endif  //EEPROMESP32_h