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

#define COLORED     0
#define UNCOLORED   1

typedef struct {
    unsigned char* image;
    int width;
    int height;
    int rotate;
} Paint;

void PaintInit(Paint* paint, unsigned char* image, int width, int height);
void PaintClear(Paint* paint, int colored);
int PaintGetWidth(Paint* paint);
void PaintSetWidth(Paint* paint, int width);
int PaintGetHeight(Paint* paint);
void PaintSetHeight(Paint* paint, int height);
int PaintGetRotate(Paint* paint);
void PaintSetRotate(Paint* paint, int rotate);
unsigned char* PaintGetImage(Paint* paint);
void PaintDrawAbsolutePixel(Paint* paint, int x, int y, int colored);
void PaintDrawPixel(Paint* paint, int x, int y, int colored);
void PaintDrawCharAt(Paint* paint, int x, int y, char ascii_char, const sFONT* font, int colored);
void PaintDrawStringAt(Paint* paint, int x, int y, const char* text, const sFONT* font, int colored);
void PaintDrawLine(Paint* paint, int x0, int y0, int x1, int y1, int colored);
void PaintDrawHorizontalLine(Paint* paint, int x, int y, int width, int colored);
void PaintDrawVerticalLine(Paint* paint, int x, int y, int height, int colored);
void PaintDrawRectangle(Paint* paint, int x0, int y0, int x1, int y1, int colored);
void PaintDrawCircle(Paint* paint, int x, int y, int radius, int colored);

#endif /* EPPAINT_H */