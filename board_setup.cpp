#include "board_setup.h"
#include "morse.h"

LiquidCrystal *lcd = new LiquidCrystal(8, 9, 4, 5, 6, 7);
SoftwareSerial hc12(10, 11);
Button button;

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
}

int Menu() {
    int menu_option = 1;

    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Select Action");
    lcd->setCursor(12, 2);
    lcd->print("MENU");
    lcd->setCursor(0, 1);
    lcd->print("Send Code");

    while (1) {
        checkMessages();
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
            lcd->setCursor(0, 1);
            switch (menu_option) {
            case 1:
                lcd->print("Send Code ");
                break;
            case 2:
                lcd->print("Send Word ");
                break;
            case 3:
                lcd->print("HC12 Setup");
                break;
            }
            delay(250);
        }
    }
}

int getCode(char text[]) {
    int current_value = 0, cursor_pos = 0;
    int code[ARR_SIZE] = {0};
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Enter Morse Code:");
    lcd->setCursor(cursor_pos, 1);
    lcd->cursor();
    lcd->autoscroll();
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
                text[cursor_pos] = WORDEND;
                break;
            }
            lcd->setCursor(cursor_pos, 1);
            delay(250);
        }
    }
}

int getText(char text[]) {
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

int receive() {
    int pressed = 0;
    int endofString = 0;
    String receivedData;
    char received[ARR_SIZE];
    int processedData[ARR_SIZE] = {END};
    char code[ARR_SIZE] = {END};
    char word[ARR_SIZE] = {END};

    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Message Received! :)");
    Serial.println("Message Received");
    playReceiveTone();
    delay(250);
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Press select");
    lcd->setCursor(0, 1);
    lcd->print("to read...");

    while (1) {
        Check();
        if (button != none) {
            if (button == select && !pressed) {
                delay(50);
                receivedData += hc12.readString();
                Serial.println(receivedData);
                receivedData.toCharArray(received, ARR_SIZE);
                for (int i = 0; i < ARR_SIZE; i++) {
                    processedData[i] = (int)received[i];
                }
                toMorse(code, word, processedData);
                lcd->clear();
                for (int i = 0; i < ARR_SIZE && word[i] != END; i++) {
                    lcd->setCursor(i, 0);
                    lcd->print(word[i]);
                    Serial.print(word[i]);
                    Serial.print("->");
                }
                for (int i = 0; i < ARR_SIZE && code[i] != END; i++) {
                    lcd->setCursor(i, 1);
                    lcd->print(code[i]);
                    Serial.print(code[i]);
                    Serial.print(">");
                }
                delay(500);
                pressed = 1;
            } else if (button == select && pressed) {
                break;
            }
        }
    }
    LEDBuzzerMap(code);
    delay(250);
    ReturnToMenu();
}

void send(Queue *queue, char text[]) {
    String send;
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Sending...");
    delay(500);
    toNum(text, queue);
    printQ(queue);

    pItem temp = queue->front;
    int counter = 0;
    while (queue->count > counter) {
        for (int i = 0; i < ARR_SIZE && temp->word[i] != END; i++) {
            send += (char)temp->word[i];
        }
        send += ' ';
        counter++;
        temp = temp->next;
    }
    send += '\0';
    DequeueAll(q);
    hc12.println(send);
    Serial.print(send);
    Serial.print(" ");
    lcd->clear();
    lcd->print("Message sent!");
    playSendTone();
    delay(500);
    ReturnToMenu();
    free(temp);
}

void checkMessages() {
    if (hc12.available()) {
        Serial.println("Message Available");
        receive();
    } else {
        return;
    }
}

void ReturnToMenu() {
    lcd->setCursor(0, 1);
    lcd->print("Return to MENU");
    while (true) {
        Check();
        if (button == select) {
            delay(250);
            int menu_option = 1;
            lcd->clear();
            lcd->setCursor(0, 0);
            lcd->print("Select Action");
            lcd->setCursor(12, 2);
            lcd->print("MENU");

            lcd->setCursor(0, 1);
            lcd->print("Send Code");
            break;
        }
    }
}

void LEDBuzzerMap(char code[]) {

    for (int i = 0; i < ARR_SIZE && code[i] != END; i++) {
        if (code[i] == '.') {
            tone(BUZZER_PIN, 1000, 200);
            digitalWrite(LEDPIN, HIGH);
            delay(200);
            digitalWrite(LEDPIN, LOW);
        }
        if (code[i] == '-') {
            tone(BUZZER_PIN, 1000, 500);
            digitalWrite(LEDPIN, HIGH);
            delay(500);
            digitalWrite(LEDPIN, LOW);
        }
    }
}

void playSendTone() {
    tone(BUZZER_PIN, 1000, 200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
    tone(BUZZER_PIN, 1200, 200);
    digitalWrite(LED_BUILTIN, HIGH);
}

void playReceiveTone() {
    int melody[] = {262, 330, 392, 523};
    for (int i = 0; i < 4; i++) {
        digitalWrite(LED_BUILTIN, LOW);
        tone(BUZZER_PIN, melody[i], 200);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(250);
    }
}