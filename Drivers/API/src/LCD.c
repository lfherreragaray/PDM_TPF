/*
 * LCD.c
 *
 *  Created on: Nov 26, 2023
 *      Author: ubuntu
 */
#include "LCD.h"
#define E 	0x4 //enable-> perminte comenzar la transmision de datos al LCD
#define BL	0x8//backlight-> variable que controla el led de iluminacion del lcd
#define CHAR 	0x1//-> tanto cmd como char corresponden al valor de rs, que permite enviar tanto comandos como caracteres
#define CMD 	0x0
#define RW 	0x2//Read/write, dado que la LCD no intentara comunicarse con nosotros, esta variable sera 0
#define R1 	0x80//tanto R1 como R2 contienen la direcion de memoria de la LCD, R1 corresponde al renglon 1
#define R2 	0xc0//
#define MASKMSB 0xf0
void DelayLCD(uint16_t t);
void LCD_Init(uint8_t address)
    {
    //I2C_device();
    I2C_Init();
    //Modo 4bits
    DelayLCD(50);
    LCD_Write(address,0x30,CMD);
    DelayLCD(5);
    LCD_Write(address,0x30,CMD);
    DelayLCD(1);
    LCD_Write(address,0x30,CMD);
    DelayLCD(10);
    LCD_Write(address,0x20,CMD);
    DelayLCD(10);
    //Inicializacion
    LCD_Write(address,0x28,CMD);
    DelayLCD(1);
    LCD_Write(address,0x08,CMD);
    DelayLCD(1);
    LCD_Write(address,0x01,CMD);
    DelayLCD(2);
    LCD_Write(address,0x06,CMD);
    DelayLCD(1);
    LCD_Write(address,0x0C,CMD);
    }

void LCD_Write(uint8_t address,uint8_t data,bool_t rs)
    {
    uint8_t Data[4]={0};

    Data[0]=(data&MASKMSB)|E|rs|BL;
    Data[1]=(data&MASKMSB)|rs|BL;
    Data[2]=((data<<4)&MASKMSB)|E|rs|BL;
    Data[3]=((data<<4)&MASKMSB)|rs|BL;
    I2C_transmit(address,(uint8_t*)&Data,sizeof(Data));

    }
void LCD_WriteChar(uint8_t address,char *data){

    for(int i=0;i<strlen(data);i++)
	{
	LCD_Write(address,data[i],1);
	}

}

void LCD_WriteXY(uint8_t address,char *data,uint8_t x, uint8_t y)
    {

    LCD_Pos(address, x, y);
    for(int i=0;i<strlen(data);i++)
	{
	LCD_Write(address,data[i],1);
	}

    }

void LCD_Pos(uint8_t address,uint8_t x,uint8_t y)
{
	if (x==1)
		x=R1;
	else if(x==2)
		x=R2;
	else
		x=R1;
	LCD_Write(address,x+y,CMD);
}

void DelayLCD(uint16_t t)
    {
    HAL_Delay(t);
    }
