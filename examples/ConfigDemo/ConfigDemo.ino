#include <Arduino.h>
#include "SCConfig.h"

/*
Configuration example.
Provide it as a parameter in Cfg.begin
Please remember to replace " with \" and write all in one line.
{
	"tz": "your_time_zone",
	"stations": [
		{
			"ssid": "your_ssid1",
			"psk": "your_password1"
		},
		{
			"ssid": "your_ssid2",
			"psk": "your_password2"
		},
		{
			"ssid": "your_ssid3",
			"psk": "your_password3"
		}
	],
}
*/

/*
  In the Serial Monitor use the following commands: help, get, reset.
  1. Use help command to get description of all commands.
  2. Use get command to get all data in JSON format.
  3. Use reset command to reset all data to its dafault values.
  4. Enter the edited JSON string you have got using get command.
  5. Validate your JSON String here: https://jsonlint.com
*/

void perform_this_once_per_10_seconds();

void setup() {
  Serial.begin(115200);
  //Parameters are:
  //1. Configuration Template that will be saved by default
  //2. Max Configuration Template length
  //3. Whole EEPROM Size
  //4. Address in EEPROM where the data will be stored
  Cfg.begin("{\"tz\":\"your_time_zone\",\"stations\":[{\"ssid\":\"your_ssid1\",\"psk\":\"your_password1\"},{\"ssid\":\"your_ssid2\",\"psk\":\"your_password2\"},{\"ssid\":\"your_ssid3\",\"psk\":\"your_password3\"}]}", 512, 1024, 10);
}
void loop() {
  //MUST CALL THIS FUNCTIONS IN THE LOOP.
  Cfg.Check();
  //-----------------------------------------------------------
  uint32_t ms = millis();
  static uint32_t last_ms = 0;
  if (ms - last_ms > 10000) {
    perform_this_once_per_10_seconds();
    last_ms = ms;
  }
}
void perform_this_once_per_10_seconds() {
  JsonDocument* jd = Cfg.GetJSONDocument();
  int stationCount = 0;
  //-----------------------------------------------------------
  if (!(*jd)["tz"]) {
    Serial.println("No Time Zone information.");
  } else {
    Serial.println((*jd)["tz"].as<String>().c_str());
  }
  //-----------------------------------------------------------
  if (!(*jd)["stations"]) {
    Serial.println("No Stations information.");
  } else {
    stationCount = (*jd)["stations"].size();
  }
  //-----------------------------------------------------------
  for (uint8_t i = 0; i < stationCount; i++) {
    if (!(*jd)["stations"][i]["ssid"]) {
      Serial.println("No SSID information.");
    } else {
      Serial.println((*jd)["stations"][i]["ssid"].as<String>().c_str());
    }
    //-----------------------------------------------------------
    if (!(*jd)["stations"][i]["psk"]) {
      Serial.println("No PSK Information.");
    } else {
      Serial.println((*jd)["stations"][i]["psk"].as<String>().c_str());
    }
  }
}
