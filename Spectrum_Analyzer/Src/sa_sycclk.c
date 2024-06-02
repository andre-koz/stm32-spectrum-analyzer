/*
 * sa_sycclk.c
 *
 *  Created on: 9/5/2023
 *      Author: andre_koz
 *     Comment: Use with HAL libraries.
 */


#include <string.h>
#include "stm32f4xx_hal.h"

#include "sa_common.h"
#include "sa_sysclk.h"


void sysclk_hse_init(void)
{
	RCC_OscInitTypeDef RCC_osc_struct = {0};
	RCC_ClkInitTypeDef RCC_clk_struct = {0};

	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	RCC_osc_struct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_osc_struct.HSEState = RCC_HSE_BYPASS;
	RCC_osc_struct.PLL.PLLState = RCC_PLL_ON;
	RCC_osc_struct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_osc_struct.PLL.PLLM = 4;
	RCC_osc_struct.PLL.PLLN = 100;
	RCC_osc_struct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_osc_struct.PLL.PLLQ = 4;

	RCC_clk_struct.ClockType = RCC_CLOCKTYPE_SYSCLK | \
							   RCC_CLOCKTYPE_HCLK 	| \
							   RCC_CLOCKTYPE_PCLK1 	| \
							   RCC_CLOCKTYPE_PCLK2;
	RCC_clk_struct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_clk_struct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_clk_struct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_clk_struct.APB2CLKDivider = RCC_HCLK_DIV1; //div 1 before

	if(HAL_RCC_OscConfig(&RCC_osc_struct) != HAL_OK) {
		error_handler();
	}

	if(HAL_RCC_ClockConfig(&RCC_clk_struct, FLASH_LATENCY_3) != HAL_OK) {
		error_handler();
	}

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	__HAL_RCC_HSI_DISABLE();
}

