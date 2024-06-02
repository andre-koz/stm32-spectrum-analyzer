/*
 * sa_spi.c
 *
 *  Created on: 11/10/2023
 *      Author: andre_koz
 *     Comment: Use with HAL libraries.
 */


#include "stm32f4xx_hal.h"

#include "sa_common.h"
#include "sa_spi.h"


SPI_HandleTypeDef hspi1;


void spi1_init (void)
{
	GPIO_InitTypeDef GPIO_spi1_struct = {0};

	__HAL_RCC_SPI1_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_spi1_struct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIO_spi1_struct.Mode = GPIO_MODE_AF_PP;
	GPIO_spi1_struct.Pull = GPIO_NOPULL;
	GPIO_spi1_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_spi1_struct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_spi1_struct);

	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_1LINE;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;

	if(HAL_SPI_Init(&hspi1) != HAL_OK) {
		error_handler();
	}
}
