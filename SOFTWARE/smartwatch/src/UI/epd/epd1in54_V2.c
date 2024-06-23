/*****************************************************************************
* | File        :   epd1in54_V2.c
* | Author      :   Waveshare team
* | Function    :   1.54inch e-paper V2
* | Info        :
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
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/

#include "epd1in54_V2.h"

#include <stdlib.h>

// waveform full refresh
uint8_t WF_Full_1IN54[159] = {
    0x80, 0x48, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x40, 0x48, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x80, 0x48, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x40, 0x48, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x8, 0x1, 0x0, 0x8, 0x1, 0x0, 0x2,
    0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x0, 0x0, 0x0,
    0x22, 0x17, 0x41, 0x0, 0x32, 0x20};

// waveform partial refresh(fast)
uint8_t WF_PARTIAL_1IN54_0[159] = {
    0x0,
    0x40,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x80,
    0x80,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x40,
    0x40,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x80,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0xF,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x1,
    0x1,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x22,
    0x22,
    0x22,
    0x22,
    0x22,
    0x22,
    0x0,
    0x0,
    0x0,
    0x02,
    0x17,
    0x41,
    0xB0,
    0x32,
    0x28,
};

void epd_destructor() {
    // Destructor
}

void EpdConstructor() {
    // 200 = EPD_WIDTH;
    // 200 = EPD_HEIGHT;
}

/**
 *  @brief: basic function for sending commands
 */
void epd_send_command(uint8_t command) {
    epdIf_digital_write_DC(0);
    // EpdWaitUntilIdle();
    epdIf_spi_transfer(command);
}

/**
 *  @brief: basic function for sending data
 */
void epd_send_data(uint8_t data) {
    epdIf_digital_write_DC(1);
    epdIf_spi_transfer(data);
}

/**
 *  @brief: Wait until the busy_pin goes HIGH
 */
void epd_wait_until_idle() {
    while (epdIf_digital_read() == 1) {  // LOW: idle, HIGH: busy
        delay_ms(100);
    }
    delay_ms(200);
}

void epd_lut(uint8_t* lut) {
    epd_send_command(0x32);
    for (uint8_t i = 0; i < 153; i++)
        epd_send_data(lut[i]);
    epd_wait_until_idle();
}

void epd_set_lut(uint8_t* lut) {
    epd_lut(lut);

    epd_send_command(0x3f);
    epd_send_data(lut[153]);

    epd_send_command(0x03);
    epd_send_data(lut[154]);

    epd_send_command(0x04);
    epd_send_data(lut[155]);
    epd_send_data(lut[156]);
    epd_send_data(lut[157]);

    epd_send_command(0x2c);
    epd_send_data(lut[158]);
}

// High Direction
int epd_HDirInit() {
    /* this calls the peripheral hardware interface, see epdif */
    if (epdIf_init() != 0) {
        return -1;
    }
    /* EPD hardware init start */
    epd_reset();

    epd_wait_until_idle();
    epd_send_command(0x12);  // SWRESET
    epd_wait_until_idle();

    epd_send_command(0x01);  // Driver output control
    epd_send_data(0xC7);
    epd_send_data(0x00);
    epd_send_data(0x01);

    epd_send_command(0x11);  // data entry mode
    epd_send_data(0x01);

    epd_send_command(0x44);  // set Ram-X address start/end position
    epd_send_data(0x00);
    epd_send_data(0x18);  // 0x0C-->(18+1)*8=200

    epd_send_command(0x45);  // set Ram-Y address start/end position
    epd_send_data(0xC7);     // 0xC7-->(199+1)=200
    epd_send_data(0x00);
    epd_send_data(0x00);
    epd_send_data(0x00);

    epd_send_command(0x3C);  // BorderWavefrom
    epd_send_data(0x01);

    epd_send_command(0x18);
    epd_send_data(0x80);

    epd_send_command(0x22);  // //Enable clock signal.
    epd_send_data(0xB1);
    epd_send_command(0x20);
    epd_wait_until_idle();

    epd_send_command(0x4E);  // set RAM x address count to 0;
    epd_send_data(0x00);
    epd_send_command(0x4F);  // set RAM y address count to 0X199;
    epd_send_data(0xC7);
    epd_send_data(0x00);
    epd_wait_until_idle();

    epd_set_lut(WF_Full_1IN54);
    /* EPD hardware init end */

    return 0;
}

// Low Direction
int epd_LDirInit() {
    /* this calls the peripheral hardware interface, see epdif */
    if (epdIf_init() != 0) {
        return -1;
    }
    /* EPD hardware init start */
    epd_reset();
    epd_wait_until_idle();
    epd_send_command(0x12);  // SWRESET
    epd_wait_until_idle();

    epd_send_command(0x01);  // Driver output control
    epd_send_data(0xC7);
    epd_send_data(0x00);
    epd_send_data(0x00);

    epd_send_command(0x11);  // data entry mode
    epd_send_data(0x03);

    epd_send_command(0x44);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    epd_send_data((0 >> 3) & 0xFF);
    epd_send_data((199 >> 3) & 0xFF);
    epd_send_command(0x45);
    epd_send_data(0 & 0xFF);
    epd_send_data((0 >> 8) & 0xFF);
    epd_send_data(199 & 0xFF);
    epd_send_data((199 >> 8) & 0xFF);

    epd_send_command(0x3C);  // BorderWavefrom
    epd_send_data(0x01);

    epd_send_command(0x18);
    epd_send_data(0x80);

    epd_send_command(0x22);  // //Load Temperature and waveform setting.
    epd_send_data(0xB1);
    epd_send_command(0x20);

    epd_send_command(0x4E);  // set RAM x address count to 0;
    epd_send_data(0x00);
    epd_send_command(0x4F);  // set RAM y address count to 0X199;
    epd_send_data(0xC7);
    epd_send_data(0x00);
    epd_wait_until_idle();

    epd_set_lut(WF_Full_1IN54);
    /* EPD hardware init end */

    return 0;
}

/**
 *  @brief: module reset.
 *          often used to awaken the module in deep sleep,
 *          see Epd::Sleep();
 */
void epd_reset() {
    // EpdIfDigitalWriteRST(1);
    // DelayMs(20);
    epdIf_digital_write_RST(0);  // module reset
    delay_ms(10);
    epdIf_digital_write_RST(1);
    delay_ms(20);
}

void epd_clear() {
    int w, h;
    w = (EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8) : (EPD_WIDTH / 8 + 1);
    h = EPD_HEIGHT;

    epd_send_command(0x24);
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            epd_send_data(0xff);
        }
    }
    epd_send_command(0x26);
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            epd_send_data(0xff);
        }
    }
    // DISPLAY REFRESH
    epd_display_frame();
}

void epd_display(uint8_t* frame_buffer) {
    int w = (EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8) : (EPD_WIDTH / 8 + 1);
    int h = EPD_HEIGHT;

    if (frame_buffer != NULL) {
        epd_send_command(0x24);
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                epd_send_data(frame_buffer[i + j * w]);
            }
        }
    }

    // DISPLAY REFRESH
    epd_display_frame();
}

void epd_display_part_base_image(uint8_t* frame_buffer) {
    int w = (EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8) : (EPD_WIDTH / 8 + 1);
    int h = EPD_HEIGHT;

    if (frame_buffer != NULL) {
        epd_send_command(0x24);
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                epd_send_data(frame_buffer[i + j * w]);
            }
        }

        epd_send_command(0x26);
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                epd_send_data(frame_buffer[i + j * w]);
            }
        }
    }

    // DISPLAY REFRESH
    epd_display_frame();
}

void epd_display_part_base_white_image() {
    int w = (EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8) : (EPD_WIDTH / 8 + 1);
    int h = EPD_HEIGHT;

    epd_send_command(0x24);
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            epd_send_data(0xff);
        }
    }

    epd_send_command(0x26);
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            epd_send_data(0xff);
        }
    }

    // DISPLAY REFRESH
    epd_display_frame();
}

void epd_display_part(uint8_t* frame_buffer) {
    int w = (EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8) : (EPD_WIDTH / 8 + 1);
    int h = EPD_HEIGHT;

    if (frame_buffer != NULL) {
        epd_send_command(0x24);
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                epd_send_data(frame_buffer[i + j * w]);
            }
        }
    }

    // DISPLAY REFRESH
    epd_display_part_frame();
}

/**
 *  @brief: private function to specify the memory area for data R/W
 */
void epd_set_memory_area(int x_start, int y_start, int x_end, int y_end) {
    epd_send_command(0x44);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    epd_send_data((x_start >> 3) & 0xFF);
    epd_send_data((x_end >> 3) & 0xFF);
    epd_send_command(0x45);
    epd_send_data(y_start & 0xFF);
    epd_send_data((y_start >> 8) & 0xFF);
    epd_send_data(y_end & 0xFF);
    epd_send_data((y_end >> 8) & 0xFF);
}

/**
 *  @brief: private function to specify the start point for data R/W
 */
void epd_set_memory_pointer(int x, int y) {
    epd_send_command(0x4e);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    epd_send_data((x >> 3) & 0xFF);
    epd_send_command(0x4F);
    epd_send_data(y & 0xFF);
    epd_send_data((y >> 8) & 0xFF);
    epd_wait_until_idle();
}

/**
 *  @brief: update the display
 *          there are 2 memory areas embedded in the e-paper display
 *          but once this function is called,
 *          the the next action of SetFrameMemory or ClearFrame will
 *          set the other memory area.
 */
void epd_display_frame() {
    // DISPLAY REFRESH
    epd_send_command(0x22);
    epd_send_data(0xc7);
    epd_send_command(0x20);
    epd_wait_until_idle();
}

void epd_display_part_frame() {
    epd_send_command(0x22);
    epd_send_data(0xcF);
    epd_send_command(0x20);
    epd_wait_until_idle();
}

void epd_set_frame_memory(uint8_t* image_buffer, int x, int y, int image_width, int image_height) {
    int x_end;
    int y_end;

    epdIf_digital_write_RST(0);  // module reset
    delay_ms(2);
    epdIf_digital_write_RST(1);
    delay_ms(2);
    epd_send_command(0x3c);
    epd_send_data(0x80);

    if (image_buffer == NULL || x < 0 || image_width < 0 || y < 0 || image_height < 0) {
        return;
    }
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    x &= 0xF8;
    image_width &= 0xF8;
    if (x + image_width >= 200) {
        x_end = 200 - 1;
    } else {
        x_end = x + image_width - 1;
    }
    if (y + image_height >= 200) {
        y_end = 200 - 1;
    } else {
        y_end = y + image_height - 1;
    }
    epd_set_memory_area(x, y, x_end, y_end);
    epd_set_memory_pointer(x, y);
    epd_send_command(0x24);
    /* send the image data */
    for (int j = 0; j < y_end - y + 1; j++) {
        for (int i = 0; i < (x_end - x + 1) / 8; i++) {
            epd_send_data(image_buffer[i + j * (image_width / 8)]);
        }
    }
}

void epd_set_frame_memory_partial(uint8_t* image_buffer, int x, int y, int image_width, int image_height) {
    int x_end;
    int y_end;

    epdIf_digital_write_RST(0);  // module reset
    delay_ms(2);
    epdIf_digital_write_RST(1);
    delay_ms(2);

    epd_set_lut(WF_PARTIAL_1IN54_0);
    epd_send_command(0x37);
    epd_send_data(0x00);
    epd_send_data(0x00);
    epd_send_data(0x00);
    epd_send_data(0x00);
    epd_send_data(0x00);
    epd_send_data(0x40);
    epd_send_data(0x00);
    epd_send_data(0x00);
    epd_send_data(0x00);
    epd_send_data(0x00);

    epd_send_command(0x3c);
    epd_send_data(0x80);

    epd_send_command(0x22);
    epd_send_data(0xc0);
    epd_send_command(0x20);
    epd_wait_until_idle();

    if (image_buffer == NULL || x < 0 || image_width < 0 || y < 0 || image_height < 0) {
        return;
    }
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    x &= 0xF8;
    image_width &= 0xF8;
    if (x + image_width >= 200) {
        x_end = 200 - 1;
    } else {
        x_end = x + image_width - 1;
    }
    if (y + image_height >= 200) {
        y_end = 200 - 1;
    } else {
        y_end = y + image_height - 1;
    }
    epd_set_memory_area(x, y, x_end, y_end);
    epd_set_memory_pointer(x, y);
    epd_send_command(0x24);
    /* send the image data */
    for (int j = 0; j < y_end - y + 1; j++) {
        for (int i = 0; i < (x_end - x + 1) / 8; i++) {
            epd_send_data(image_buffer[i + j * (image_width / 8)]);
        }
    }
}

/**
 *  @brief: After this command is transmitted, the chip would enter the
 *          deep-sleep mode to save power.
 *          The deep sleep mode would return to standby by hardware reset.
 *          The only one parameter is a check code, the command would be
 *          executed if check code = 0xA5.
 *          You can use Epd::Init() to awaken
 */
void epd_sleep() {
    epd_send_command(0x10);  // enter deep sleep
    epd_send_data(0x01);
    delay_ms(200);

    epdIf_digital_write_RST(0);
}
