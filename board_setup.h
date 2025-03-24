#ifndef BOARD_SETUP_H_
#define BOARD_SETUP_H_

#define LCD_WIDTH   16
#define LCD_HEIGHT  2
#define LCD_SIZE    (LCD_WIDTH * LCD_HEIGHT)

#define PINRS       8
#define PINEN       9
#define PIND4       4 
#define PIND5       5 
#define PIND6       6 
#define PIND7       7  
#define BUTTONPIN   A0
#define BUZZER_PIN   12

#include <Wire.h>
#include <Arduino.h>
#include <stdio.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#include "morse.h"

#define LCD_WIDTH      16
#define LCD_HEIGHT     2
#define LCD_SIZE       (LCD_WIDTH * LCD_HEIGHT)

#define EXIT_OK         0
#define EXIT_ERROR     -1


enum Button       {none, right, left, up, down, select};

LiquidCrystal* InitLCD( int pin_rs, int pin_en, int pin_d4, int pin_d5, 
                        int pin_d6, int pin_d7, int lcd_width, int lcd_height);


void Check(LiquidCrystal *lcd);

int Menu(LiquidCrystal *lcd);

int getCode(LiquidCrystal *lcd, char text[]);

int getText(LiquidCrystal *lcd, char text[]);

int receive(LiquidCrystal *lcd, SoftwareSerial hc12);

void send(LiquidCrystal *lcd, Queue *queue, SoftwareSerial hc12, char text[]);

void checkMessages(SoftwareSerial hc12, LiquidCrystal *lcd);

void ReturnToMenu(LiquidCrystal *lcd);

void playSendTone();

void playReceiveTone();
       
#endif
