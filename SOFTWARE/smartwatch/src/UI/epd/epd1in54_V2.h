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

void epd_init();
void epd_destructor();

int epd_LDirInit();
int epd_HDirInit();
void epd_send_command(uint8_t command);
void epd_send_data(uint8_t data);
void epd_wait_until_idle();
void epd_reset();
void epd_clear();
void epd_display(uint8_t* frame_buffer);
void epd_display_part_base_image(uint8_t* frame_buffer);
void epd_display_part_base_white_image();
void epd_display_part(uint8_t* frame_buffer);
void epd_set_frame_memory(
        uint8_t* image_buffer,
        int x,
        int y,
        int image_width,
        int image_height
);
void epd_set_frame_memory_partial(
        uint8_t* image_buffer,
        int x,
        int y,
        int image_width,
        int image_height
);
void epd_display_frame();
void epd_display_part_frame();
void epd_sleep();

void epd_lut(uint8_t* lut);
void epd_set_lut(uint8_t* lut);
void epd_set_memory_area(int x_start, int y_start, int x_end, int y_end);
void epd_set_memory_pointer(int x, int y);

#endif /* EPD1IN54_V2_H */

/* END OF FILE */
