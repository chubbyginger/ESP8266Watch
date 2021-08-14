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
#include <Arduino.h>
#include <DS1302.h>
#include <Wire.h>
#include <U8g2lib.h>
//#include <U8g2wqy.h>
#include <OneButton.h>

// You can change the pins here.
// The potentiometer pin:
#define POTPIN A0
// The button pin:
#define BTNPIN 15
// DS1302 CLK, DAT and RST pins:
#define CLK 14
#define DAT 12
#define RST 13
// The screen can only be connected to the hardware I2C bus,
// but you can edit the screen width and height here, if you
// are wanting to use another size.
//
// If your screen has a reset pin, change the reset pin below.
// If your screen doesn't have a reset pin, leave it -1.
//
// If you want another I2C bus address, change it below.
// Mine is using 0x3C. A generic 12864 should be this.
// I am using a 0.96 inch 12864 one here.
#define SCR_WIDTH 128
#define SCR_HEIGHT 64
#define SCR_RESET -1
#define SCR_ADDR 0x3C

// Some definitions to make code cleaner.
#define ALIGN_CENTER(a) ((SCR_WIDTH - (u8g2.getUTF8Width(a))) / 2)
#define ALIGN_RIGHT(a) (SCR_WIDTH -  u8g2.getUTF8Width(a))
#define ALIGN_LEFT 0
#define countof(a) (sizeof(a) / sizeof(a[0]))

// Initialize variables.
bool buttonClicked = false;
bool buttonDoubleClicked = false;
bool buttonLongPressed = false;

// Create device objects.
DS1302 rtc(RST, DAT, CLK);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
OneButton btn(BTNPIN, false);

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
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_ncenB10_tr);

  Serial.println("Configuring button...");
  btn.attachClick(clicked);
  btn.attachDoubleClick(doubleClicked);
  btn.attachLongPressStop(longPressed);
  Serial.println("Configuration completed!");
}

void loop() {
  // put your main code here, to run repeatedly:
  char *choices[] = {"Some", "Another", "The other"};
  int selection = showMenu("Choices", choices);
  Serial.println(choices[selection]);
  u8g2.clearBuffer();
  u8g2.drawStr(0, 12, choices[selection]);
  u8g2.sendBuffer();
  delay(1000);
  //  printTime();
}
