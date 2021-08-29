/*
   ESP8266Watch
   Connection as the schematics in the hardware folder.

   NOTICE:
   1. When booting the watch, press the BACK key if you are
      using the default pin layout because GPIO 15 cannot be
      high at boot.
   2. When uploading a program, remove the connection between
      GPIO 15 and the BACK key to make sure GPIO 15 floats
      because GPIO 15 must be low during an upload.
*/

#include <DS1302.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <OneButton.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <EEPROM.h>

// The left button pin:
#define BTNLEFT 0
#define BTNENTER 16
#define BTNRIGHT 2
#define BTNBACK 15
// DS1302 pins:
#define CLK 14
#define DAT 12
#define RST 13
// If your screen has a reset pin, change the reset pin below.
// If your screen doesn't have a reset pin, leave it -1.
#define SCR_WIDTH 128
#define SCR_HEIGHT 64
#define SCR_RESET -1

#define WIFI_TIMEOUT_SECS 5

#define ALIGN_CENTER(a) ((SCR_WIDTH - (u8g2.getUTF8Width(a))) / 2)
#define ALIGN_CENTER_PROCESSED_LENGTH(a) ((SCR_WIDTH - a) / 2)
#define ALIGN_RIGHT(a) (SCR_WIDTH -  u8g2.getUTF8Width(a))
#define ALIGN_LEFT 0
#define countof(a) (sizeof(a) / sizeof(a[0]))

bool btnleftClicked = false;
bool btnenterClicked = false;
bool btnrightClicked = false;
bool btnbackClicked = false;

DS1302 rtc(RST, DAT, CLK);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
OneButton btnleft(BTNLEFT, true);
OneButton btnenter(BTNENTER, true);
OneButton btnright(BTNRIGHT, true);
OneButton btnback(BTNBACK, true);
WiFiUDP udp;
NTPClient timeClient(udp);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Configuring RTC module...");
  Serial.println();
  rtc.writeProtect(false);
  rtc.halt(false);
  // Uncomment the two lines below to set the clock.
//  Time t(2021, 8, 25, 22, 31, 50, Time::kWednesday);
//  rtc.time(t);

  Serial.println("Configuring screen...");
  u8g2.begin(BTNENTER, BTNRIGHT, BTNLEFT, U8X8_PIN_NONE);
  u8g2.enableUTF8Print();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  u8g2.drawStr(0, 12, "Booting...");
  u8g2.sendBuffer();

  // You may need to configure the internal pullup here.
  Serial.println("Configuring button...");
  btnleft.attachClick(btnleftClickedFunc);
  btnenter.attachClick(btnenterClickedFunc);
  btnright.attachClick(btnrightClickedFunc);
  btnback.attachClick(btnbackClickedFunc);

  Serial.println("Congifuring EEPROM...");
  EEPROM.begin(512);
  
  Serial.println("Checking network connection...");
  WiFi.mode(WIFI_STA);
  connectfromconfig();
  int secs = 0;
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
    secs++;
    if (secs == WIFI_TIMEOUT_SECS) {
      break;
    }
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected!");
    Serial.print("Current SSID: ");
    Serial.println(WiFi.SSID());
  } else {
    Serial.println("WiFi not connected!");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  btnenter.tick();
  printTime();
  if (btnenterClicked) {
    btnenterClicked = false;
    mainmenu();
  }
}
