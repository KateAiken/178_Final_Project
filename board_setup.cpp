#include "board_setup.h"
#include "morse.h"

Button button;

LiquidCrystal *InitLCD(int pin_rs, int pin_en, int pin_d4, int pin_d5,
                       int pin_d6, int pin_d7, int lcd_width, int lcd_height) {
    LiquidCrystal *lcd = new LiquidCrystal(pin_rs, pin_en, pin_d4, pin_d5, pin_d6, pin_d7);
    lcd->begin(lcd_width, lcd_height);
    return lcd;
}

void Check() {
    int x = analogRead(A0);
    if (x < 60)
        button = right;
    else if (x > 60 && x < 200)
        button = up;
    else if (x > 200 && x < 400)
        button = down;
    else if (x > 400 && x < 600)
        button = left;
    else if (x < 800 && x >= 600)
        button = select;
    else
        button = none;
    // Serial.println(x);
}

int Menu(LiquidCrystal *lcd) {
    int menu_option = 1; // 1:Morse 2:Text 3:Recieve

    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Select Action");
    lcd->setCursor(12, 2);
    lcd->print("MENU");

    lcd->setCursor(0, 1);
    lcd->print("Send Code");

    while (1) {
        // Serial.print("In Menu");
        // Serial.println(menu_option);

        Check();
        lcd->setCursor(0, 1);

        if (button != none) {
            if (button == right || button == up) {
                menu_option++;
                if (menu_option > 3)
                    menu_option = 1;
            } else if (button == left || button == down) {
                menu_option--;
                if (menu_option < 1)
                    menu_option = 3;
            } else if (button == select) {
                delay(250);
                return menu_option;
            }

            // print menu choices on Row 2
            lcd->setCursor(0, 1);
            switch (menu_option) {
            case 1:
                lcd->print("Send Code");
                break;
            case 2:
                lcd->print("Send Word");
                break;
            case 3:
                lcd->print("Recive   ");
                break;
            }
            delay(250);
        }
    }
}

int getCode(LiquidCrystal *lcd, char text[]) {
    int current_value = 0, cursor_pos = 0;
    int code[ARR_SIZE] = {0};

    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Enter Morse Code:");
    lcd->setCursor(cursor_pos, 1);
    lcd->cursor();

    while (1) {
        Check();
        if (button != none) {
            if (button == up) {
                current_value++;
                if (current_value > 3)
                    current_value = 0;
                code[cursor_pos] = current_value;

            } else if (button == down) {
                current_value--;
                if (current_value < 0)
                    current_value = 3;
                code[cursor_pos] = current_value;

            } else if (button == right) {
                cursor_pos++;
                current_value = code[cursor_pos];

            } else if (button == left) {
                cursor_pos--;

                if (cursor_pos < 0)
                    cursor_pos = 0;
                current_value = code[cursor_pos];

            } else if (button == select) {
                delay(250);
                lcd->noCursor();
                return EXIT_OK;
            }

            lcd->setCursor(cursor_pos, 1);
            delay(250);

            switch (current_value) {
            case 0: // SPACE
                lcd->print(" ");
                text[cursor_pos] = SPACE;
                break;
            case 1: // DASH
                lcd->print("-");
                text[cursor_pos] = DASH;
                break;
            case 2: // DOT
                lcd->print(".");
                text[cursor_pos] = DOT;
                break;
            case 3: // END
                lcd->print("0");
                text[cursor_pos] = '0';
                break;
            }

            lcd->setCursor(cursor_pos, 1);
            delay(250);
        }
    }
}

int getText(LiquidCrystal *lcd, char text[]) {
    int current_value = 64, cursor_pos = 0;
    int code[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; i++) {
        code[i] = 64;
    }

    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Enter Sentance:");
    lcd->setCursor(cursor_pos, 1);
    lcd->cursor();

    while (1) {
        Check();
        if (button != none) {
            if (button == up) {
                current_value++;
                if (current_value > 90)
                    current_value = 64;
                code[cursor_pos] = current_value;

            } else if (button == down) {
                current_value--;
                if (current_value < 64)
                    current_value = 90;
                code[cursor_pos] = current_value;

            } else if (button == right) {
                cursor_pos++;
                current_value = code[cursor_pos];

            } else if (button == left) {
                cursor_pos--;

                if (cursor_pos < 0)
                    cursor_pos = 0;
                current_value = code[cursor_pos];

            } else if (button == select) {
                delay(250);
                lcd->noCursor();
                return EXIT_OK;
            }
            Serial.println(current_value);

            lcd->setCursor(cursor_pos, 1);
            delay(250);

            switch (current_value) {
            case 64: // SPACE
                lcd->print(" ");
                text[cursor_pos] = SPACE;
                break;
            case 'A' ... 'Z': // DASH
                char letter = (char)current_value;
                lcd->print(letter);
                text[cursor_pos] = current_value;
                break;
            }

            lcd->setCursor(cursor_pos, 1);
            delay(250);
        }
    }
}

int receive(LiquidCrystal *lcd, SoftwareSerial hc12) {
    int pressed = 0;
    int receiving = 0;
    int index = 0;

    char code[ARR_SIZE];
    char word[ARR_SIZE];
    char received[ARR_SIZE];
    char receivedData[ARR_SIZE];

    char incomingChar = hc12.read();

    Serial.println("Check");
    if (incomingChar == '<') {
        receiving = true;
        index = 0;
        memset(receivedData, 0, ARR_SIZE);
    } else if (incomingChar == '>') {
        receiving = false;
        receivedData[index] = '\0';

        char *token = strtok(receivedData, ",");

        for (int i = 0; i < ARR_SIZE && token != NULL; i++) {
            received[i] = atoi(token);
            token = strtok(NULL, ",");
        }
    } else if (receiving) {
        for (index; index < ARR_SIZE; index++) {
            receivedData[index] = incomingChar;
        }
    }
    toMorse(code, word, received);

    lcd->setCursor(0, 0);
    lcd->print("Message Received! :)");
    Serial.print("Message Received");
    playReceiveTone();
    delay(250);
    lcd->setCursor(1, 0);
    lcd->print("Press select to read");

    while (1) {
        Check();
        if (button != none) {
            if (button == select && pressed) {
                delay(250);
                for (int i = 0; i < ARR_SIZE; i++) {
                    lcd->setCursor(0, i);
                    lcd->print(word[i]);
                    Serial.print(word[i]);
                    Serial.print(" ");
                }
                Serial.print("\n");
                for (int i = 0; i < ARR_SIZE; i++) {
                    lcd->setCursor(1, i);
                    lcd->print(code[i]);
                    Serial.print(code[i]);
                    Serial.print(" ");
                }
                delay(500);
                pressed = 1;
            } else if (button == select && !pressed) {
                ReturnToMenu(lcd);
            }
        }
    }
}

void send(LiquidCrystal *lcd, Queue *queue, SoftwareSerial hc12, char text[]) {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Sending...");
    delay(500);
    toNum(text, queue);
    //Serial.println("\nQueue\n");
    printQ(queue);

    pItem temp = (pItem)malloc(sizeof(Item));
    temp = queue->front;
    while (temp->next != NULL) {
        char message[ARR_SIZE];
        message[0] = '<';
        int pos = 1;
        for (int i = 0; i < ARR_SIZE; i++) {
            pos += sprintf(&message[pos], "%d", text[i]);
            if (i < ARR_SIZE - 1) {
                message[pos++] = ',';
            }
        }
        message[pos++] = '>';
        message[pos] = '\0';
        hc12.print(message);
        temp = temp->next;
        delay(50);
        checkMessages(hc12, lcd);
    }
    lcd->clear();
    lcd->print("Message sent!");
    playSendTone();
    delay(500);
    ReturnToMenu(lcd);
}

void checkMessages(SoftwareSerial hc12, LiquidCrystal *lcd) {
    if (hc12.available()) {
        Serial.println("Message Available");
        receive(lcd, hc12);
    }
}

void ReturnToMenu(LiquidCrystal *lcd) {
    lcd->setCursor(0, 1);
    lcd->print("Return to MENU");

    while (true) {
        Check();
        if (button == select) {
            delay(250);
            break;
        }
    }
}

void playSendTone() {
    tone(BUZZER_PIN, 1000, 200);
    delay(250);
    tone(BUZZER_PIN, 1200, 200);
}

void playReceiveTone() {
    int melody[] = {262, 330, 392, 523};
    for (int i = 0; i < 4; i++) {
        tone(BUZZER_PIN, melody[i], 200);
        delay(250);
    }
}