int showMenu(String title, String items[]) {
  u8g2.firstPage();
  u8g2.drawFrame(0, 0, 64, 14);
  u8g2.drawStr(0, 13, title.c_str());
  u8g2.nextPage();
  int selection;
  while (!buttonClicked) {
    btn.tick();
    selection = getCurrentSelection(items);
    u8g2.firstPage();
    u8g2.drawStr(0, 30, items[selection].c_str());
    u8g2.nextPage();
    // Make sure the watchdog won't bark.
    yield();
  }
  return selection;
}

int getCurrentSelection(String items[]) {
  int analogIn = analogRead(POTPIN);
  int itemCount = countof(items);
  int current = map(analogIn, 0, 1024, 0, itemCount);
  return current;
}
