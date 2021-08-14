int showMenu(String title, char *items[]) {
  int selection = 0;
  while (!buttonClicked) {
    btn.tick();
    u8g2.clearBuffer();
    u8g2.drawStr(ALIGN_CENTER(title.c_str()), 12, title.c_str());
    u8g2.drawHLine(0, 13, SCR_WIDTH);
    int selection = getCurrentSelection(items);
    u8g2.drawStr(ALIGN_CENTER(items[selection]), 36, items[selection]);
    u8g2.sendBuffer();
    yield();
  }
  buttonClicked = false;
  return selection;
}

int getCurrentSelection(char *items[]) {
  int analogIn = analogRead(POTPIN);
  int itemCount = countof(items);
  int current = map(analogIn, 0, 1024, 0, itemCount);
  return current;
}
