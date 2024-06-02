/*
 * sa_common.c
 *
 *  Created on: 9/2/2023
 *      Author: andre_koz
 *     Comment: Use with HAL libraries.
 */


#include "sa_common.h"

#include "stm32f4xx.h"
#include <math.h>


void FPU_enable (void)
{
	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));
}


float32_t int16_to_float32 (int16_t input_val)
{
	return ((float32_t)input_val / 32768.0f);
}


uint8_t float32_to_uint8 (float32_t input_val)
{
	return ((uint8_t)round(input_val));
}


void error_handler(void)
{
	while (1);
}
