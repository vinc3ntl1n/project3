#pragma once
#include "image.h"

unsigned char clamp(int value);
unsigned char intToChar(int value);
int charToInt(char value);
float scale(float f);
float screenCalculator(float f, int a, int b);
float checkBounds(float f);
float norm(unsigned char a, unsigned char top, unsigned char bottom);
image multiply(image &a, image &b);
image subtract(image &a, image &b);
image screen(image &a, image &b);
image overlay(image &a, image &b);
image part6(image &a);
image part7(image &a);
image part8(image &a, const string &channel);
image part9(image &red, image &green, image &blue);
image part10(image &a);