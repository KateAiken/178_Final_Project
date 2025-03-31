/*******************************************************
board_setup.h

Header File for board_setup.ccp
********************************************************/

// Header file initialization 
#ifndef BOARD_SETUP_H_
#define BOARD_SETUP_H_

#define BUZZER_PIN 12
#define SETPIN 3
#define LEDPIN 13

// Include Libraries
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <stdio.h>

// Include headerfiles 
#include "morse.h"

// Declare button types
enum Button { none,
              right,
              left,
              up,
              down,
              select };
extern Button button;

// Declare external accesible objects
extern SoftwareSerial hc12;
extern LiquidCrystal *lcd;

// Function Decleration
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

// Close Header File
#endif
