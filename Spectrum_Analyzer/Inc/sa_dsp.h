/*
 * sa_dsp.h
 *
 *  Created on:  17/10/2023
 *      Author: andre_koz
 */


#ifndef INC_SA_DSP_H_
#define INC_SA_DSP_H_


#include "stm32f4xx_hal.h"


#define I2S_BUFF_SIZE 1024
#define FFT_BUFF_SIZE (I2S_BUFF_SIZE / 2)
#define FFT_MAG_BUFF_SIZE (FFT_BUFF_SIZE / 2)


void audio_data_receive(void);
void audio_data_rx_callback(I2S_HandleTypeDef *hi2s);
void audio_data_rx_half_callback(I2S_HandleTypeDef *hi2s);

void fft_perform (void);
void fft_init (void);

void disp_sig_freq_dom (void);


#endif /* INC_SA_DSP_H_ */
