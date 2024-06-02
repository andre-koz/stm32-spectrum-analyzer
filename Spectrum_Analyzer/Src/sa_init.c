/*
 * sa_init.c
 *
 *  Created on: 9/1/2023
 *      Author: andre_koz
 *     Comment: Use with HAL libraries.
 */


#include "sa_init.h"

#include <ILI9341_drivers.h>

#include "sa_common.h"
#include "sa_display.h"
#include "sa_dma.h"
#include "sa_dsp.h"
#include "sa_gpio.h"
#include "sa_i2s.h"
#include "sa_spi.h"
#include "sa_sysclk.h"


void spec_analyzer_init(void)
{
	FPU_enable();

	sysclk_hse_init();
	gpio_init();
	dma_init();
	i2s4_init();
	spi1_init();
	ILI9341_init();

	display_init();
	fft_init();
}

