char *mainmenuitems = 
  "File Browser\n"
  "Settings";

void mainmenu() {
  int selection = 0;
  selection = u8g2.userInterfaceSelectionList("Main Menu", selection, mainmenuitems);
  u8g2.userInterfaceMessage("Selection", u8x8_GetStringLineStart(selection - 1, mainmenuitems), "", "OK");
}
