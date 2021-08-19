/*
   ESP8266Watch
   Connection as the schematics in the hardware folder.

   NOTICE: Press the BACK key if you are using the 
   default pin layout because GPIO 15 cannot be high at
   boot.
*/

#include <DS1302.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <OneButton.h>

// You can change the pins here.
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

// Some useful definitions
#define ALIGN_CENTER(a) ((SCR_WIDTH - (u8g2.getUTF8Width(a))) / 2)
#define ALIGN_RIGHT(a) (SCR_WIDTH -  u8g2.getUTF8Width(a))
#define ALIGN_LEFT 0
#define countof(a) (sizeof(a) / sizeof(a[0]))

// Initialize variables.
bool btnleftClicked = false;
bool btnenterClicked = false;
bool btnrightClicked = false;
bool btnbackClicked = false;

// Create device objects.
DS1302 rtc(RST, DAT, CLK);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
OneButton btnleft(BTNLEFT, true);
OneButton btnenter(BTNENTER, true);
OneButton btnright(BTNRIGHT, true);
OneButton btnback(BTNBACK, true);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Configuring RTC module...");
  Serial.println();
  rtc.writeProtect(false);
  rtc.halt(false);
  // Uncomment the two lines below to set the clock.
  //    Time t(2021, 8, 10, 22, 25, 50, Time::kTuesday);
  //    rtc.time(t);

  Serial.println("Configuring screen...");
  u8g2.begin(BTNENTER, BTNRIGHT, BTNLEFT, U8X8_PIN_NONE);
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_ncenB10_tr);

  // You may need to configure the internal pullup here.
  Serial.println("Configuring button...");
  btnleft.attachClick(btnleftClickedFunc);
  btnenter.attachClick(btnenterClickedFunc);
  btnright.attachClick(btnrightClickedFunc);
  btnback.attachClick(btnbackClickedFunc);
  Serial.println("Configuration done!");
}

void loop() {
  // put your main code here, to run repeatedly:
  char *choices[] = {"Some", "Another", "The other"};
//  int selection = showMenu("Choices", choices);
//  Serial.println(choices[selection]);
//  u8g2.clearBuffer();
//  u8g2.drawStr(0, 12, choices[selection]);
//  u8g2.sendBuffer();
//  delay(1000);
    printTime();
}
