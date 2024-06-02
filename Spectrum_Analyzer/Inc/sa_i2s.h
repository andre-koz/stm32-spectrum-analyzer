/*
 * sa_i2s.h
 *
 *  Created on: 9/6/2023
 *      Author: andre_koz
 *     Comment: Use with HAL libraries.
 */

#ifndef INC_SA_I2S_H_
#define INC_SA_I2S_H_


#include "stm32f4xx_hal.h"


extern I2S_HandleTypeDef hi2s4;


void i2s4_init(void);

void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s);
void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s);


#endif /* INC_SA_I2S_H_ */
