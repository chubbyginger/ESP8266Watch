// NTP servers, user-editable.
char *ntpservers[] = {
  "ntp1.aliyun.com",
  "ntp2.aliyun.com",
  "ntp3.aliyun.com",
  "ntp4.aliyun.com",
  "ntp5.aliyun.com",
  "ntp6.aliyun.com",
  "ntp7.aliyun.com",
};

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

void ntpselect() {
  int selection = 0;
  selection = u8g2.userInterfaceSelectionList("Choose server", selection, ntpservers);
  Serial.println(selection);
}
