/**
 *  @filename   :   epdpaint.c
 *  @brief      :   Implements EPD paint functions for Zephyr
 *  @date       :   May 26 2024
 *  @modified by:   ChatGPT
 */

#include "epdpaint.h"

void PaintInit(Paint* paint, unsigned char* image, int width, int height) {
    paint->image = image;
    paint->width = width % 8 ? width + 8 - (width % 8) : width;
    paint->height = height;
    paint->rotate = 0;
}

void PaintClear(Paint* paint) {
    for (int x = 0; x < paint->width; x++) {
        for (int y = 0; y < paint->height; y++) {
            PaintDrawAbsolutePixel(paint, x, y);
        }
    }
}

int PaintGetWidth(Paint* paint) {
    return paint->width;
}

void PaintSetWidth(Paint* paint, int width) {
    paint->width = width % 8 ? width + 8 - (width % 8) : width;
}

int PaintGetHeight(Paint* paint) {
    return paint->height;
}

void PaintSetHeight(Paint* paint, int height) {
    paint->height = height;
}

int PaintGetRotate(Paint* paint) {
    return paint->rotate;
}

void PaintSetRotate(Paint* paint, int rotate) {
    paint->rotate = rotate;
}

unsigned char* PaintGetImage(Paint* paint) {
    return paint->image;
}

void PaintDrawAbsolutePixel(Paint* paint, int x, int y) {
    if (x < 0 || x >= paint->width || y < 0 || y >= paint->height) {
        return;
    }
    // if (colored) {
    //     paint->image[(x + y * paint->width) / 8] |= (0x80 >> (x % 8));
    // } else {
        paint->image[(x + y * paint->width) / 8] &= ~(0x80 >> (x % 8));
    // }
}

void PaintDrawPixel(Paint* paint, int x, int y) {
    if (paint->rotate == 0) {
        if (x < 0 || x >= paint->width || y < 0 || y >= paint->height) {
            return;
        }
        PaintDrawAbsolutePixel(paint, x, y);
    } else if (paint->rotate == 90) {
        if (x < 0 || x >= paint->height || y < 0 || y >= paint->width) {
            return;
        }
        int temp = x;
        x = paint->width - y - 1;
        y = temp;
        PaintDrawAbsolutePixel(paint, x, y);
    } else if (paint->rotate == 180) {
        if (x < 0 || x >= paint->width || y < 0 || y >= paint->height) {
            return;
        }
        x = paint->width - x - 1;
        y = paint->height - y - 1;
        PaintDrawAbsolutePixel(paint, x, y);
    } else if (paint->rotate == 270) {
        if (x < 0 || x >= paint->height || y < 0 || y >= paint->width) {
            return;
        }
        int temp = x;
        x = y;
        y = paint->height - temp - 1;
        PaintDrawAbsolutePixel(paint, x, y);
    }
}

void PaintDrawCharAt(Paint* paint, int x, int y, char ascii_char, const sFONT* font) {
    int i, j;
    unsigned int char_offset = (ascii_char - ' ') * font->Height * (font->Width / 8 + (font->Width % 8 ? 1 : 0));
    const unsigned char* ptr = &font->table[char_offset];

    for (j = 0; j < font->Height; j++) {
        for (i = 0; i < font->Width; i++) {
            if (*ptr & (0x80 >> (i % 8))) {
                PaintDrawPixel(paint, x + i, y + j);
            }
            if (i % 8 == 7) {
                ptr++;
            }
        }
        if (font->Width % 8 != 0) {
            ptr++;
        }
    }
}

void PaintDrawStringAt(Paint* paint, int x, int y, const char* text, const sFONT* font) {
    const char* p_text = text;
    int refcolumn = x;

    while (*p_text != 0) {
        PaintDrawCharAt(paint, refcolumn, y, *p_text, font);
        refcolumn += font->Width;
        p_text++;
    }
}

void PaintDrawLine(Paint* paint, int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1) {
        PaintDrawPixel(paint, x0, y0);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void PaintDrawHorizontalLine(Paint* paint, int x, int y, int width) {
    int i;
    for (i = x; i < x + width; i++) {
        PaintDrawPixel(paint, i, y);
    }
}

void PaintDrawVerticalLine(Paint* paint, int x, int y, int height) {
    int i;
    for (i = y; i < y + height; i++) {
        PaintDrawPixel(paint, x, i);
    }
}

void PaintDrawRectangle(Paint* paint, int x0, int y0, int x1, int y1) {
    int min_x = (x0 < x1) ? x0 : x1;
    int max_x = (x0 > x1) ? x0 : x1;
    int min_y = (y0 < y1) ? y0 : y1;
    int max_y = (y0 > y1) ? y0 : y1;

    PaintDrawHorizontalLine(paint, min_x, min_y, max_x - min_x + 1);
    PaintDrawHorizontalLine(paint, min_x, max_y, max_x - min_x + 1);
    PaintDrawVerticalLine(paint, min_x, min_y, max_y - min_y + 1);
    PaintDrawVerticalLine(paint, max_x, min_y, max_y - min_y + 1);
}

void PaintDrawCircle(Paint* paint, int x, int y, int radius) {
    int xi = -radius;
    int yi = 0;
    int err = 2 - 2 * radius;
    int e2;

    do {
        PaintDrawPixel(paint, x - xi, y + yi);
        PaintDrawPixel(paint, x + xi, y + yi);
        PaintDrawPixel(paint, x + xi, y - yi);
        PaintDrawPixel(paint, x - xi, y - yi);
        e2 = err;
        if (e2 <= yi) {
            err += ++yi * 2 + 1;
            if (-xi == yi && e2 <= xi) {
                e2 = 0;
            }
        }
        if (e2 > xi) {
            err += ++xi * 2 + 1;
        }
    } while (xi <= 0);
}
