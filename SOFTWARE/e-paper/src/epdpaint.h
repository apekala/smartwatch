/**
 *  @filename   :   epdpaint.h
 *  @brief      :   Header file for epdpaint.c
 *  @date       :   May 26 2024
 *  @modified by:   ChatGPT
 */

#ifndef EPPAINT_H
#define EPPAINT_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "fonts.h"

// #define COLORED     0
// #define UNCOLORED   1

struct Paint{
    uint8_t* image;
    int width;
    int height;
    int rotate;
};

void PaintInit(struct  Paint* paint, unsigned char* image, int width, int height);
void PaintClear(struct Paint* paint);
int PaintGetWidth(struct Paint* paint);
void PaintSetWidth(struct Paint* paint, int width);
int PaintGetHeight(struct Paint* paint);
void PaintSetHeight(struct Paint* paint, int height);
int PaintGetRotate(struct Paint* paint);
void PaintSetRotate(struct Paint* paint, int rotate);
void PaintSetImage(struct Paint* paint, uint8_t* image);
uint8_t* PaintGetImage(struct Paint* paint);
void PaintDrawAbsolutePixel(struct Paint* paint, int x, int y);
void PaintDrawPixel(struct Paint* paint, int x, int y);
void PaintDrawCharAt(struct Paint* paint, int x, int y, char ascii_char, const sFONT* font);
void PaintDrawStringAt(struct Paint* paint, int x, int y, const char* text, const sFONT* font);
void PaintDrawLine(struct Paint* paint, int x0, int y0, int x1, int y1);
void PaintDrawHorizontalLine(struct Paint* paint, int x, int y, int width);
void PaintDrawVerticalLine(struct Paint* paint, int x, int y, int height);
void PaintDrawRectangle(struct Paint* paint, int x0, int y0, int x1, int y1);
void PaintDrawCircle(struct Paint* paint, int x, int y, int radius);

#endif /* EPPAINT_H */