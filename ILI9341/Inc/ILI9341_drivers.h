/*
 * ILI9341.h
 *
 *  Created on: 11/10/2023
 *      Author: andre_koz
 *     Comment: Use with HAL libraries.
 */

#ifndef INC_ILI9341_DRIVERS_H_
#define INC_ILI9341_DRIVERS_H_


#include "fonts.h"
#include <stdbool.h>


#define ILI9341_WIDTH  		320
#define ILI9341_HEIGHT 		240
#define ILI9341_MADCTL	 	(0x40 | 0x80 | 0x20 | 0x08)


#define ILI9341_RESX_PIN       	GPIO_PIN_7
#define ILI9341_RESX_PORT 		GPIOC
#define ILI9341_DCX_PIN        	GPIO_PIN_9
#define ILI9341_DCX_PORT	  	GPIOA
#define ILI9341_CSX_PIN       	GPIO_PIN_6
#define ILI9341_CSX_PORT		GPIOB


#define	ILI9341_BLACK   		0x0000
#define ILI9341_MAGENTA 		0xF81F
#define ILI9341_YELLOW  		0xFFE0
#define	ILI9341_BLUE    		0x001F
#define	ILI9341_RED    	 		0xF800
#define	ILI9341_GREEN  		 	0x07E0
#define ILI9341_GREEN_500		0x0300
#define ILI9341_GREEN_100		0x0100
#define ILI9341_CYAN    		0x07FF
#define ILI9341_WHITE   		0xFFFF


typedef enum
{
	DIR_UP,
	DIR_DOWN,
	DIR_RIGHT,
	DIR_LEFT,
}DIRECTION_t;


void ILI9341_init(void);
void ILI9341_write_string(uint16_t x, uint16_t y, const char* str, font_t font, uint16_t color,
						  uint16_t bg_color);
void ILI9341_draw_rectangle_full(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
								 uint16_t color);
void ILI9341_draw_rectangle_empty(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
								  uint8_t thickness, uint16_t color);
void ILI9341_fill_screen(uint16_t color);
void ILI9341_draw_pixel(uint16_t x, uint16_t y, uint16_t color);

#endif /* INC_ILI9341_DRIVERS_H_ */
