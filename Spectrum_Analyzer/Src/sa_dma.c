/*
 * sa_dma.c
 *
 *  Created on: 9/6/2023
 *      Author: andre_koz
 *     Comment: Use with HAL libraries.
 */


#include "stm32f4xx_hal.h"

#include "sa_it.h"


DMA_HandleTypeDef hdma_spi4_rx;


/* DMA is used for I2S data transmission. */
void dma_init(void)
{
	  __HAL_RCC_DMA2_CLK_ENABLE();

	  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
	  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
}
