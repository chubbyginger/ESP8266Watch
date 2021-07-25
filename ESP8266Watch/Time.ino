void printTime() {
  Time t = rtc.time();
  char bufDate[10];
  char bufTime[9];
  snprintf(bufDate, sizeof(bufDate), "%04d/%02d/%02d", t.yr, t.mon, t.date);
  snprintf(bufTime, sizeof(bufTime), "%02d:%02d:%02d", t.hr, t.min, t.sec);
  String analogStr = "Analog:";
  analogStr += String(analogRead(POTPIN));
  String digitalStr = "Digital:";
  digitalStr += String(digitalRead(BTNPIN));
  u8g2.drawStr(0, 12, bufDate);
  u8g2.drawStr(0, 24, bufTime);
  u8g2.drawStr(0, 36, analogStr.c_str());
  u8g2.drawStr(0, 48, digitalStr.c_str());
}
