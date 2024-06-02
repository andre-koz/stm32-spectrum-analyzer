/*
 * sa_display.c
 *
 *  Created on: 25/5/2024
 *      Author: andre_koz
 *     Comment: Use with HAL libraries.
 */


#include "stm32f4xx_hal.h"
#include "ILI9341_drivers.h"


/* Display the device's home screen. */
void display_init(void)
{
	HAL_Delay(3000);
	ILI9341_fill_screen(ILI9341_GREEN_100);
    HAL_Delay(1000);

    ILI9341_write_string(41, 5+0*18, "SPECTRUM ANALYZER 3000", Font_11x18, ILI9341_WHITE, ILI9341_GREEN_100);
    HAL_Delay(5);
	ILI9341_draw_rectangle_empty(31, 57, 260, 154, 2, ILI9341_GREEN_500);
	ILI9341_draw_rectangle_full(31, 211, 2, 3, ILI9341_GREEN_500);
	ILI9341_draw_rectangle_full(96, 211, 2, 3, ILI9341_GREEN_500);
	ILI9341_draw_rectangle_full(161, 211, 2, 3, ILI9341_GREEN_500);
	ILI9341_draw_rectangle_full(226, 211, 2, 3, ILI9341_GREEN_500);
	ILI9341_draw_rectangle_full(289, 211, 2, 3, ILI9341_GREEN_500);
	HAL_Delay(5);
	ILI9341_write_string(27, 216, "0", Font_11x18, ILI9341_WHITE, ILI9341_GREEN_100);
	ILI9341_write_string(241, 216, " 8000Hz", Font_11x18, ILI9341_WHITE, ILI9341_GREEN_100);
}

