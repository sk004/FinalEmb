
#include <stdio.h>
#include <stdint.h>
#include "PIO_LED.h"
#include "PIO_BUTTON.h"
#include <time.h>
#include "CSpider.h"
#include "CSpiderLeg.h"
#include <iostream>

int main(int argc, char *argv[]){

    CPIO_LED LED_PIO;
    CPIO_BUTTON BUTTON_PIO;
    CSpider Spider;
    
    printf("Spider Init & Standup\r\n");
    if (!Spider.Init())
    {
        printf("Spilder Init failed\r\n");
    }
    else
    {
        if (!Spider.Standup())
            printf("Spilder Standup failed\r\n");
    }

    Spider.SetSpeed(50);

    printf("Main Funtionality\n");
    while(1)
    {

        //if (old_buttons != buttons)
        //{

            // Could be good if we implement this in a separate thread as
            // we can not stop the spider (for example pressing KEY1) until
            // the all the following lines are executed.
            if ((BUTTON_PIO.GetBUTTON() & 0x01)== 0) //KEY0
            {
                Spider.MoveForward(10);
                //Spider.RotatelLeft(10);
                //Spider.MoveForward(10); 
            }

            if ((BUTTON_PIO.GetBUTTON() & 0x02)== 0) //KEY1
            {
                return 0; //Key 1 Not implemented yet... Just exit
            }
        //}
    }
return 0;
}
