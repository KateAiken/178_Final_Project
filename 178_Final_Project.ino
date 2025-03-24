#include "board_Setup.h"


LiquidCrystal *lcd;

void setup() {
  Serial.begin(9600);

  Serial.println("Setup started...");

  // Initialize the LCD board
  lcd = InitLCD(PINRS, PINEN, PIND4, PIND5, PIND6, PIND7, LCD_WIDTH, LCD_HEIGHT);

  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Loading...");
  Serial.println("Check 0");
}

void loop() {
  char input[ARR_SIZE] = { 0 };
  Queue *q = CreateQueue();

  // Shows the menu on the LCD
  // Option choice 1--"Add" 2--"show" 3--"remove"
  Serial.println("Check 1");

  switch (Menu(lcd)) {
    case 1:
      // Serial.println("Check 2");
      if (getCode(lcd, input) == EXIT_OK) {
        // Serial.println("Check 3");
        ReturnToMenu(lcd);
        toNum(input, q);
        printf("\nQueue \n");
        printQ(q);
      }
      break;
    case 2:
      if (getCode(lcd, input) == EXIT_OK) {
        ReturnToMenu(lcd);
      }
      break;
    case 3:
      if (getCode(lcd, input) == EXIT_OK) {
        ReturnToMenu(lcd);
      }
      break;
  }
}
