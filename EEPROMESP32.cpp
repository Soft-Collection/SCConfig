#if defined(ESP32)
#include "EEPROMESP32.h"

EEPROMESP32::EEPROMESP32() {
}
EEPROMESP32::~EEPROMESP32() {
}
bool EEPROMESP32::begin(int eepromSize) {
  return EEPROM.begin(eepromSize);
}
//-----------------------------------------------------------
void EEPROMESP32::Save_I8(int address, int8_t value) {
  EEPROM.writeByte(address, value);
  EEPROM.commit();
}
void EEPROMESP32::Save_UI8(int address, uint8_t value) {
  EEPROM.writeByte(address, value);
  EEPROM.commit();
}
void EEPROMESP32::Save_I16(int address, int16_t value) {
  EEPROM.writeShort(address, value);
  EEPROM.commit();
}
void EEPROMESP32::Save_UI16(int address, uint16_t value) {
  EEPROM.writeUShort(address, value);
  EEPROM.commit();
}
void EEPROMESP32::Save_I32(int address, int32_t value) {
  EEPROM.writeInt(address, value);
  EEPROM.commit();
}
void EEPROMESP32::Save_UI32(int address, uint32_t value) {
  EEPROM.writeUInt(address, value);
  EEPROM.commit();
}
void EEPROMESP32::Save_String(int address, String str, int maxLength) {
  if (str.length() < maxLength) {
    EEPROM.writeString(address, str);
    EEPROM.commit();
  }
}
//-----------------------------------------------------------
int8_t EEPROMESP32::Load_I8(int address) {
  return (EEPROM.readByte(address));
}
uint8_t EEPROMESP32::Load_UI8(int address) {
  return (EEPROM.readByte(address));
}
int16_t EEPROMESP32::Load_I16(int address) {
  return (EEPROM.readShort(address));
}
uint16_t EEPROMESP32::Load_UI16(int address) {
  return (EEPROM.readUShort(address));
}
int32_t EEPROMESP32::Load_I32(int address) {
  return (EEPROM.readInt(address));
}
uint32_t EEPROMESP32::Load_UI32(int address) {
  return (EEPROM.readUInt(address));
}
String EEPROMESP32::Load_String(int address, int maxLength) {
  String str = EEPROM.readString(address);
  return (str.length() < maxLength) ? str : "";
}
#endif
