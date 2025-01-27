//https://randomnerdtutorials.com/esp32-flash-memory/
#if !defined(__SCCONFIG_H__)
#define __SCCONFIG_H__

#include "Arduino.h"
#include <ArduinoJson.h>
#include "EEPROMRW.h"

class SCConfig {
public:
  SCConfig();
  ~SCConfig();
  bool begin(String jsonTemplate, int maxJSONConfigSize, int eepromSize, int eepromAddress);
  void Check();
  JsonDocument* GetJSONDocument();
protected:
  void OnCommand(String command);
  void SaveData(String jsonString);
  String LoadData();
  bool ParseJSONString(String jsonString);
protected:
  String mJSONTemplate;
  int mEEPROMSize;
  int mEEPROMAddress;
  JsonDocument* mJD;
  EEPROMRW* mEERW;
};

extern SCConfig Cfg;

#endif  // !defined(__SCCONFIG_H__)
