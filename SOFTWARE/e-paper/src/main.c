#include <zephyr/kernel.h>
#include <stdlib.h>
#include "epd1in54_V2.h"
#include "epdpaint.h"
#include "imagedata.h"
#include "epdif.h"
// #include "fonts.h"

int main(void)
{       
        printk("In main\n");
        uint8_t image[800] = {0xff};
        struct Paint paint;
        paint.image = image;
        
        EpdLDirInit();
        printk("After init\n");
        EpdClear();    
        k_msleep(2000);
                PaintClear(&paint); 
        PaintSetImage(&paint, image);
        PaintSetWidth(&paint, 200);
        PaintSetHeight(&paint, 24);
        PaintSetRotate(&paint, 0);
        printf("Paint initialized: width=%d, height=%d, rotate=%d\n", paint.width, paint.height, paint.rotate);
        PaintDrawStringAt(&paint,30, 4, "Hello world!", &Font16);
        EpdSetFrameMemory(PaintGetImage(&paint), 0, 10, PaintGetWidth(&paint), PaintGetHeight(&paint));
        EpdDisplayFrame();
        k_msleep(2000);
        EpdSleep();

//Increment
//         EpdHDirInit();
//    PaintSetWidth(&paint, 50);
//   PaintSetHeight(&paint, 60);
//   PaintClear(&paint);
//         int i = 0;
//   char str[10][10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
//   for (i = 0; i < 10; i++) {
//     PaintClear(&paint);
//     PaintDrawStringAt(&paint,10, 10, str[i], &Font24);
//     EpdSetFrameMemoryPartial(PaintGetImage(&paint), 80, 70, PaintGetWidth(&paint), PaintGetHeight(&paint)); //Refresh part display
//     EpdDisplayPartFrame();
//     k_msleep(1000);
//   }
        
        

        // EpdHDirInit();
        // EpdDisplayPartBaseImage(papi);
        // printk("e-Paper show pic\n");
        // k_msleep(4000);
        // EpdHDirInit();
        // EpdClear();
        // k_msleep(1000);
        EpdSleep();
        printk("sleep\n");
        return 0;
}
