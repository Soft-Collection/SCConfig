#if defined(ESP8266)
#include "EEPROMESP8266.h"

EEPROMESP8266::EEPROMESP8266() {
}
EEPROMESP8266::~EEPROMESP8266() {
}
bool EEPROMESP8266::begin(int eepromSize) {
  EEPROM.begin(eepromSize);
  return true;
}
//-----------------------------------------------------------
void EEPROMESP8266::Save_I8(int address, int8_t value) {
  EEPROM.put(address, value);
  EEPROM.commit();
}
void EEPROMESP8266::Save_UI8(int address, uint8_t value) {
  EEPROM.put(address, value);
  EEPROM.commit();
}
void EEPROMESP8266::Save_I16(int address, int16_t value) {
  EEPROM.put(address, value);
  EEPROM.commit();
}
void EEPROMESP8266::Save_UI16(int address, uint16_t value) {
  EEPROM.put(address, value);
  EEPROM.commit();
}
void EEPROMESP8266::Save_I32(int address, int32_t value) {
  EEPROM.put(address, value);
  EEPROM.commit();
}
void EEPROMESP8266::Save_UI32(int address, uint32_t value) {
  EEPROM.put(address, value);
  EEPROM.commit();
}
void EEPROMESP8266::Save_String(int address, String str, int maxLength) {
  if (str.length() > maxLength) return;
  int length = str.length();
  EEPROM.put(address, length);
  address += sizeof(length);
  for (int i = 0; i < length; i++) {
    EEPROM.put(address++, str[i]);
  }
  EEPROM.commit();
}
//-----------------------------------------------------------
int8_t EEPROMESP8266::Load_I8(int address) {
  int8_t retVal = 0;
  EEPROM.get(address, retVal);
  return (retVal);
}
uint8_t EEPROMESP8266::Load_UI8(int address) {
  uint8_t retVal = 0;
  EEPROM.get(address, retVal);
  return (retVal);
}
int16_t EEPROMESP8266::Load_I16(int address) {
  int16_t retVal = 0;
  EEPROM.get(address, retVal);
  return (retVal);
}
uint16_t EEPROMESP8266::Load_UI16(int address) {
  uint16_t retVal = 0;
  EEPROM.get(address, retVal);
  return (retVal);
}
int32_t EEPROMESP8266::Load_I32(int address) {
  int32_t retVal = 0;
  EEPROM.get(address, retVal);
  return (retVal);
}
uint32_t EEPROMESP8266::Load_UI32(int address) {
  uint32_t retVal = 0;
  EEPROM.get(address, retVal);
  return (retVal);
}
String EEPROMESP8266::Load_String(int address, int maxLength) {
  int length;
  EEPROM.get(address, length);
  address += sizeof(length);
  String str;
  for (int i = 0; i < length; i++) {
    char c;
    EEPROM.get(address++, c);
    str += c;
  }
  return (str.length() > maxLength) ? "" : str;
}
#endif
