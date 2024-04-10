#pragma once
#include "image.h"

unsigned char between(int value);
float scale(float f);
image multiplyBlend(image &a, image &b);
image subtractBlend(image &a, image &b);
image screen(image &a, image &b);
image overlay(image &a, image &b);
image p6(image &a);
image p7(image &a);
image p8(image &a, const std::string &channel);
image p9(image &red, image &green, image &blue);
image p10(image &a);