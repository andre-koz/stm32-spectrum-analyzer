/*
 * sa_dsp.c
 *
 *  Created on: 17/10/2023
 *      Author: andre_koz
 *     Comment: Use with HAL libraries.
 */


#include "sa_dsp.h"

#include <ILI9341_drivers.h>
#include <stdlib.h>
#include <string.h>
#include "arm_math.h"

#include "sa_common.h"
#include "sa_i2s.h"


arm_rfft_fast_instance_f32 hFFT;

int16_t i2s_buffer[I2S_BUFF_SIZE];
float32_t signal_mean_out;
float32_t fft_buff_in[FFT_BUFF_SIZE];
float32_t fft_buff_out[FFT_BUFF_SIZE];
float32_t fft_mag_buff_out[FFT_MAG_BUFF_SIZE];

static volatile int16_t *in_buff_ptr;
static volatile float32_t *out_buff_ptr = fft_buff_in;

uint8_t fft_flag = 0;
uint8_t data_ready_flag = 0;


static void data_process (void);


/* Initialization function for the floating-point real FFT. */
void fft_init (void)
{
	arm_rfft_fast_init_f32(&hFFT, FFT_BUFF_SIZE);
}


void fft_perform (void)
{
	if(data_ready_flag) {
		data_process();
		data_ready_flag = 0;
	}
}

/* Transform the signal from the time domain to the frequency domain.
   In order to reduce latency problems, double buffering is used. */
static void data_process (void)
{
	static int16_t fft_counter = 0;

	for(uint16_t i = 0; i < (I2S_BUFF_SIZE / 2); i += 2) {
		out_buff_ptr[i/2] = int16_to_float32(in_buff_ptr[i]);
		fft_counter ++;
		if((fft_counter) == FFT_BUFF_SIZE) {
			arm_mean_f32(fft_buff_in, FFT_BUFF_SIZE, &signal_mean_out);
			for(uint16_t j = 0; j < FFT_BUFF_SIZE; j++) {
				fft_buff_in[j] = fft_buff_in[j] - signal_mean_out;
			}
			arm_rfft_fast_f32(&hFFT, fft_buff_in, fft_buff_out, 0);
			arm_cmplx_mag_f32(fft_buff_out, fft_mag_buff_out, FFT_MAG_BUFF_SIZE);
			fft_flag = 1;
			fft_counter = 0;
		}
	}
}


void audio_data_receive(void)
{
	HAL_I2S_Receive_DMA(&hi2s4, (uint16_t *)i2s_buffer, sizeof(i2s_buffer)/2);
}


/* Function called in callback when the i2s data buffer is full. */
void audio_data_rx_callback(I2S_HandleTypeDef *hi2s)
{
	in_buff_ptr = &i2s_buffer[I2S_BUFF_SIZE / 2];
	out_buff_ptr = &fft_buff_in[FFT_BUFF_SIZE / 2];

	data_ready_flag = 1;
}


/* Function called in callback when the i2s data buffer is full. */
void audio_data_rx_half_callback(I2S_HandleTypeDef *hi2s)
{
	in_buff_ptr = &i2s_buffer[0];
	out_buff_ptr = &fft_buff_in[0];

	data_ready_flag = 1;
}


/* Display the signal waveform in the frequency domain.
   x poles start at 33; y poles start at 216 */
void disp_sig_freq_dom (void)
{
	static float32_t fft_mag_buff_out_cpy[FFT_MAG_BUFF_SIZE];

	if(fft_flag == 1) {
		// clear previous
		for(uint16_t i = 0; i < FFT_MAG_BUFF_SIZE; i++) {
			uint8_t pole_height = float32_to_uint8(fft_mag_buff_out_cpy[i]);
			if(pole_height > 150)
				pole_height = 150;
			for(uint8_t j = 0; j < pole_height; j++ ) {
				ILI9341_draw_pixel((33 + i), (208 - j), ILI9341_GREEN_100);
			}
		}

		for(uint16_t i = 0; i < FFT_MAG_BUFF_SIZE; i++) {
			uint8_t pole_height = float32_to_uint8(fft_mag_buff_out[i]);
			if(pole_height > 150)
				pole_height = 150;
			for(uint8_t j = 0; j < pole_height; j++ ) {
				ILI9341_draw_pixel((33 + i), (208 - j), ILI9341_WHITE);
			}
		}
		memcpy(fft_mag_buff_out_cpy, fft_mag_buff_out, sizeof(fft_mag_buff_out));
		fft_flag = 0;
	}

}
