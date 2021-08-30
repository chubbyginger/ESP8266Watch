/*
 * Notes on data persistence:
 * 
 * The WLAN SSID, WLAN Password and the NTP server choice are stored in the
 * EEPROM (actually a place in the internal flash) for data persistence.
 * * The WLAN SSID is intended to be stored from address 0 to address 63, max
 *   64 ASCII characters. Currently only ASCII characters are allowed.
 * * The WLAN Password is intended to be stored from address 64 to address 127,
 *   max 64 ASCII characters. Currently only ASCII characters are allowed.
 * * The NTP server choice is intended to be stored from address 128 to 129, max
 *   1 byte, 256 integers. This means that you can have at most 256 NTP servers.
 */

/*
 * Read or write strings to EEPROM.
 * These functions come from The Robotics Back-End.
 * Reference: https://roboticsbackend.com/arduino-write-string-in-eeprom/
 */

void writeStringToEEPROM(int addrOffset, const String &strToWrite) {
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++) {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
  EEPROM.commit();
}

String readStringFromEEPROM(int addrOffset) {
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; i++) {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0';
  return String(data);
}
