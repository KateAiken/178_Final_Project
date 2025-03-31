// Include headerfiles
#include "board_setup.h"

// Setup Hardware Components
void setup() {
    // Setup serial momitor and hc12 module
    Serial.begin(9600);
    hc12.begin(9600);

    // Setup lights
    pinMode(SETPIN, OUTPUT);
    pinMode(LEDPIN, OUTPUT);
    digitalWrite(SETPIN, HIGH);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    // Test Serial output and empty hc12 buffer
    Serial.println("print test");
    Serial.flush();

    // Initialize LCD Screen
    lcd->begin(16, 2);
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Loading...");
    delay(1000);
}

// Main Code Loop
void loop() {
    // Initialize arrays and data structures
    char input[ARR_SIZE] = {END};
    q = CreateQueue();
    root = createBST();
    checkMessages();

    // Swtich case to check for menu selection
    switch (Menu()) {
        delay(250);
    case 1:
        // Case 1: User has selected to input morse code
        if (getCode(input) == EXIT_OK) { // getCode fills input array with desired messsage
            send(q, input); // Send translates input and adds to a queue that gets sorted and sent to other hc12 modules
        }
        break;
    case 2:
        // Case 2: User select to input text 
        if (getText(input) == EXIT_OK) { // getText fills inut array with desired message
            send(q, input); // Send translates input and adds to a queue that gets sorted and sent to the other hc12 modules
        }
        break;
    case 3:
        // Case 3: USer selected to setup hc12 by puttin it into at mode 
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
