char *settingsitems = 
  "<-- Back\n"
  "WLAN\n"
  "Sync time\n"
  "NTP Server\n"
  "Reboot\n"
  "About";

void settingsmenu() {
  int selection = 0;
  while (true) {
    selection = u8g2.userInterfaceSelectionList("Settings", selection, settingsitems);
    if (selection == 1) {
      return;
    } else if (selection == 2) {
      wifiConfig();
    } else if (selection == 5) {
      selection = u8g2.userInterfaceMessage("Reboot?", "", "", "Yes\nNo");
      if (selection == 1) {
        ESP.restart();
      }
    }
    yield();
  }
}
