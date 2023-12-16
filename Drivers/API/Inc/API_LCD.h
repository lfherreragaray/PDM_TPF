/*
 * LCD.h
 *
 *  Created on: Nov 26, 2023
 *      Author: ubuntu
 */

#ifndef API_INC_API_LCD_H_
#define API_INC_API_LCD_H_
#include <API_I2C.h>
#include "string.h"
void LCD_Init(uint8_t address);
void LCD_Write(uint8_t address,uint8_t data,bool_t rs);
void LCD_WriteChar(uint8_t address,char *data);
void LCD_WriteXY(uint8_t address,char *data,uint8_t x, uint8_t y);
void LCD_Pos(uint8_t address,uint8_t x,uint8_t y);
#endif /* API_INC_API_LCD_H_ */
