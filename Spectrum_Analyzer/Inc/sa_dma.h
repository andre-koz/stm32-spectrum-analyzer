/*
 * sa_dma.h
 *
 *  Created on: 9/6/2023
 *      Author: andre_koz
 *     Comment: Use with HAL libraries.
 */

#ifndef INC_SA_DMA_H_
#define INC_SA_DMA_H_


#include "stm32f4xx_hal.h"


extern DMA_HandleTypeDef hdma_spi4_rx;


void dma_init(void);


#endif /* INC_SA_DMA_H_ */
