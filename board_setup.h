#ifndef BOARD_SETUP_H_
#define BOARD_SETUP_H_

#define LCD_WIDTH 16
#define LCD_HEIGHT 2
#define LCD_SIZE (LCD_WIDTH * LCD_HEIGHT)

#define PINRS 8
#define PINEN 9
#define PIND4 4
#define PIND5 5
#define PIND6 6
#define PIND7 7
#define BUTTONPIN A0
#define BUZZER_PIN 12
#define SETPIN 3

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <stdio.h>

#include "morse.h"

#define LCD_WIDTH 16
#define LCD_HEIGHT 2
#define LCD_SIZE (LCD_WIDTH * LCD_HEIGHT)

#define EXIT_OK 0
#define EXIT_ERROR -1

extern SoftwareSerial hc12;
extern LiquidCrystal *lcd;
enum Button { none,
              right,
              left,
              up,
              down,
              select };
extern Button button;

void Check();

int Menu();

int getCode(char text[]);

int getText(char text[]);

int receive();

void send(Queue *queue, char text[]);

void checkMessages();

void ReturnToMenu();

void playSendTone();

void playReceiveTone();

#endif
