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

void paint_init(struct  Paint* paint, unsigned char* image, int width, int height);
void paint_clear(struct Paint* paint);
int paint_get_width(struct Paint* paint);
void paint_set_width(struct Paint* paint, int width);
int paint_get_height(struct Paint* paint);
void paint_set_height(struct Paint* paint, int height);
int paint_get_rotate(struct Paint* paint);
void paint_set_rotate(struct Paint* paint, int rotate);
void paint_set_image(struct Paint* paint, uint8_t* image);
uint8_t* paint_get_image(struct Paint* paint);
void paint_draw_absolute_pixel(struct Paint* paint, int x, int y);
void paint_draw_pixel(struct Paint* paint, int x, int y);
void paint_draw_char_at(struct Paint* paint, int x, int y, char ascii_char, const sFONT* font);
void paint_draw_string_at(struct Paint* paint, int x, int y, const char* text, const sFONT* font);
void paint_draw_line(struct Paint* paint, int x0, int y0, int x1, int y1);
void paint_draw_horizontal_line(struct Paint* paint, int x, int y, int width);
void paint_draw_vertical_line(struct Paint* paint, int x, int y, int height);
void paint_draw_rectangle(struct Paint* paint, int x0, int y0, int x1, int y1);
void paint_draw_circle(struct Paint* paint, int x, int y, int radius);

#endif /* EPPAINT_H */