#include <zephyr/kernel.h>
#include <stdlib.h>
#include "epd1in54_V2.h"

int main(void)
{
        Epd* epd;
        EpdLDirInit(epd);
        printk("After initr\n");
        EpdClear(epd);
        printk("e-Paper init and clear\n");
        EpdSleep(epd);
        printk("sleep\n");
        return 0;
}
