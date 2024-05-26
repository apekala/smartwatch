/*****************************************************************************
* | File       :   epd1in54_V2.h
* | Author     :   Waveshare team
* | Function   :   1.54inch e-paper V2
* | Info       :
*----------------
* | This version:   V1.0
* | Date        :   2019-06-24
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/

#ifndef EPD1IN54_V2_H
#define EPD1IN54_V2_H

#include "epdif.h"

// Display resolution
#define EPD_WIDTH       200
#define EPD_HEIGHT      200

typedef struct {
    unsigned long width;
    unsigned long height;
    unsigned int reset_pin;
    unsigned int dc_pin;
    unsigned int cs_pin;
    unsigned int busy_pin;
} Epd;

void EpdInit(Epd* epd);
void EpdDestructor(Epd* epd);

int EpdLDirInit(Epd* epd);
int EpdHDirInit(Epd* epd);
void EpdSendCommand(Epd* epd, unsigned char command);
void EpdSendData(Epd* epd, unsigned char data);
void EpdWaitUntilIdle(Epd* epd);
void EpdReset(Epd* epd);
void EpdClear(Epd* epd);
void EpdDisplay(Epd* epd, const unsigned char* frame_buffer);
void EpdDisplayPartBaseImage(Epd* epd, const unsigned char* frame_buffer);
void EpdDisplayPartBaseWhiteImage(Epd* epd);
void EpdDisplayPart(Epd* epd, const unsigned char* frame_buffer);
void EpdSetFrameMemory(
        Epd* epd,
        const unsigned char* image_buffer,
        int x,
        int y,
        int image_width,
        int image_height
);
void EpdSetFrameMemoryPartial(
        Epd* epd,
        const unsigned char* image_buffer,
        int x,
        int y,
        int image_width,
        int image_height
);
void EpdDisplayFrame(Epd* epd);
void EpdDisplayPartFrame(Epd* epd);
void EpdSleep(Epd* epd);

void EpdLut(Epd* epd, unsigned char* lut);
void EpdSetLut(Epd* epd, unsigned char* lut);
void EpdSetMemoryArea(Epd* epd, int x_start, int y_start, int x_end, int y_end);
void EpdSetMemoryPointer(Epd* epd, int x, int y);

#endif /* EPD1IN54_V2_H */

/* END OF FILE */
