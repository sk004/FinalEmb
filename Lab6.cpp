//Miguel De Lora Velasquez
//medelora@uark.edu


#include <stdio.h>
#include <stdint.h>
#include "terasic_os.h"
#include "PIO_LED.h"
#include "PIO_BUTTON.h"
#include <time.h>


int main(int argc, char *argv[]){

    CPIO_LED LED_PIO;
    CPIO_BUTTON BUTTON_PIO;

	uint32_t tickCount = OS_GetTickCount(); 
	int led = 1;
	int frequency = 8;

		int buttons;
		int prev_buttons;
		
	while((BUTTON_PIO.GetBUTTON() & 0x03) != 0) {

		
		prev_buttons = buttons;
		buttons = BUTTON_PIO.GetBUTTON();

			if ((buttons & 0x01) == 0) {
				if(buttons != prev_buttons) {
					frequency -= 1;
					if(frequency < 1) {
						frequency = 1;
					}
				}

			}
	
			if ((buttons & 0x02) == 0) {
				if(buttons != prev_buttons) {

					frequency += 1;
					if(frequency > 16) {
						frequency = 16;
					}
				}
			}

		if(OS_GetTickCount()-tickCount > OS_TicksPerSecond()/frequency) {
			tickCount = OS_GetTickCount(); 
			led = led << 1;
			if(led > 256) {
				led = 1;
			}
			LED_PIO.SetLED(led);
			//printf("Frequency : %d\n", frequency);
			
		}
	}


	return 0;
}	
