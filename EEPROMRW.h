#ifndef EEPROMRW_h
#define EEPROMRW_h

#include "Arduino.h"

class EEPROMRW {
public:
  EEPROMRW(){};
  virtual ~EEPROMRW(){};
  virtual bool begin(int eepromSize) = 0;
  //-----------------------------------
  virtual void Save_I8(int address, int8_t value) = 0;
  virtual void Save_UI8(int address, uint8_t value) = 0;
  virtual void Save_I16(int address, int16_t value) = 0;
  virtual void Save_UI16(int address, uint16_t value) = 0;
  virtual void Save_I32(int address, int32_t value) = 0;
  virtual void Save_UI32(int address, uint32_t value) = 0;
  virtual void Save_String(int address, String str, int maxLength) = 0;
  //-----------------------------------
  virtual int8_t Load_I8(int address) = 0;
  virtual uint8_t Load_UI8(int address) = 0;
  virtual int16_t Load_I16(int address) = 0;
  virtual uint16_t Load_UI16(int address) = 0;
  virtual int32_t Load_I32(int address) = 0;
  virtual uint32_t Load_UI32(int address) = 0;
  virtual String Load_String(int address, int maxLength) = 0;
  //-----------------------------------
};

#endif  //EEPROMRW_h