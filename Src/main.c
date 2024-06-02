/*
 * main.c
 *
 *      Author: andre_koz
 *     Comment: Use with HAL libraries.
 */


#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "stm32f4xx_hal.h"

#include "sa_dsp.h"
#include "sa_init.h"


int main(void)
{
	HAL_Init();
	spec_analyzer_init();

	audio_data_receive();

    while(1)
    {
    	fft_perform();
    	disp_sig_freq_dom();
    }
}



