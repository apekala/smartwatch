/**
 *  @filename   :   fonts.h
 *  @brief      :   Header file for font data
 *  @date       :   May 26 2024
 *  @modified by:   ChatGPT
 */

#ifndef FONTS_H
#define FONTS_H

typedef struct {
    const unsigned char* table;
    unsigned short Width;
    unsigned short Height;
} sFONT;

extern sFONT Font8;
extern sFONT Font12;
extern sFONT Font16;
extern sFONT Font20;
extern sFONT Font24;

#endif /* FONTS_H */
