/*
 * metronome_it.c
 *
 *  Created on: 9/5/2023
 *      Author: andre_koz
 *     Comment: Use with HAL libraries.
 */

#include "stm32f4xx_hal.h"

#include "sa_dma.h"
#include "sa_it.h"


void SysTick_Handler(void)
{
	HAL_IncTick();
}


void DMA2_Stream0_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_spi4_rx);
}
