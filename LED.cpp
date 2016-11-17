#include <iostream>
#include <stdio.h>
#include "terasic_os.h"
#include <chrono>
#include <thread>
#include <stdint.h>
//Soohwan Kim (ID: 010655915)
//Joel Garay (ID: 010639763)

#include "PIO_LED.h"
#include "PIO_BUTTON.h"
#include <time.h>

using namespace std;

void shiftLED()
{
	unsigned int rate = OS_TicksPerSecond()/8;
	unsigned int led = 1;
	while((BUTTON_PIO.GetBUTTON() & 0x01) != 0)
	{
		LED_PIO.SetLED(led);
		unsigned int limit = OS_GetTickCount() + rate;
		while(OS_GetTickCount() < limit)
		{
			limit = limit;
		}
		led = led << 1;
		if(led >= 256)
		led = 1;
	}
}

void blinkLED()
{
	unsigned int rate = OS_TicksPerSecond()/16;
	unsigned int led = 255;
	while(((BUTTON_PIO.GetBUTTON() & 0x01) != 0) || ((BUTTON_PIO.GetBUTTON() & 0x02) != 0))
	{
		LED_PIO.SetLED(led);
		unsigned int limit = OS_GetTickCount() + rate;
		while(OS_GetTickCount() < limit)
		{
			limit = limit;
		}
		if(led = 255)
			led = 0;
		else
			led = 255;
	}
}



int main(int argc, char *argv[]){

	unsigned int led = 1;
	unsigned int hertz = 8;
	unsigned int rate;
    CPIO_LED LED_PIO;
    CPIO_BUTTON BUTTON_PIO;
		
	while (((BUTTON_PIO.GetBUTTON() & 0x01) != 0) || ((BUTTON_PIO.GetBUTTON() & 0x02) != 0))
	{
		if((BUTTON_PIO.GetBUTTON() & 0x01) == 0)
			hertz -= 1;
		else if((BUTTON_PIO.GetBUTTON() & 0x02) == 0)
			hertz += 1;
		if(hertz > 16)
			hertz = 16;
		else if(hertz < 1)
			hertz = 1;
		LED_PIO.SetLED(led);
		rate = OS_TicksPerSecond()/hertz;
		unsigned int limit = OS_GetTickCount() + rate;
		while(OS_GetTickCount() < limit)
		{
			limit = limit;
		}
		led = led << 1;
		if(led >= 256)
			led = 1;
	}
	return 0;
}	
