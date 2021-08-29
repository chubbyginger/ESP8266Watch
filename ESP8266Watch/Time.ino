/*
 * Notes on data persistence:
 * 
 * * The NTP server choice is intended to be stored in the EEPROM address
 *   128 to 129, max 1 byte, from 0 to 255. This means, you will have as
 *   many as 256 choices of NTP servers.
 */

void printTime() {
  Time t = rtc.time();
  char bufDate[11];
  char bufTime[6];
  snprintf(bufDate, sizeof(bufDate), "%04d/%02d/%02d", t.yr, t.mon, t.date);
  snprintf(bufTime, sizeof(bufTime), "%02d:%02d", t.hr, t.min);
//  String analogStr = "Analog:";
//  analogStr += String(analogRead(POTPIN));
//  String digitalStr = "Digital:";
//  digitalStr += String(digitalRead(BTNPIN));
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_inr30_mr);
  u8g2.drawStr(ALIGN_CENTER(bufTime), 40, bufTime);
  u8g2.setFont(u8g2_font_ncenB10_tr);
  u8g2.drawStr(ALIGN_CENTER(bufDate), 55, bufDate);
//  u8g2.drawStr(0, 36, analogStr.c_str());
//  u8g2.drawStr(0, 48, digitalStr.c_str());
  u8g2.sendBuffer();
}
