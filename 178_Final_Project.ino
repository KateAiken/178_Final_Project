#include "board_setup.h"

void setup() {

  Serial.begin(9600);
  hc12.begin(9600);

  //lcd = InitLCD(PINRS, PINEN, PIND4, PIND5, PIND6, PIND7, LCD_WIDTH, LCD_HEIGHT);
  //LiquidCrystal *lcd(8, 9, 4, 5, 6, 7);
//SoftwareSerial hc12(10, 11);
  lcd->begin(16,2);
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Loading...");
  delay(1000);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("print test");
}

void loop() {
  char input[ARR_SIZE] = { '\0' };
  Queue *q = CreateQueue();
  checkMessages();

  switch (Menu()) {
    delay(250);
    case 1:
      if (getCode(input) == EXIT_OK) {
        send(q, input);
        //ReturnToMenu(lcd);
        // Serial.println("Array\n");
        // for (int i = 0; i < ARR_SIZE; i++) {
        //     Serial.print(input[i]);
        //     Serial.print(", ");
        // }
      }
      break;
    case 2:
      if (getText(input) == EXIT_OK) {
        send(q, input);
        //ReturnToMenu(lcd);
        // Serial.println("Array\n");
        // for (int i = 0; i < ARR_SIZE; i++) {
        //     Serial.print(input[i]);
        //     Serial.print(", ");
      }
      break;
  }
}
