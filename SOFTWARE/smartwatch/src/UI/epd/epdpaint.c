/**
 *  @filename   :   epdpaint.c
 *  @brief      :   Implements EPD paint functions for Zephyr
 *  @date       :   May 26 2024
 *  @modified by:   ChatGPT
 */

#include "epdpaint.h"

void paint_init(struct Paint* paint, unsigned char* image, int width, int height) {
    // paint->image = image;
    // paint->width = width % 8 ? width + 8 - (width % 8) : width;
    // paint->height = height;
    // paint->rotate = 0;
}

void paint_clear(struct Paint* paint) {
    for (int x = 0; x < paint->width; x++) {
        for (int y = 0; y < paint->height; y++) {
            paint_draw_absolute_pixel(paint, x, y);
        }
    }
}

void paint_set_image(struct Paint* paint, uint8_t* image) {
    paint->image = image;
}

int paint_get_width(struct Paint* paint) {
    return paint->width;
}

void paint_set_width(struct Paint* paint, int width) {
    paint->width = width % 8 ? width + 8 - (width % 8) : width;
}

int paint_get_height(struct Paint* paint) {
    return paint->height;
}

void paint_set_height(struct Paint* paint, int height) {
    paint->height = height;
}

int paint_get_rotate(struct Paint* paint) {
    return paint->rotate;
}

void paint_set_rotate(struct Paint* paint, int rotate) {
    paint->rotate = rotate;
}

uint8_t* paint_get_image(struct Paint* paint) {
    return paint->image;
}

void paint_draw_absolute_pixel(struct Paint* paint, int x, int y) {
    if (x < 0 || x >= paint->width || y < 0 || y >= paint->height) {
        return;
    }
     paint->image[(x + y * paint->width) / 8] |= 0x80 >> (x % 8); // White text on black background
    // paint->image[(x + y * paint->width) / 8] &= ~(0x80 >> (x % 8)); // Black text on white backround, not teted
}

void paint_draw_pixel(struct Paint* paint, int x, int y) {
    if (paint->rotate == 0) {
        if (x < 0 || x >= paint->width || y < 0 || y >= paint->height) {
            return;
        }
        paint_draw_absolute_pixel(paint, x, y);
    } else if (paint->rotate == 90) {
        if (x < 0 || x >= paint->height || y < 0 || y >= paint->width) {
            return;
        }
        int temp = x;
        x = paint->width - y - 1;
        y = temp;
        paint_draw_absolute_pixel(paint, x, y);
    } else if (paint->rotate == 180) {
        if (x < 0 || x >= paint->width || y < 0 || y >= paint->height) {
            return;
        }
        x = paint->width - x - 1;
        y = paint->height - y - 1;
        paint_draw_absolute_pixel(paint, x, y);
    } else if (paint->rotate == 270) {
        if (x < 0 || x >= paint->height || y < 0 || y >= paint->width) {
            return;
        }
        int temp = x;
        x = y;
        y = paint->height - temp - 1;
        paint_draw_absolute_pixel(paint, x, y);
    }
}

void paint_draw_char_at(struct Paint* paint, int x, int y, char ascii_char, const sFONT* font) {
    int i, j;
    unsigned int char_offset = (ascii_char - ' ') * font->Height * (font->Width / 8 + (font->Width % 8 ? 1 : 0));
    const unsigned char* ptr = &font->table[char_offset];

    for (j = 0; j < font->Height; j++) {
        for (i = 0; i < font->Width; i++) {
            if (*ptr & (0x80 >> (i % 8))) {
                paint_draw_pixel(paint, x + i, y + j);
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

void paint_draw_string_at(struct Paint* paint, int x, int y, const char* text, const sFONT* font) {
    const char* p_text = text;
    int refcolumn = x;

    while (*p_text != 0) {
        paint_draw_char_at(paint, refcolumn, y, *p_text, font);
        refcolumn += font->Width;
        p_text++;
    }
}

void paint_draw_line(struct Paint* paint, int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1) {
        paint_draw_pixel(paint, x0, y0);
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

void paint_draw_horizontal_line(struct Paint* paint, int x, int y, int width) {
    int i;
    for (i = x; i < x + width; i++) {
        paint_draw_pixel(paint, i, y);
    }
}

void paint_draw_vertical_line(struct Paint* paint, int x, int y, int height) {
    int i;
    for (i = y; i < y + height; i++) {
        paint_draw_pixel(paint, x, i);
    }
}

void paint_draw_rectangle(struct Paint* paint, int x0, int y0, int x1, int y1) {
    int min_x = (x0 < x1) ? x0 : x1;
    int max_x = (x0 > x1) ? x0 : x1;
    int min_y = (y0 < y1) ? y0 : y1;
    int max_y = (y0 > y1) ? y0 : y1;

    paint_draw_horizontal_line(paint, min_x, min_y, max_x - min_x + 1);
    paint_draw_horizontal_line(paint, min_x, max_y, max_x - min_x + 1);
    paint_draw_vertical_line(paint, min_x, min_y, max_y - min_y + 1);
    paint_draw_vertical_line(paint, max_x, min_y, max_y - min_y + 1);
}

void paint_draw_circle(struct Paint* paint, int x, int y, int radius) {
    int xi = -radius;
    int yi = 0;
    int err = 2 - 2 * radius;
    int e2;

    do {
        paint_draw_pixel(paint, x - xi, y + yi);
        paint_draw_pixel(paint, x + xi, y + yi);
        paint_draw_pixel(paint, x + xi, y - yi);
        paint_draw_pixel(paint, x - xi, y - yi);
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
