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

#include <stdlib.h>
#include "epd1in54_V2.h"

// waveform full refresh
unsigned char WF_Full_1IN54[159] = {											
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
    0x22, 0x17, 0x41, 0x0, 0x32, 0x20
};

// waveform partial refresh(fast)
unsigned char WF_PARTIAL_1IN54_0[159] = {
    0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x80, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x40, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
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
    0x02, 0x17, 0x41, 0xB0, 0x32, 0x28,
};

void EpdDestructor(Epd* epd)
{
    // Destructor
}

void EpdConstructor(Epd* epd)
{
    epd->width = EPD_WIDTH;
    epd->height = EPD_HEIGHT;
}

/**
 *  @brief: basic function for sending commands
 */
void EpdSendCommand(Epd* epd, unsigned char command)
{
    EpdIfDigitalWriteDC(0);
    EpdIfSpiTransfer(command);
}

/**
 *  @brief: basic function for sending data
 */
void EpdSendData(Epd* epd, unsigned char data)
{
    EpdIfDigitalWriteDC(1);
    EpdIfSpiTransfer(data);
}

/**
 *  @brief: Wait until the busy_pin goes HIGH
 */
void EpdWaitUntilIdle(Epd* epd)
{
    while(EpdIfDigitalRead() == 1) {      //LOW: idle, HIGH: busy
        DelayMs(100);
    }
    DelayMs(200);
}

void EpdLut(Epd* epd, unsigned char* lut)
{
    EpdSendCommand(epd, 0x32);
    for(unsigned char i = 0; i < 153; i++)
        EpdSendData(epd, lut[i]);
    EpdWaitUntilIdle(epd);
}

void EpdSetLut(Epd* epd, unsigned char* lut)
{
    EpdLut(epd, lut);
    
    EpdSendCommand(epd, 0x3f);
    EpdSendData(epd, lut[153]);
    
    EpdSendCommand(epd, 0x03);
    EpdSendData(epd, lut[154]);
    
    EpdSendCommand(epd, 0x04);
    EpdSendData(epd, lut[155]);
    EpdSendData(epd, lut[156]);
    EpdSendData(epd, lut[157]);
    
    EpdSendCommand(epd, 0x2c);
    EpdSendData(epd, lut[158]);
}

// High Direction
int EpdHDirInit(Epd* epd)
{
    /* this calls the peripheral hardware interface, see epdif */
    if (EpdIfInit() != 0) {
        return -1;
    }
    /* EPD hardware init start */
    EpdReset(epd);

    EpdWaitUntilIdle(epd);
    EpdSendCommand(epd, 0x12);  //SWRESET
    EpdWaitUntilIdle(epd);

    EpdSendCommand(epd, 0x01); //Driver output control
    EpdSendData(epd, 0xC7);
    EpdSendData(epd, 0x00);
    EpdSendData(epd, 0x01);

    EpdSendCommand(epd, 0x11); //data entry mode
    EpdSendData(epd, 0x01);

    EpdSendCommand(epd, 0x44); //set Ram-X address start/end position
    EpdSendData(epd, 0x00);
    EpdSendData(epd, 0x18);    //0x0C-->(18+1)*8=200

    EpdSendCommand(epd, 0x45); //set Ram-Y address start/end position
    EpdSendData(epd, 0xC7);   //0xC7-->(199+1)=200
    EpdSendData(epd, 0x00);
    EpdSendData(epd, 0x00);
    EpdSendData(epd, 0x00);

    EpdSendCommand(epd, 0x3C); //BorderWavefrom
    EpdSendData(epd, 0x01);

    EpdSendCommand(epd, 0x18);
    EpdSendData(epd, 0x80);

    EpdSendCommand(epd, 0x22); // //Load Temperature and waveform setting.
    EpdSendData(epd, 0xB1);
    EpdSendCommand(epd, 0x20);

    EpdSendCommand(epd, 0x4E);   // set RAM x address count to 0;
    EpdSendData(epd, 0x00);
    EpdSendCommand(epd, 0x4F);   // set RAM y address count to 0X199;
    EpdSendData(epd, 0xC7);
    EpdSendData(epd, 0x00);
    EpdWaitUntilIdle(epd);

    EpdSetLut(epd, WF_Full_1IN54);
    /* EPD hardware init end */

    return 0;
}

// Low Direction
int EpdLDirInit(Epd* epd)
{
    /* this calls the peripheral hardware interface, see epdif */
    if (EpdIfInit() != 0) {
        return -1;
    }
    printk("a");
    /* EPD hardware init start */
    EpdReset(epd);
    printk("b");
    EpdWaitUntilIdle(epd);
    printk("c");
    EpdSendCommand(epd, 0x12);  //SWRESET
    EpdWaitUntilIdle(epd);

    EpdSendCommand(epd, 0x01); //Driver output control
    EpdSendData(epd, 0xC7);
    EpdSendData(epd, 0x00);
    EpdSendData(epd, 0x00);

    EpdSendCommand(epd, 0x11); //data entry mode
    EpdSendData(epd, 0x03);

    EpdSendCommand(epd, 0x44);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    EpdSendData(epd, (0 >> 3) & 0xFF);
    EpdSendData(epd, (199 >> 3) & 0xFF);
    EpdSendCommand(epd, 0x45);
    EpdSendData(epd, 0 & 0xFF);
    EpdSendData(epd, (0 >> 8) & 0xFF);
    EpdSendData(epd, 199 & 0xFF);
    EpdSendData(epd, (199 >> 8) & 0xFF);

    EpdSendCommand(epd, 0x3C); //BorderWavefrom
    EpdSendData(epd, 0x01);

    EpdSendCommand(epd, 0x18);
    EpdSendData(epd, 0x80);

    EpdSendCommand(epd, 0x22); // //Load Temperature and waveform setting.
    EpdSendData(epd, 0xB1);
    EpdSendCommand(epd, 0x20);

    EpdSendCommand(epd, 0x4E);   // set RAM x address count to 0;
    EpdSendData(epd, 0x00);
    EpdSendCommand(epd, 0x4F);   // set RAM y address count to 0X199;
    EpdSendData(epd, 0xC7);
    EpdSendData(epd, 0x00);
    EpdWaitUntilIdle(epd);

    EpdSetLut(epd, WF_Full_1IN54);
    /* EPD hardware init end */

    return 0;
}


/**
 *  @brief: module reset.
 *          often used to awaken the module in deep sleep,
 *          see Epd::Sleep();
 */
void EpdReset(Epd* epd)
{
    EpdIfDigitalWriteRST(1);
    DelayMs(20);
    EpdIfDigitalWriteRST(0);                //module reset
    DelayMs(5);
    EpdIfDigitalWriteRST(1);
    DelayMs(20);
}

void EpdClear(Epd* epd)
{
    int w, h;
    w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    h = EPD_HEIGHT;
 
    EpdSendCommand(epd, 0x24);
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            EpdSendData(epd, 0xff);
        }
    }
    EpdSendCommand(epd, 0x26);
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            EpdSendData(epd, 0xff);
        }
    }
    //DISPLAY REFRESH
    EpdDisplayFrame(epd);
}

void EpdDisplay(Epd* epd, const unsigned char* frame_buffer)
{
    int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    int h = EPD_HEIGHT;

    if (frame_buffer != NULL) {
        EpdSendCommand(epd, 0x24);
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                EpdSendData(epd, pgm_read_byte(&frame_buffer[i + j * w]));
            }
        }
    }

    //DISPLAY REFRESH
    EpdDisplayFrame(epd);
}

void EpdDisplayPartBaseImage(Epd* epd, const unsigned char* frame_buffer)
{
    int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    int h = EPD_HEIGHT;

    if (frame_buffer != NULL) {
        EpdSendCommand(epd, 0x24);
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                EpdSendData(epd, pgm_read_byte(&frame_buffer[i + j * w]));
            }
        }

        EpdSendCommand(epd, 0x26);
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                EpdSendData(epd, pgm_read_byte(&frame_buffer[i + j * w]));
            }
        }
    }

    //DISPLAY REFRESH
    EpdDisplayFrame(epd);
}

void EpdDisplayPartBaseWhiteImage(Epd* epd)
{
    int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    int h = EPD_HEIGHT;

    EpdSendCommand(epd, 0x24);
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            EpdSendData(epd, 0xff);
        }
    }

    EpdSendCommand(epd, 0x26);
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            EpdSendData(epd, 0xff);
        }
    }

    //DISPLAY REFRESH
    EpdDisplayFrame(epd);
}

void EpdDisplayPart(Epd* epd, const unsigned char* frame_buffer)
{
    int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    int h = EPD_HEIGHT;

    if (frame_buffer != NULL) {
        EpdSendCommand(epd, 0x24);
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                EpdSendData(epd, pgm_read_byte(&frame_buffer[i + j * w]));
            }
        }
    }

    //DISPLAY REFRESH
    EpdDisplayPartFrame(epd);
}


/**
 *  @brief: private function to specify the memory area for data R/W
 */
void EpdSetMemoryArea(Epd* epd, int x_start, int y_start, int x_end, int y_end)
{
    EpdSendCommand(epd, 0x44);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    EpdSendData(epd, (x_start >> 3) & 0xFF);
    EpdSendData(epd, (x_end >> 3) & 0xFF);
    EpdSendCommand(epd, 0x45);
    EpdSendData(epd, y_start & 0xFF);
    EpdSendData(epd, (y_start >> 8) & 0xFF);
    EpdSendData(epd, y_end & 0xFF);
    EpdSendData(epd, (y_end >> 8) & 0xFF);
}

/**
 *  @brief: private function to specify the start point for data R/W
 */
void EpdSetMemoryPointer(Epd* epd, int x, int y)
{
    EpdSendCommand(epd, 0x4e);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    EpdSendData(epd, (x >> 3) & 0xFF);
    EpdSendCommand(epd, 0x4F);
    EpdSendData(epd, y & 0xFF);
    EpdSendData(epd, (y >> 8) & 0xFF);
    EpdWaitUntilIdle(epd);
}


/**
 *  @brief: update the display
 *          there are 2 memory areas embedded in the e-paper display
 *          but once this function is called,
 *          the the next action of SetFrameMemory or ClearFrame will
 *          set the other memory area.
 */
void EpdDisplayFrame(Epd* epd)
{
    //DISPLAY REFRESH
    EpdSendCommand(epd, 0x22);
    EpdSendData(epd, 0xc7);
    EpdSendCommand(epd, 0x20);
    EpdWaitUntilIdle(epd);
}

void EpdDisplayPartFrame(Epd* epd)
{
    EpdSendCommand(epd, 0x22);
    EpdSendData(epd, 0xcF);
    EpdSendCommand(epd, 0x20);
    EpdWaitUntilIdle(epd);
}


void EpdSetFrameMemory(Epd* epd, const unsigned char* image_buffer, int x, int y, int image_width, int image_height)
{
    int x_end;
    int y_end;
    
    EpdIfDigitalWriteRST(0);                //module reset
    DelayMs(2);
    EpdIfDigitalWriteRST(1);
    DelayMs(2);
    EpdSendCommand(epd, 0x3c);
    EpdSendData(epd, 0x80);

    if (image_buffer == NULL || x < 0 || image_width < 0 || y < 0 || image_height < 0) {
        return;
    }
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    x &= 0xF8;
    image_width &= 0xF8;
    if (x + image_width >= epd->width) {
        x_end = epd->width - 1;
    } else {
        x_end = x + image_width - 1;
    }
    if (y + image_height >= epd->height) {
        y_end = epd->height - 1;
    } else {
        y_end = y + image_height - 1;
    }
    EpdSetMemoryArea(epd, x, y, x_end, y_end);
    EpdSetMemoryPointer(epd, x, y);
    EpdSendCommand(epd, 0x24);
    /* send the image data */
    for (int j = 0; j < y_end - y + 1; j++) {
        for (int i = 0; i < (x_end - x + 1) / 8; i++) {
            EpdSendData(epd, image_buffer[i + j * (image_width / 8)]);
        }
    }
}

void EpdSetFrameMemoryPartial(Epd* epd, const unsigned char* image_buffer, int x, int y, int image_width, int image_height)
{
    int x_end;
    int y_end;
    
    EpdIfDigitalWriteRST(0);                //module reset
    DelayMs(2);
    EpdIfDigitalWriteRST(1);
    DelayMs(2);

    EpdSetLut(epd, WF_PARTIAL_1IN54_0);
    EpdSendCommand(epd, 0x37); 
    EpdSendData(epd, 0x00);  
    EpdSendData(epd, 0x00);  
    EpdSendData(epd, 0x00);  
    EpdSendData(epd, 0x00); 
    EpdSendData(epd, 0x00);  	
    EpdSendData(epd, 0x40);  
    EpdSendData(epd, 0x00);  
    EpdSendData(epd, 0x00);   
    EpdSendData(epd, 0x00);  
    EpdSendData(epd, 0x00);

    EpdSendCommand(epd, 0x3c);
    EpdSendData(epd, 0x80);

    EpdSendCommand(epd, 0x22); 
    EpdSendData(epd, 0xc0); 
    EpdSendCommand(epd, 0x20); 
    EpdWaitUntilIdle(epd);
    
    if (image_buffer == NULL || x < 0 || image_width < 0 || y < 0 || image_height < 0) {
        return;
    }
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    x &= 0xF8;
    image_width &= 0xF8;
    if (x + image_width >= epd->width) {
        x_end = epd->width - 1;
    } else {
        x_end = x + image_width - 1;
    }
    if (y + image_height >= epd->height) {
        y_end = epd->height - 1;
    } else {
        y_end = y + image_height - 1;
    }
    EpdSetMemoryArea(epd, x, y, x_end, y_end);
    EpdSetMemoryPointer(epd, x, y);
    EpdSendCommand(epd, 0x24);
    /* send the image data */
    for (int j = 0; j < y_end - y + 1; j++) {
        for (int i = 0; i < (x_end - x + 1) / 8; i++) {
            EpdSendData(epd, image_buffer[i + j * (image_width / 8)]);
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
void EpdSleep(Epd* epd)
{
    EpdSendCommand(epd, 0x10); //enter deep sleep
    EpdSendData(epd, 0x01);
    DelayMs(200);

    EpdIfDigitalWriteRST(0);
}
