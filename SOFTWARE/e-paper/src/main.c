#include <zephyr/kernel.h>
#include <stdlib.h>
#include "epd1in54_V2.h"
#include "epdpaint.h"
#include "imagedata.h"
#include "epdif.h"
// #include "fonts.h"
#define WIDTH 200
#define HEIGHT 200

int main(void)
{
    // if (EpdIfInit() != 0) {
    //     return -1;
    // }
    //     while(1){
    //             EpdIfSpiTransfer(0x55);
    //     }
        
        EpdLDirInit();
        printk("After init\n");
        EpdClear();
        printk("e-Paper init and clear\n");
        printk("e-Paper show pic\n");
        EpdHDirInit();
        EpdDisplayPartBaseImage(IMAGE_DATA);
        EpdSleep();
        printk("sleep\n");
        return 0;
}
