#include "board_setup.h"

void setup() {

  Serial.begin(9600);
  hc12.begin(9600);

  //lcd = InitLCD(PINRS, PINEN, PIND4, PIND5, PIND6, PIND7, LCD_WIDTH, LCD_HEIGHT);
  //LiquidCrystal *lcd(8, 9, 4, 5, 6, 7);
  //SoftwareSerial hc12(10, 11);
  lcd->begin(16, 2);
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Loading...");
  delay(1000);

  pinMode(SETPIN, OUTPUT);
  digitalWrite(SETPIN, HIGH);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("print test");
  Serial.flush();
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
    case 3:
      lcd->clear();
      lcd->setCursor(0, 0);
      lcd->print("HC12 Setup Mode");
      digitalWrite(SETPIN, LOW);
      Serial.println("HC-12 AT Command Mode Ready");
      while (1) {
        if (Serial.available()) {
          hc12.write(Serial.read());
        }
        if (hc12.available()) {
          Serial.write(hc12.read());
        }
        Check();
        if (button != none && button == select) {
          digitalWrite(SETPIN, HIGH);
          ReturnToMenu();
        }
      }
  }
}
