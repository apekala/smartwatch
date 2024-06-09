/**
 *  @filename   :   epdpaint.c
 *  @brief      :   Implements EPD paint functions for Zephyr
 *  @date       :   May 26 2024
 *  @modified by:   ChatGPT
 */

#include "epdpaint.h"

void PaintInit(struct Paint* paint, unsigned char* image, int width, int height) {
    // paint->image = image;
    // paint->width = width % 8 ? width + 8 - (width % 8) : width;
    // paint->height = height;
    // paint->rotate = 0;
}

void PaintClear(struct Paint* paint) {
    for (int x = 0; x < paint->width; x++) {
        for (int y = 0; y < paint->height; y++) {
            PaintDrawAbsolutePixel(paint, x, y);
        }
    }
}

void PaintSetImage(struct Paint* paint, uint8_t* image) {
    paint->image = image;
}

int PaintGetWidth(struct Paint* paint) {
    return paint->width;
}

void PaintSetWidth(struct Paint* paint, int width) {
    paint->width = width % 8 ? width + 8 - (width % 8) : width;
}

int PaintGetHeight(struct Paint* paint) {
    return paint->height;
}

void PaintSetHeight(struct Paint* paint, int height) {
    paint->height = height;
}

int PaintGetRotate(struct Paint* paint) {
    return paint->rotate;
}

void PaintSetRotate(struct Paint* paint, int rotate) {
    paint->rotate = rotate;
}

uint8_t* PaintGetImage(struct Paint* paint) {
    return paint->image;
}

void PaintDrawAbsolutePixel(struct Paint* paint, int x, int y) {
    if (x < 0 || x >= paint->width || y < 0 || y >= paint->height) {
        return;
    }
         paint->image[(x + y * paint->width) / 8] |= 0x80 >> (x % 8); // White text on black background
        // paint->image[(x + y * paint->width) / 8] &= ~(0x80 >> (x % 8)); // Black text on white backround, not teted
}

void PaintDrawPixel(struct Paint* paint, int x, int y) {
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

void PaintDrawCharAt(struct Paint* paint, int x, int y, char ascii_char, const sFONT* font) {
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

void PaintDrawStringAt(struct Paint* paint, int x, int y, const char* text, const sFONT* font) {
    const char* p_text = text;
    int refcolumn = x;

    while (*p_text != 0) {
        PaintDrawCharAt(paint, refcolumn, y, *p_text, font);
        refcolumn += font->Width;
        p_text++;
    }
}

void PaintDrawLine(struct Paint* paint, int x0, int y0, int x1, int y1) {
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

void PaintDrawHorizontalLine(struct Paint* paint, int x, int y, int width) {
    int i;
    for (i = x; i < x + width; i++) {
        PaintDrawPixel(paint, i, y);
    }
}

void PaintDrawVerticalLine(struct Paint* paint, int x, int y, int height) {
    int i;
    for (i = y; i < y + height; i++) {
        PaintDrawPixel(paint, x, i);
    }
}

void PaintDrawRectangle(struct Paint* paint, int x0, int y0, int x1, int y1) {
    int min_x = (x0 < x1) ? x0 : x1;
    int max_x = (x0 > x1) ? x0 : x1;
    int min_y = (y0 < y1) ? y0 : y1;
    int max_y = (y0 > y1) ? y0 : y1;

    PaintDrawHorizontalLine(paint, min_x, min_y, max_x - min_x + 1);
    PaintDrawHorizontalLine(paint, min_x, max_y, max_x - min_x + 1);
    PaintDrawVerticalLine(paint, min_x, min_y, max_y - min_y + 1);
    PaintDrawVerticalLine(paint, max_x, min_y, max_y - min_y + 1);
}

void PaintDrawCircle(struct Paint* paint, int x, int y, int radius) {
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
