char *mainmenuitems =
  "<-- Back\n"
  "File Manager\n"
  "Settings";

void mainmenu() {
  int selection = 0;
  while (true) {
    selection = u8g2.userInterfaceSelectionList("Main Menu", selection, mainmenuitems);
    if (selection == 1) {
      return;
    } else if (selection == 3) {
      settingsmenu();
    } else {
      u8g2.userInterfaceMessage("Developing", "Go back", "", "OK");
    }
    yield();
  }
}

int selectionmenu(String title, char *items[], int glyphs[]) {
  unsigned int selection = 0;
  bool first = true;
  bool last = false;
  char *currenttext = items[selection];
  while (!btnenterClicked) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(ALIGN_CENTER(title.c_str()), 12, title.c_str());
    u8g2.drawHLine(0, 14, SCR_WIDTH);
    u8g2.setFont(u8g2_font_open_iconic_all_4x_t);
    u8g2.drawGlyph(ALIGN_CENTER_PROCESSED_LENGTH(32), 50, glyphs[selection]);
//    if (first) {
//      u8g2.drawTriangle(10, 30, 10, 34, 5, 32);
//    } else if (last) {
//      u8g2.drawTriangle(118, 30, 118, 34, 123, 32);
//    } else {
//      u8g2.drawTriangle(10, 30, 10, 34, 5, 32);
//      u8g2.drawTriangle(118, 30, 118, 34, 123, 32);
//    }
    u8g2.drawStr(ALIGN_CENTER(currenttext), 63, currenttext);
    u8g2.sendBuffer();
    btnleft.tick();
    btnright.tick();
    btnenter.tick();
    btnback.tick();
    if (btnleftClicked && (selection != 0)) {
      btnleftClicked = false;
      selection--;
    }
    if (btnrightClicked && (selection != countof(items))) {
      btnrightClicked = false;
      selection++;
    }
    if (btnbackClicked) {
      btnbackClicked = false;
      return -1;
    }
    yield();
  }
  btnenterClicked = false;
  return selection;
}
