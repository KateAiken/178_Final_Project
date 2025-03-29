#include "board_setup.h"

void setup() {
    Serial.begin(9600);
    hc12.begin(9600);

    pinMode(SETPIN, OUTPUT);
    digitalWrite(SETPIN, HIGH);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("print test");
    Serial.flush();

    lcd->begin(16, 2);
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Loading...");
    delay(1000);
}

void loop() {
    char input[ARR_SIZE] = {END};
    q = CreateQueue();
    root = createBST();
    checkMessages();

    switch (Menu()) {
        delay(250);
    case 1:
        if (getCode(input) == EXIT_OK) {
            send(q, input);
        }
        break;
    case 2:
        if (getText(input) == EXIT_OK) {
            send(q, input);
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
                break;
            }
        }
        ReturnToMenu();
    }
}
