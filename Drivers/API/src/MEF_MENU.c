/*
 * MEF_MENU.c
 *
 *  Created on: Nov 19, 2023
 *      Author: ubuntu
 */


#include "MEF_MENU.h"

#define ESPERA 40
#define DATOSF2S 5
#define ADDR_LCD 0x27
#define R1 1
#define R2 2
#define LCDPOSCENTER 8
#define LCDPOSL 0
typedef enum{
	EstadoMenu_1,
	EstadoMenu_2,
	EstadoMenu_3,
	EstadoMenu_4
} EstadoMenu_t;

EstadoMenu_t EstadoMenu;
delay_t delayMenu;
char data[]={0};
char data0[]={"      Menu    "};
char data1[]={"1-Mostrar Acc "};
char data2[]={"2-Mostrar Gyro"};
char data4[]={"   X:"};
char data5[]={"Y:"};
char data6[]={"Z:"};
char data7[]={"Acc :"};
char data8[]={"Gyro:"};
char data10[]={"                "};
void MefMenuImprimir(float* pdata);
void LCD_Limpiar();
void MenuMEF_Init(){
    LCD_Init(ADDR_LCD);
    MPU6050_Init();
    debounceFSM_Init();
	 EstadoMenu=EstadoMenu_1;
	 delayInit(&delayMenu,ESPERA);
}

void MenuMEF_Uptade(){
    debounceFSM_Update();
	switch(EstadoMenu)
	{
		case EstadoMenu_1:
		LCD_WriteXY(ADDR_LCD,(char*)data0,R1,LCDPOSL);
		LCD_WriteXY(ADDR_LCD,(char*)data1,R2,LCDPOSL);
		if(readKeyAsc())
		{
			LCD_Limpiar();
		    EstadoMenu=EstadoMenu_2;
		}

		else if(readKeyPress())
		{
			LCD_Limpiar();
		EstadoMenu=EstadoMenu_3;
		}
		break;
		
		case EstadoMenu_2:
		LCD_WriteXY(ADDR_LCD,(char*)data0,R1,LCDPOSL);
		LCD_WriteXY(ADDR_LCD,(char*)(data2),R2,LCDPOSL);
		if(readKeyAsc())
		{
			LCD_Limpiar();
			EstadoMenu=EstadoMenu_1;

		}

		else if(readKeyPress())
		{
			LCD_Limpiar();
		EstadoMenu=EstadoMenu_4;
		}
		break;

		/*case EstadoMenu_3:
		LCD_WriteXY(ADDR_LCD,(char*)data0,R1,LCDPOSL);
		LCD_WriteXY(ADDR_LCD,(char*)(data3),R2,LCDPOSL);
		if(readKeyAsc())
		{
			LCD_Limpiar();
		    EstadoMenu=EstadoMenu_1;
		}

		else if(readKeyPress())
		{
			LCD_Limpiar();
		EstadoMenu=EstadoMenu_6;
		}
		break;
*/
		case EstadoMenu_3:
		LCD_WriteXY(ADDR_LCD, (char*) data7, R1, LCDPOSL);
		MefMenuImprimir(MPU_ReadAcc());

		if(readKeyPress())
		{
			LCD_Limpiar();
			EstadoMenu=EstadoMenu_1;
		}
		break;

		case EstadoMenu_4:
		//float* Acc=MPU_ReadAcc();
		LCD_WriteXY(ADDR_LCD, (char*) data8, R1, LCDPOSL);
		MefMenuImprimir(MPU_ReadGyro());

		if(readKeyPress())
		{
			LCD_Limpiar();
			EstadoMenu=EstadoMenu_2;
		}
		break;
		/*
		case EstadoMenu_6:
				//float* Acc=MPU_ReadAcc();

				MefMenuImprimir(MPU_ReadGyro());

				if(readKeyPress())
				{
					LCD_Limpiar();
					EstadoMenu=EstadoMenu_3;
				}
				break;
		break;*/
		default:EstadoMenu=EstadoMenu_1;
	}
	
	
	
}

void LCD_Limpiar()
{
	LCD_WriteXY(ADDR_LCD, (char*) (data10), R1, LCDPOSL);
	LCD_WriteXY(ADDR_LCD, (char*) (data10), R2, LCDPOSL);
}

void MefMenuImprimir(float* pdata)
{
	snprintf(data,DATOSF2S, "%.2f", *(pdata));
	LCD_WriteChar(ADDR_LCD, (char*) (data4));
	LCD_WriteChar(ADDR_LCD, (char*) (data));
	snprintf(data,DATOSF2S, "%.2f", *(pdata + 1));
	//LCD_WriteXY(ADDR_LCD, (char*) (data10), R2, LCDPOSL);
	LCD_WriteXY(ADDR_LCD, (char*) (data5), R2, LCDPOSL);
	LCD_WriteChar(ADDR_LCD, (char*) (data));
	snprintf(data,DATOSF2S, "%.2f", *(pdata + 2));
	LCD_WriteXY(ADDR_LCD, (char*) (data6), R2, LCDPOSCENTER);
	LCD_WriteChar(ADDR_LCD, (char*) (data));
}
