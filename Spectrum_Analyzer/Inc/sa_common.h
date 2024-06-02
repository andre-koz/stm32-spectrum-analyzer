/*
 * sa_common.h
 *
 *  Created on: 9/2/2023
 *      Author: andre_koz
 *     Comment: Use with HAL libraries.
 */

#ifndef INC_SA_COMMON_H_
#define INC_SA_COMMON_H_


#include <stdint.h>


typedef float float32_t;


void FPU_enable (void);
void error_handler(void);
float32_t int16_to_float32 (int16_t input_val);
uint8_t float32_to_uint8 (float32_t input_val);
void set_multiplier_value (uint8_t mltplr);


#endif /* INC_SA_COMMON_H_ */
