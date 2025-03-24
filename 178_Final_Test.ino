#include "board_setup.h"

LiquidCrystal *lcd;
SoftwareSerial hc12(18, 19);

void setup() {
  Serial.begin(9600);
  hc12.begin(9600);

  lcd = InitLCD(PINRS, PINEN, PIND4, PIND5, PIND6, PIND7, LCD_WIDTH, LCD_HEIGHT);

  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Loading...");
  delay(1000);
}

void loop() {
  char input[ARR_SIZE] = { '\0' };
  Queue *q = CreateQueue();
  check(hc12, lcd);

  switch (Menu(lcd)) {
    delay(250);
    case 1:
      if (getCode(lcd, input) == EXIT_OK) {
        send(lcd, q, hc12, input);
        //ReturnToMenu(lcd);
        // Serial.println("Array\n");
        // for (int i = 0; i < ARR_SIZE; i++) {
        //     Serial.print(input[i]);
        //     Serial.print(", ");
        // }
      }
      break;
    case 2:
      if (getText(lcd, input) == EXIT_OK) {
        send(lcd, q, hc12, input);
        //ReturnToMenu(lcd);
        // Serial.println("Array\n");
        // for (int i = 0; i < ARR_SIZE; i++) {
        //     Serial.print(input[i]);
        //     Serial.print(", ");
      }
  }
  break;
  check(hc12, lcd);
}
}
