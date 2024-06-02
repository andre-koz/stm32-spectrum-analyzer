/*
 * sa_gpio.c
 *
 *  Created on: 9/1/2023
 *      Author: andre_koz
 *     Comment: Use with HAL libraries.
 */

#include "stm32f4xx_hal.h"


#include "sa_gpio.h"
#include "sa_bsp.h"


void gpio_init (void)
{
	GPIO_InitTypeDef GPIO_ili9341_rst_struct = {0};

	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_ili9341_rst_struct.Pin = GPIO_PIN_7;
	GPIO_ili9341_rst_struct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_ili9341_rst_struct.Pull = GPIO_NOPULL;
	GPIO_ili9341_rst_struct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_ili9341_rst_struct);


	GPIO_InitTypeDef GPIO_ili9341_dc_struct = {0};

	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_ili9341_dc_struct.Pin = GPIO_PIN_9;
	GPIO_ili9341_dc_struct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_ili9341_dc_struct.Pull = GPIO_NOPULL;
	GPIO_ili9341_dc_struct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_ili9341_dc_struct);


	GPIO_InitTypeDef GPIO_ili9341_cs_struct = {0};

	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_ili9341_cs_struct.Pin = GPIO_PIN_6;
	GPIO_ili9341_cs_struct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_ili9341_cs_struct.Pull = GPIO_NOPULL;
	GPIO_ili9341_cs_struct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_ili9341_cs_struct);
}
