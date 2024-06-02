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
    0x22, 0x17, 0x41, 0x0, 0x32, 0x20
};

// waveform partial refresh(fast)
uint8_t WF_PARTIAL_1IN54_0[159] = {
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

void EpdDestructor()
{
    // Destructor
}

void EpdConstructor()
{
    // 200 = EPD_WIDTH;
    // 200 = EPD_HEIGHT;
}

/**
 *  @brief: basic function for sending commands
 */
void EpdSendCommand(uint8_t command)
{
    EpdIfDigitalWriteDC(0);
    // EpdWaitUntilIdle();
    EpdIfSpiTransfer(command);
}

/**
 *  @brief: basic function for sending data
 */
void EpdSendData(uint8_t data)
{
    EpdIfDigitalWriteDC(1);
    EpdIfSpiTransfer(data);
}

/**
 *  @brief: Wait until the busy_pin goes HIGH
 */
void EpdWaitUntilIdle()
{
    while(EpdIfDigitalRead() == 1) {      //LOW: idle, HIGH: busy
        DelayMs(100);
    }
    DelayMs(200);
}

void EpdLut(uint8_t* lut)
{
    EpdSendCommand(0x32);
    for(uint8_t i = 0; i < 153; i++)
        EpdSendData(lut[i]);
    EpdWaitUntilIdle();
}

void EpdSetLut(uint8_t* lut)
{
    EpdLut(lut);
    
    EpdSendCommand(0x3f);
    EpdSendData(lut[153]);
    
    EpdSendCommand(0x03);
    EpdSendData(lut[154]);
    
    EpdSendCommand(0x04);
    EpdSendData( lut[155]);
    EpdSendData( lut[156]);
    EpdSendData( lut[157]);
    
    EpdSendCommand(0x2c);
    EpdSendData(lut[158]);
}

// High Direction
int EpdHDirInit()
{
    /* this calls the peripheral hardware interface, see epdif */
    if (EpdIfInit() != 0) {
        return -1;
    }
    /* EPD hardware init start */
    EpdReset();

    EpdWaitUntilIdle();
    EpdSendCommand(0x12);  //SWRESET
    EpdWaitUntilIdle();

    EpdSendCommand(0x01); //Driver output control
    EpdSendData(0xC7);
    EpdSendData(0x00);
    EpdSendData(0x01);

    EpdSendCommand(0x11); //data entry mode
    EpdSendData(0x01);

    EpdSendCommand(0x44); //set Ram-X address start/end position
    EpdSendData(0x00);
    EpdSendData(0x18);    //0x0C-->(18+1)*8=200

    EpdSendCommand(0x45); //set Ram-Y address start/end position
    EpdSendData(0xC7);   //0xC7-->(199+1)=200
    EpdSendData(0x00);
    EpdSendData(0x00);
    EpdSendData(0x00);

    EpdSendCommand(0x3C); //BorderWavefrom
    EpdSendData(0x01);

    EpdSendCommand(0x18);
    EpdSendData(0x80);

    EpdSendCommand(0x22); // //Enable clock signal.
    EpdSendData(0xB1);
    EpdSendCommand(0x20);
    EpdWaitUntilIdle();


    EpdSendCommand(0x4E);   // set RAM x address count to 0;
    EpdSendData(0x00);
    EpdSendCommand(0x4F);   // set RAM y address count to 0X199;
    EpdSendData(0xC7);
    EpdSendData(0x00);
    EpdWaitUntilIdle();

    EpdSetLut(WF_Full_1IN54);
    /* EPD hardware init end */

    return 0;
}

// Low Direction
int EpdLDirInit()
{
    /* this calls the peripheral hardware interface, see epdif */
    if (EpdIfInit() != 0) {
        return -1;
    }
    printk("a");
    /* EPD hardware init start */
    EpdReset();
    printk("b");
    EpdWaitUntilIdle();
    printk("c");
    EpdSendCommand(0x12);  //SWRESET
    EpdWaitUntilIdle();

    EpdSendCommand(0x01); //Driver output control
    EpdSendData(0xC7);
    EpdSendData(0x00);
    EpdSendData(0x00);

    EpdSendCommand(0x11); //data entry mode
    EpdSendData(0x03);

    EpdSendCommand(0x44);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    EpdSendData((0 >> 3) & 0xFF);
    EpdSendData((199 >> 3) & 0xFF);
    EpdSendCommand(0x45);
    EpdSendData(0 & 0xFF);
    EpdSendData((0 >> 8) & 0xFF);
    EpdSendData(199 & 0xFF);
    EpdSendData((199 >> 8) & 0xFF);

    EpdSendCommand(0x3C); //BorderWavefrom
    EpdSendData(0x01);

    EpdSendCommand(0x18);
    EpdSendData(0x80);

    EpdSendCommand(0x22); // //Load Temperature and waveform setting.
    EpdSendData(0xB1);
    EpdSendCommand(0x20);

    EpdSendCommand(0x4E);   // set RAM x address count to 0;
    EpdSendData(0x00);
    EpdSendCommand(0x4F);   // set RAM y address count to 0X199;
    EpdSendData(0xC7);
    EpdSendData(0x00);
    EpdWaitUntilIdle();

    EpdSetLut(WF_Full_1IN54);
    /* EPD hardware init end */

    return 0;
}


/**
 *  @brief: module reset.
 *          often used to awaken the module in deep sleep,
 *          see Epd::Sleep();
 */
void EpdReset()
{
    // EpdIfDigitalWriteRST(1);
    // DelayMs(20);
    EpdIfDigitalWriteRST(0);                //module reset
    DelayMs(10);
    EpdIfDigitalWriteRST(1);
    DelayMs(20);
}

void EpdClear()
{
    int w, h;
    w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    h = EPD_HEIGHT;
 
    EpdSendCommand(0x24);
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            EpdSendData(0xff);
        }
    }
    EpdSendCommand(0x26);
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            EpdSendData(0xff);
        }
    }
    //DISPLAY REFRESH
    EpdDisplayFrame();
}

void EpdDisplay(uint8_t* frame_buffer)
{
    int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    int h = EPD_HEIGHT;

    if (frame_buffer != NULL) {
        EpdSendCommand(0x24);
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                EpdSendData( frame_buffer[i + j * w]);
            }
        }
    }

    //DISPLAY REFRESH
    EpdDisplayFrame();
}

void EpdDisplayPartBaseImage(uint8_t* frame_buffer)
{
    int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    int h = EPD_HEIGHT;

    if (frame_buffer != NULL) {
        EpdSendCommand(0x24);
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                EpdSendData(frame_buffer[i + j * w]);
            }
        }

        EpdSendCommand( 0x26);
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                EpdSendData(frame_buffer[i + j * w]);
            }
        }
    }

    //DISPLAY REFRESH
    EpdDisplayFrame();
}

void EpdDisplayPartBaseWhiteImage()
{
    int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    int h = EPD_HEIGHT;

    EpdSendCommand(0x24);
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            EpdSendData(0xff);
        }
    }

    EpdSendCommand(0x26);
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            EpdSendData(0xff);
        }
    }

    //DISPLAY REFRESH
    EpdDisplayFrame();
}

void EpdDisplayPart(uint8_t* frame_buffer)
{
    int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    int h = EPD_HEIGHT;

    if (frame_buffer != NULL) {
        EpdSendCommand( 0x24);
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                EpdSendData( frame_buffer[i + j * w]);
            }
        }
    }

    //DISPLAY REFRESH
    EpdDisplayPartFrame();
}


/**
 *  @brief: private function to specify the memory area for data R/W
 */
void EpdSetMemoryArea(int x_start, int y_start, int x_end, int y_end)
{
    EpdSendCommand(0x44);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    EpdSendData( (x_start >> 3) & 0xFF);
    EpdSendData( (x_end >> 3) & 0xFF);
    EpdSendCommand( 0x45);
    EpdSendData( y_start & 0xFF);
    EpdSendData( (y_start >> 8) & 0xFF);
    EpdSendData( y_end & 0xFF);
    EpdSendData( (y_end >> 8) & 0xFF);
}

/**
 *  @brief: private function to specify the start point for data R/W
 */
void EpdSetMemoryPointer(int x, int y)
{
    EpdSendCommand(0x4e);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    EpdSendData((x >> 3) & 0xFF);
    EpdSendCommand(0x4F);
    EpdSendData(y & 0xFF);
    EpdSendData((y >> 8) & 0xFF);
    EpdWaitUntilIdle();
}


/**
 *  @brief: update the display
 *          there are 2 memory areas embedded in the e-paper display
 *          but once this function is called,
 *          the the next action of SetFrameMemory or ClearFrame will
 *          set the other memory area.
 */
void EpdDisplayFrame()
{
    //DISPLAY REFRESH
    EpdSendCommand(0x22);
    EpdSendData(0xc7);
    EpdSendCommand(0x20);
    EpdWaitUntilIdle();

}

void EpdDisplayPartFrame()
{
    EpdSendCommand( 0x22);
    EpdSendData( 0xcF);
    EpdSendCommand( 0x20);
    EpdWaitUntilIdle();
}


void EpdSetFrameMemory(uint8_t* image_buffer, int x, int y, int image_width, int image_height)
{
    int x_end;
    int y_end;
    
    EpdIfDigitalWriteRST(0);                //module reset
    DelayMs(2);
    EpdIfDigitalWriteRST(1);
    DelayMs(2);
    EpdSendCommand(0x3c);
    EpdSendData(0x80);

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
    EpdSetMemoryArea( x, y, x_end, y_end);
    EpdSetMemoryPointer( x, y);
    EpdSendCommand( 0x24);
    /* send the image data */
    for (int j = 0; j < y_end - y + 1; j++) {
        for (int i = 0; i < (x_end - x + 1) / 8; i++) {
            EpdSendData( image_buffer[i + j * (image_width / 8)]);
        }
    }
}

void EpdSetFrameMemoryPartial(uint8_t* image_buffer, int x, int y, int image_width, int image_height)
{
    int x_end;
    int y_end;
    
    EpdIfDigitalWriteRST(0);                //module reset
    DelayMs(2);
    EpdIfDigitalWriteRST(1);
    DelayMs(2);

    EpdSetLut( WF_PARTIAL_1IN54_0);
    EpdSendCommand( 0x37); 
    EpdSendData( 0x00);  
    EpdSendData( 0x00);  
    EpdSendData( 0x00);  
    EpdSendData( 0x00); 
    EpdSendData( 0x00);  	
    EpdSendData( 0x40);  
    EpdSendData( 0x00);  
    EpdSendData( 0x00);   
    EpdSendData( 0x00);  
    EpdSendData( 0x00);

    EpdSendCommand( 0x3c);
    EpdSendData( 0x80);

    EpdSendCommand( 0x22); 
    EpdSendData( 0xc0); 
    EpdSendCommand( 0x20); 
    EpdWaitUntilIdle();
    
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
    EpdSetMemoryArea( x, y, x_end, y_end);
    EpdSetMemoryPointer( x, y);
    EpdSendCommand( 0x24);
    /* send the image data */
    for (int j = 0; j < y_end - y + 1; j++) {
        for (int i = 0; i < (x_end - x + 1) / 8; i++) {
            EpdSendData( image_buffer[i + j * (image_width / 8)]);
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
void EpdSleep()
{
    EpdSendCommand(0x10); //enter deep sleep
    EpdSendData(0x01);
    DelayMs(200);

    EpdIfDigitalWriteRST(0);
}
