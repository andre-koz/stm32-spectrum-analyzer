/*
 * ILI9341.c
 *
 *  Created on: 11/10/2023
 *      Author: andre_koz
 *     Comment: Use with HAL libraries.
 */


#include <ILI9341_drivers.h>
#include "stm32f4xx_hal.h"

#include "sa_spi.h"


static void ILI9341_select(void);
static void ILI9341_unselect(void);
static void ILI9341_data_select(void);
static void ILI9341_command_select(void);
static void ILI9341_reset(void);
static void ILI9341_write_command(uint8_t cmd);
static void ILI9341_write_data(uint8_t* buff, size_t buff_size);
static void ILI9341_set_frame_mem_area(uint16_t sc, uint16_t sp, uint16_t ec, uint16_t ep);
static void ILI9341_write_char(uint16_t x, uint16_t y, char ch, font_t font, uint16_t color, uint16_t bgcolor);


/* Initialize the device. */
void ILI9341_init(void)
{
	ILI9341_unselect();
    ILI9341_select();
    ILI9341_reset();

    /* Software reset */
    ILI9341_write_command(0x01);
    HAL_Delay(1000);

    /* Power control A */
    ILI9341_write_command(0xCB);
    uint8_t pwr_ctrl_A_data[] = {0x39, 0x2C, 0x00, 0x34, 0x02};
    ILI9341_write_data(pwr_ctrl_A_data, sizeof(pwr_ctrl_A_data));

    /* Power control B */
    ILI9341_write_command(0xCF);
    uint8_t pwr_ctrl_B_data[] = {0x00, 0xC1, 0x30};
    ILI9341_write_data(pwr_ctrl_B_data, sizeof(pwr_ctrl_B_data));

    /* Driver timing control A */
    ILI9341_write_command(0xE8);
    uint8_t drv_tim_ctrl_A_data[] = {0x85, 0x00, 0x78};
    ILI9341_write_data(drv_tim_ctrl_A_data, sizeof(drv_tim_ctrl_A_data));

    /* Driver timing control B */
    ILI9341_write_command(0xEA);
    uint8_t drv_tim_ctrl_B_data[] = {0x00, 0x00};
    ILI9341_write_data(drv_tim_ctrl_B_data, sizeof(drv_tim_ctrl_B_data));

    /* Power on sequence control */
    ILI9341_write_command(0xED);
    uint8_t pwr_on_seq_ctrl_data[] = {0x64, 0x03, 0x12, 0x81};
    ILI9341_write_data(pwr_on_seq_ctrl_data, sizeof(pwr_on_seq_ctrl_data));

    /* Pump ratio control */
    ILI9341_write_command(0xF7);
    uint8_t pmp_rto_ctrl_data[] = {0x20};
    ILI9341_write_data(pmp_rto_ctrl_data, sizeof(pmp_rto_ctrl_data));

    /* Power Control 1 */
    ILI9341_write_command(0xC0);
    uint8_t pwr_ctrl_1_data[] = {0x23};
    ILI9341_write_data(pwr_ctrl_1_data, sizeof(pwr_ctrl_1_data));

    /* Power Control 2 */
    ILI9341_write_command(0xC1);
    uint8_t pwr_ctrl_2_data[] = {0x10};
    ILI9341_write_data(pwr_ctrl_2_data, sizeof(pwr_ctrl_2_data));

    /* VCOM Control 1 */
    ILI9341_write_command(0xC5);
    uint8_t VCOM_ctrl_1_data[] = {0x3E, 0x28};
    ILI9341_write_data(VCOM_ctrl_1_data, sizeof(VCOM_ctrl_1_data));

    /* VCOM Control 2 */
    ILI9341_write_command(0xC7);
    uint8_t VCOM_ctrl_2_data[] = {0x86};
    ILI9341_write_data(VCOM_ctrl_2_data, sizeof(VCOM_ctrl_2_data));

    /* Memory access control (MADCTL) */
    ILI9341_write_command(0x36);
    uint8_t madctl1_data[] = { 0x48 };
    ILI9341_write_data(madctl1_data, sizeof(madctl1_data));

    /* Pixel format set (PIXSET) */
    ILI9341_write_command(0x3A);
    uint8_t pixset_data[] = {0x55};
    ILI9341_write_data(pixset_data, sizeof(pixset_data));

    /* Frame rate control (FRMCTR1) */
    ILI9341_write_command(0xB1);
    uint8_t frmctr1_data[] = {0x00, 0x18};
    ILI9341_write_data(frmctr1_data, sizeof(frmctr1_data));

    /* Display function control (DISCTRL) */
    ILI9341_write_command(0xB6);
    uint8_t disctrl_data[] = {0x08, 0x82, 0x27};
    ILI9341_write_data(disctrl_data, sizeof(disctrl_data));

    /* Enable 3G */
    ILI9341_write_command(0xF2);
    uint8_t en_3g_data[] = {0x00};
    ILI9341_write_data(en_3g_data, sizeof(en_3g_data));

    /* Gamma set (GAMSET) */
    ILI9341_write_command(0x26);
    uint8_t gamset_data[] = {0x01};
    ILI9341_write_data(gamset_data, sizeof(gamset_data));

    /* Positive gamma correction (PGAMCTRL) */
    ILI9341_write_command(0xE0);
    uint8_t pgamctrl_data[] = {0x0F, 0x31, 0x2B, 0x0C, 0x0E,
    						   0x08, 0x4E, 0xF1, 0x37, 0x07,
							   0x10, 0x03, 0x0E, 0x09, 0x00};
    ILI9341_write_data(pgamctrl_data, sizeof(pgamctrl_data));

    /* Negative gamma correction (NGAMCTRL) */
    ILI9341_write_command(0xE1);
    uint8_t ngamctrl_data[] = {0x00, 0x0E, 0x14, 0x03, 0x11,
    						   0x07, 0x31, 0xC1, 0x48, 0x08,
							   0x0F, 0x0C, 0x31, 0x36, 0x0F};
    ILI9341_write_data(ngamctrl_data, sizeof(ngamctrl_data));

    /* Memory access control (MADCTL) */
    ILI9341_write_command(0x36);
    uint8_t madctl2_data[] = {ILI9341_MADCTL};
    ILI9341_write_data(madctl2_data, sizeof(madctl2_data));

    /* Sleep out (SLPOUT) */
    ILI9341_write_command(0x11);
    HAL_Delay(120);

    /* Display ON (DISPON) */
    ILI9341_write_command(0x29);

    ILI9341_unselect();
}


/* Set ILI9341 CSX pin "low" to select the device. */
static void ILI9341_select(void)
{
    HAL_GPIO_WritePin(ILI9341_CSX_PORT, ILI9341_CSX_PIN, GPIO_PIN_RESET);
}

/* Set ILI9341 CSX pin "high" to unselect the device. */
static void ILI9341_unselect(void)
{
    HAL_GPIO_WritePin(ILI9341_CSX_PORT, ILI9341_CSX_PIN, GPIO_PIN_SET);
}

/* Set ILI9341 DCX pin "high" to enter the "data mode". */
static void ILI9341_data_select(void)
{
	HAL_GPIO_WritePin(ILI9341_DCX_PORT, ILI9341_DCX_PIN, GPIO_PIN_SET);
}

/* Set ILI9341 DCX pin "low" to enter the "command mode". */
static void ILI9341_command_select(void)
{
	HAL_GPIO_WritePin(ILI9341_DCX_PORT, ILI9341_DCX_PIN, GPIO_PIN_RESET);
}


/* Set ILI9341 RESX pin "low" and then "high" to reset the device. */
static void ILI9341_reset(void)
{
    HAL_GPIO_WritePin(ILI9341_RESX_PORT, ILI9341_RESX_PIN, GPIO_PIN_RESET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(ILI9341_RESX_PORT, ILI9341_RESX_PIN, GPIO_PIN_SET);
}


/*
 * Transmit 8-bit command.
 * Parameter "cmd" is a command to transmit.
 */
static void ILI9341_write_command(uint8_t cmd)
{
	ILI9341_command_select();
    HAL_SPI_Transmit(&hspi1, &cmd, sizeof(cmd), HAL_MAX_DELAY);
}


/* The data packet is cut into segments and then transmitted. */
static void ILI9341_write_data(uint8_t* pBuff, size_t buff_size)
{
	ILI9341_data_select();

    while(buff_size > 0) {
        uint16_t buff_segm_size = buff_size > 32768 ? 32768 : buff_size;
        HAL_SPI_Transmit(&hspi1, pBuff, buff_segm_size, HAL_MAX_DELAY);
        pBuff = pBuff + buff_segm_size;
        buff_size = buff_size - buff_segm_size;
    }
}


/*
 * Define the frame memory area available to the MCU.
 * 1st parameter "sc" is a column starting point;
 * 2nd parameter "sp" is a page (row) starting point;
 * 3rd parameter "ec" is a column ending point;
 * 4th parameter "ep" is a page (row) ending point.
 */
static void ILI9341_set_frame_mem_area(uint16_t sc, uint16_t sp, uint16_t ec, uint16_t ep)
{
    /* Column address set (CASET) */
    ILI9341_write_command(0x2A);
    uint8_t caset_data[] = {sc >> 8, sc, ec >> 8, ec};
    ILI9341_write_data(caset_data, sizeof(caset_data));

    /* Page address set (PASET) */
    ILI9341_write_command(0x2B);
    uint8_t paset_data[] = {sp >> 8, sp, ep >> 8, ep};
    ILI9341_write_data(paset_data, sizeof(paset_data));

    /* Memory write (RAMWR) */
    ILI9341_write_command(0x2C);
}


/*
 * Write a character.
 * 1st parameter "x" is a starting x coordinate;
 * 2nd parameter "y" is a starting y coordinate;
 * 3rd parameter "ch" is a character to write;
 * 4th parameter "font" is a fontpocz type;
 * 5th parameter "color" is a font color;
 * 6th parameter "bg_color" is a font background color.
 */
static void ILI9341_write_char(uint16_t x, uint16_t y, char ch, font_t font, uint16_t color, uint16_t bg_color)
{
    uint32_t i, b, j;

    ILI9341_set_frame_mem_area(x, y, x+font.width-1, y+font.height-1);

    for(i = 0; i < font.height; i++){
        b = font.data[(ch - 32) * font.height + i];
        for(j = 0; j < font.width; j++){
            if((b << j) & 0x8000){
                uint8_t data[] = {color >> 8, color};
                ILI9341_write_data(data, sizeof(data));
            } else {
                uint8_t data[] = { bg_color >> 8, bg_color};
                ILI9341_write_data(data, sizeof(data));
            }
        }
    }
}


/*
 * Write a string.
 * 1st parameter "x" is a starting x coordinate.
 * 2nd parameter "y" is a starting y coordinate.
 * 3rd parameter "str" is a string to write.
 * 4th parameter "font" is a font type.
 * 5th parameter "color" is a font color.
 * 6th parameter "bg_color" is a font background color.
 */
void ILI9341_write_string(uint16_t x, uint16_t y, const char* str, font_t font, uint16_t color, uint16_t bg_color)
{
    ILI9341_select();

    while(*str) {
        if(x + font.width >= ILI9341_WIDTH) {
            x = 0;
            y = y + font.height;
            if(y + font.height >= ILI9341_HEIGHT) {
                break;
            }

            if(*str == ' ') {
                /* Skip spaces in the beginning of the new line. */
                str++;
                continue;
            }
        }

        ILI9341_write_char(x, y, *str, font, color, bg_color);
        x = x + font.width;
        str++;
    }

    ILI9341_unselect();
}


/* Draw a single pixel. */
void ILI9341_draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
	ILI9341_select();
	ILI9341_set_frame_mem_area(x, y, (x + 1), (y + 1));

    uint8_t data[] = {color >> 8, color};
    ILI9341_write_data(data, sizeof(data));

    ILI9341_unselect();
}


/*
 * Draw an rectangle without filling.
 * 1st parameter "x" is a starting x coordinate;
 * 2nd parameter "y" is a starting y coordinate;
 * 3rd parameter "width" is a width of the rectangle;
 * 4th parameter "height" is a height of the rectangle;
 * 5th parameter "thickness" is a thickness of the rectangle edges;
 * 6th parameter "color" is a color of the rectangle.
 */
void ILI9341_draw_rectangle_empty(uint16_t x, uint16_t y, uint16_t width,
								  uint16_t height, uint8_t thickness, uint16_t color)
{
	if(!(x >= ILI9341_WIDTH) && !(y >= ILI9341_HEIGHT)){
		if(!((x + width - 1) >= ILI9341_WIDTH) && !((y + height - 1) >= ILI9341_HEIGHT)){
			if((thickness < (width / 2)) && (thickness < (height /2))) {
				uint16_t i;
				uint8_t j;

				for(i = 0; i < width; i++){
					for(j = 0; j < thickness; j++){
						ILI9341_draw_pixel((x + i), (y + j), color);
						ILI9341_draw_pixel((x + i), (y + height - 1 - j), color);
					}
				}

				for(i = 0; i < height; i++) {
					for(j = 0; j < thickness; j++){
						ILI9341_draw_pixel((x + j), (y + i), color);
						ILI9341_draw_pixel((x + width - 1 - j), (y + i), color);
					}
				}
			}
		}
	}
}


/*
 * Draw a filled rectangle.
 * 1st parameter "x" is a starting x coordinate;
 * 2nd parameter "y" is a starting y coordinate;
 * 3rd parameter "width" is a width of the rectangle;
 * 4th parameter "height" is a height of the rectangle;
 * 5th parameter "color" is a color of the rectangle.
 */
void ILI9341_draw_rectangle_full(uint16_t x, uint16_t y, uint16_t width,
								 uint16_t height, uint16_t color)
{
	if(!(x >= ILI9341_WIDTH) && !(y >= ILI9341_HEIGHT)){
		if(!((x + width - 1) >= ILI9341_WIDTH) && !((y + height - 1) >= ILI9341_HEIGHT)){
			ILI9341_select();
			ILI9341_set_frame_mem_area(x, y, (x + width - 1), (y + height - 1));

			uint8_t data[] = {color >> 8, color};
			HAL_GPIO_WritePin(ILI9341_DCX_PORT, ILI9341_DCX_PIN, GPIO_PIN_SET);
			for(y = 0; y < height; y++){
				for(x = 0; x < width; x++){
					HAL_SPI_Transmit(&hspi1, data, sizeof(data), HAL_MAX_DELAY);
				}
			}
			ILI9341_unselect();
		}
	}
}


/* Fill the screen with color. */
void ILI9341_fill_screen(uint16_t color)
{
    ILI9341_draw_rectangle_full(0, 0, ILI9341_WIDTH, ILI9341_HEIGHT, color);
}
