/*
   ESP8266Watch
   - Connection -
   DS1302:
   CLK => GPIO 14 (D5)
   DAT => GPIO 12 (D6)
   RST => GPIO 13 (D7)

   SSD1306 0.96'' OLED:
   SDA => GPIO 4 (D2)
   SCL => GPIO 5 (D1)

   Potentiometer:
   Connect the two ends to VCC and GND, and the pin in the middle to ADC0 (A0).

   Touch button:
   SIG => GPIO 15 (D8)
*/

// Include necessary libraries.
#include <DS1302.h>
#include <U8g2lib.h>
#include <Wire.h>

// You can change the pins here.
// The porentiometer pin:
#define POTPIN A0
// The button pin:
#define BTNPIN 15
// DS1302 CLK, DAT and RST pins:
#define CLK 14
#define DAT 12
#define RST 13

// Create device objects.
DS1302 rtc(RST, DAT, CLK);
U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Configuring RTC module...");
  Serial.println();
  rtc.writeProtect(false);
  rtc.halt(false);
  // Uncomment the two lines below to set the clock.
  //  Time t(2021, 7, 21, 22, 42, 50, Time::kWednesday);
  //  rtc.time(t);

  Serial.println("RTC configuration completed. Configuring screen...");
  u8g2.begin();
  u8g2.enableUTF8Print();
//  u8g2.setFont(u8g2_font_ncenB10_tr);
  Serial.println("Screen configuration completed. Moving to the loop...");
}

void loop() {
  // put your main code here, to run repeatedly:
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 24, "RTC Test");
  printTime();
  u8g2.sendBuffer();
  delay(1000);
}

void printTime() {
  Time t = rtc.time();
  char bufDate[10];
  char bufTime[9];
  snprintf(bufDate, sizeof(bufDate), "%04d/%02d/%02d", t.yr, t.mon, t.date);
  snprintf(bufTime, sizeof(bufTime), "%02d:%02d:%02d", t.hr, t.min, t.sec);
  Serial.println(bufDate);
  Serial.println(bufTime);
  u8g2.drawStr(0, 36, bufDate);
  u8g2.drawStr(0, 48, bufTime);
}
