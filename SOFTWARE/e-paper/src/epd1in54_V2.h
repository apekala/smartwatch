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

// typedef struct {
//      long width;
//     unsigned long height;
//     unsigned int reset_pin;
//     unsigned int dc_pin;
//     unsigned int cs_pin;
//     unsigned int busy_pin;
// } Epd;

void EpdInit();
void EpdDestructor();

int EpdLDirInit();
int EpdHDirInit();
void EpdSendCommand(uint8_t command);
void EpdSendData(uint8_t data);
void EpdWaitUntilIdle();
void EpdReset();
void EpdClear();
void EpdDisplay(uint8_t* frame_buffer);
void EpdDisplayPartBaseImage(uint8_t* frame_buffer);
void EpdDisplayPartBaseWhiteImage();
void EpdDisplayPart(uint8_t* frame_buffer);
void EpdSetFrameMemory(
        uint8_t* image_buffer,
        int x,
        int y,
        int image_width,
        int image_height
);
void EpdSetFrameMemoryPartial(
        uint8_t* image_buffer,
        int x,
        int y,
        int image_width,
        int image_height
);
void EpdDisplayFrame();
void EpdDisplayPartFrame();
void EpdSleep();

void EpdLut(uint8_t* lut);
void EpdSetLut(uint8_t* lut);
void EpdSetMemoryArea(int x_start, int y_start, int x_end, int y_end);
void EpdSetMemoryPointer(int x, int y);

#endif /* EPD1IN54_V2_H */

/* END OF FILE */
