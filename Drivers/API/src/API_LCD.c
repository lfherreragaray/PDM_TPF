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
#define R2 	0xc0//R2 corresponde al renglon dos.
#define MASKMSB 0xf0//esta macro se utilizar para separar el registro de 8 bits en dos nibles

#define POS_LCD_L1 1 //macro para pocision LCD: renglon 1
#define POS_LCD_L2 2 //macro para pocision LCD: renglon 2

//Tiempos para inicializacion necesarios del LCD
#define DELAY_LCD_50 50
#define DELAY_LCD_10 10
#define DELAY_LCD_5 5
#define DELAY_LCD_2 2
#define DELAY_LCD_1 1

#define RS_HIGH 1
#define RS_LOW 0

void DelayLCD(uint16_t t);

/*@brief LCD_Init: Inicializa el LCD
 * @param void
 * @return void
*/
void LCD_Init(uint8_t address)
    {
    //I2C_device();
    I2C_Init();
    //Modo 4bits
    DelayLCD(DELAY_LCD_50);
    LCD_Write(address,0x30,CMD);
    DelayLCD(DELAY_LCD_5);
    LCD_Write(address,0x30,CMD);
    DelayLCD(DELAY_LCD_1);
    LCD_Write(address,0x30,CMD);
    DelayLCD(DELAY_LCD_10);
    LCD_Write(address,0x20,CMD);
    DelayLCD(DELAY_LCD_10);
    //Inicializacion
    LCD_Write(address,0x28,CMD);
    DelayLCD(DELAY_LCD_1);
    LCD_Write(address,0x08,CMD);
    DelayLCD(DELAY_LCD_1);
    LCD_Write(address,0x01,CMD);
    DelayLCD(DELAY_LCD_2);
    LCD_Write(address,0x06,CMD);
    DelayLCD(DELAY_LCD_1);
    LCD_Write(address,0x0C,CMD);
    }


/*@brief LCD_Write: Parte el envío de Byte en nibble alto y bajo
 * @param void
 * @return void
*/
void LCD_Write(uint8_t address,uint8_t data,bool_t rs)
    {
    uint8_t Data[4]={0};
    /*para una configuracion que manda 4bits se necesita descomponer el valor a enviar en dos nibles
     * cada nible es enviado cuando E es activado y desactivadom tambien se tomma en cuenta si se quiere enviar un
     * comando o un caracter, dadas las caracteristicas de la interfaz i2c, los 4 bits se mandan por el MSB
     * y los bits de coniguracion se envian en el lsb*/
    Data[0]=(data&MASKMSB)|E|rs|BL;
    Data[1]=(data&MASKMSB)|rs|BL;
    Data[2]=((data<<4)&MASKMSB)|E|rs|BL;
    Data[3]=((data<<4)&MASKMSB)|rs|BL;
    I2C_transmit(address,(uint8_t*)&Data,sizeof(Data));
    }

/*@brief LCD_WriteChar: Envía cadena de datos tipo char al LCD
 * @param void
 * @return void
*/
void LCD_WriteChar(uint8_t address,char *data){

    for(int i=0;i<strlen(data);i++)
	{
	LCD_Write(address,data[i],RS_HIGH);
	}

}

/*@brief LCD_WriteXY: Escribe una cadena tipo char en una pocision específica del LCD
 * @param void
 * @return void
*/
void LCD_WriteXY(uint8_t address,char *data,uint8_t x, uint8_t y)
    {

    LCD_Pos(address, x, y);
    for(int i=0;i<strlen(data);i++)
	{
	LCD_Write(address,data[i],RS_HIGH);
	}

    }

/*@brief LCD_Pos: Envía la pocision en la pantalla LCD
 * @param void
 * @return void
*/
void LCD_Pos(uint8_t address,uint8_t x,uint8_t y)
{
	if (x==POS_LCD_L1)
		x=R1;
	else if(x==POS_LCD_L2)
		x=R2;
	else
		x=R1;
	LCD_Write(address,x+y,CMD);
}

/*@brief DelayLCD: Demora bloqueante para uso del LCD
 * @param void
 * @return void
*/
void DelayLCD(uint16_t t)
    {
    HAL_Delay(t);
    }
