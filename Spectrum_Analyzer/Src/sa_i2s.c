/*
 * sa_i2s.c
 *
 *  Created on: 9/6/2023
 *      Author: andre_koz
 *     Comment: Use with HAL libraries.
 */


#include "sa_i2s.h"
#include "sa_common.h"
#include "sa_dma.h"
#include "sa_dsp.h"


I2S_HandleTypeDef hi2s4;


void i2s4_init(void)
{
	hi2s4.Instance = SPI4;
	hi2s4.Init.Mode = I2S_MODE_MASTER_RX;
	hi2s4.Init.Standard = I2S_STANDARD_PHILIPS;
	hi2s4.Init.DataFormat = I2S_DATAFORMAT_16B_EXTENDED;
	hi2s4.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
	hi2s4.Init.AudioFreq = I2S_AUDIOFREQ_16K; //check other values
	hi2s4.Init.CPOL = I2S_CPOL_LOW;
	hi2s4.Init.ClockSource = I2S_CLOCK_PLL;
	hi2s4.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;

	hi2s4.Lock = HAL_UNLOCKED;

	__HAL_RCC_SYSCFG_CLK_ENABLE();
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

	if(hi2s4.Instance==SPI4) {
		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
	    PeriphClkInitStruct.PLLI2S.PLLI2SN = 192;
	    PeriphClkInitStruct.PLLI2S.PLLI2SM = 8;
	    PeriphClkInitStruct.PLLI2S.PLLI2SR = 4;

	    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
	    	error_handler();
	    }

	    __HAL_RCC_SPI4_CLK_ENABLE();

	    __HAL_RCC_GPIOA_CLK_ENABLE();
	    __HAL_RCC_GPIOB_CLK_ENABLE();

	    /* I2S4 GPIO Configuration */
	    GPIO_InitStruct.Pin = GPIO_PIN_1;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	    GPIO_InitStruct.Alternate = GPIO_AF5_SPI4;
	    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	    GPIO_InitStruct.Alternate = GPIO_AF6_SPI4;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	    hdma_spi4_rx.Instance = DMA2_Stream0;
	    hdma_spi4_rx.Init.Channel = DMA_CHANNEL_4;
	    hdma_spi4_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	    hdma_spi4_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	    hdma_spi4_rx.Init.MemInc = DMA_MINC_ENABLE;
	    hdma_spi4_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	    hdma_spi4_rx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	    hdma_spi4_rx.Init.Mode = DMA_CIRCULAR;
	    hdma_spi4_rx.Init.Priority = DMA_PRIORITY_LOW;
	    hdma_spi4_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	    if (HAL_DMA_Init(&hdma_spi4_rx) != HAL_OK) {
	    	error_handler();
	    }

	    __HAL_LINKDMA(&hi2s4,hdmarx,hdma_spi4_rx);
	}

	hi2s4.State = HAL_I2S_STATE_BUSY;
	CLEAR_BIT(hi2s4.Instance->I2SCFGR, (SPI_I2SCFGR_CHLEN | SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CKPOL | \
	                                    SPI_I2SCFGR_I2SSTD | SPI_I2SCFGR_PCMSYNC | SPI_I2SCFGR_I2SCFG | \
	                                    SPI_I2SCFGR_I2SE | SPI_I2SCFGR_I2SMOD));
	hi2s4.Instance->I2SPR = 0x0002U;
	hi2s4.Instance->I2SPR = (uint32_t)((uint32_t)23 | (uint32_t)(256 | (uint32_t)hi2s4.Init.MCLKOutput));
	MODIFY_REG(hi2s4.Instance->I2SCFGR, (SPI_I2SCFGR_CHLEN | SPI_I2SCFGR_DATLEN | \
	                                     SPI_I2SCFGR_CKPOL | SPI_I2SCFGR_I2SSTD | \
	                                     SPI_I2SCFGR_PCMSYNC | SPI_I2SCFGR_I2SCFG | \
	                                     SPI_I2SCFGR_I2SE  | SPI_I2SCFGR_I2SMOD), \
	             	 	 	 	 	 	 (SPI_I2SCFGR_I2SMOD | hi2s4.Init.Mode | \
	             	 	 	 	 	 	 hi2s4.Init.Standard | hi2s4.Init.DataFormat | \
										 hi2s4.Init.CPOL));
	hi2s4.State     = HAL_I2S_STATE_READY;
}


/* Callback is called when the i2s data buffer is full. */
void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s)
{
	audio_data_rx_callback(hi2s);
}


/* Callback is called when the i2s data buffer is half full. */
void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
	audio_data_rx_half_callback(hi2s);
}
