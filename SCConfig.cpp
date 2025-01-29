#include "SCConfig.h"

#if defined(ESP32)
#include "EEPROMESP32.h"
#elif defined(ESP8266)
#include "EEPROMESP8266.h"
#elif defined(ARDUINO_ARCH_RP2040)
#include "EEPROMRP2040.h"
#endif

SCConfig::SCConfig(void) {
}
SCConfig::~SCConfig(void) {
}
bool SCConfig::begin(String jsonTemplate, int maxJSONConfigSize, int eepromSize, int eepromAddress) {
  mJSONTemplate = jsonTemplate;
  mEEPROMSize = eepromSize;
  mEEPROMAddress = eepromAddress;
  mJD = new JsonDocument();
#if defined(ESP32)
  mEERW = new EEPROMESP32();
#elif defined(ESP8266)
  mEERW = new EEPROMESP8266();
#elif defined(ARDUINO_ARCH_RP2040)
  mEERW = new EEPROMRP2040();
#endif
#if defined(ESP32) || defined(ESP8266)
  Serial.setRxBufferSize(maxJSONConfigSize);
#endif
  //------------------------------------------------
  if (!mEERW->begin(mEEPROMSize)) return false;
  //mEERW->Save_UI8(mEEPROMAddress + 0, 255);
  if (mEERW->Load_UI8(mEEPROMAddress + 0) != 25) {
    //------------------------------------------------
    SaveData(mJSONTemplate);
    //------------------------------------------------
    mEERW->Save_UI8(mEEPROMAddress + 0, 25);
  }
  if (!ParseJSONString(LoadData())) {
    mEERW->Save_UI8(mEEPROMAddress + 0, 255);
#if defined(ESP32) || defined(ESP8266)
    Serial.println("Restarting...");
    ESP.restart();
#elif defined(ARDUINO_ARCH_RP2040)
    Serial.println("Restart the device");
#endif
    return false;
  }
  return true;
}
void SCConfig::Check() {
  String inputString = "";
  while (Serial.available()) {
    inputString += (char)Serial.read();
    delay(1);
  }
  inputString.trim();
  if (inputString.length()) {
    OnCommand(inputString);
  }
}
void SCConfig::OnCommand(String command) {
  if (command == "help") {
    Serial.println("1. Use help command to get description of all commands.");
    Serial.println("2. Use get command to get all data in JSON format.");
    Serial.println("3. Use reset command to reset all data to its dafault values.");
    Serial.println("4. Enter the edited JSON string you have got using get command.");
    Serial.println("5. Validate your JSON String here: https://jsonlint.com");
  } else if (command == "get") {
    Serial.println(LoadData());
  } else if (command == "reset") {
    mEERW->Save_UI8(mEEPROMAddress + 0, 255);
    Serial.println("Default values set.");
#if defined(ESP32) || defined(ESP8266)
    Serial.println("Restarting...");
    ESP.restart();
#elif defined(ARDUINO_ARCH_RP2040)
    Serial.println("Restart the device");
#endif
  } else {
    String tempData = LoadData();
    if (!ParseJSONString(command)) {
      SaveData(tempData);
      Serial.println("Wrong data/command provided.");
#if defined(ESP32) || defined(ESP8266)
      Serial.println("Restarting...");
      ESP.restart();
#elif defined(ARDUINO_ARCH_RP2040)
      Serial.println("Restart the device");
#endif
    }
    SaveData(command);
    Serial.println("Configuration Updated Successfully.");
#if defined(ESP32) || defined(ESP8266)
    Serial.println("Restarting...");
    ESP.restart();
#elif defined(ARDUINO_ARCH_RP2040)
    Serial.println("Restart the device");
#endif
  }
}
void SCConfig::SaveData(String jsonString) {
  mEERW->Save_String(mEEPROMAddress + 1, jsonString, mEEPROMSize - 10);
}
String SCConfig::LoadData() {
  return (mEERW->Load_String(mEEPROMAddress + 1, mEEPROMSize - 10));
}
bool SCConfig::ParseJSONString(String jsonString) {
  DeserializationError error = deserializeJson(*mJD, jsonString);
  if (error) {
    Serial.println("Wrong JSON String:");
    Serial.println(jsonString);
    Serial.println("Validate it here: https://jsonlint.com");
    return false;
  }
  return true;
}
JsonDocument* SCConfig::GetJSONDocument() {
  return mJD;
}

SCConfig Cfg;
