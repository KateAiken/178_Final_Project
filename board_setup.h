#ifndef BOARD_SETUP_H_
#define BOARD_SETUP_H_

#define BUZZER_PIN 12
#define SETPIN 3
#define LEDPIN 2

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <stdio.h>

#include "morse.h"

enum Button { none,
              right,
              left,
              up,
              down,
              select };
extern Button button;

extern SoftwareSerial hc12;
extern LiquidCrystal *lcd;

void Check();

int Menu();

int getCode(char text[]);

int getText(char text[]);

int receive();

void send(Queue *queue, char text[]);

void checkMessages();

void ReturnToMenu();

void LEDBuzzerMap(char code[]);

void playSendTone();

void playReceiveTone();

#endif
