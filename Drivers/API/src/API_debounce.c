/*
 * API_debounce.c
 *
 *  Created on: Nov 19, 2023
 *      Author: ubuntu
 */


#include "API_debounce.h"

#define ESPERA 40
#define ESPERA_ENTER 2000
#define ESPERA_RESET 0
//const uint8_t espera =40;
typedef enum{
	Button_Up,
	Button_Falling,
	Button_Down,
	Button_Rising,
} debounceState_t;
debounceState_t EstadoBoton;//=Button_Up;
delay_t delayBoton;
delay_t delayBotonEnter;
bool_t botonDes=false;
bool_t botonAsc=false;
bool_t tCenter=false;
void debounceFSM_Init(){
	 EstadoBoton=Button_Up;

	 delayInit(&delayBotonEnter,ESPERA_ENTER);

}

void debounceFSM_Update(){

switch (EstadoBoton)
{
case Button_Up: if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))
						{
							EstadoBoton=Button_Falling;
						}
break;
case Button_Falling: 			  delayRead(&delayBoton);
					    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))
						{

						EstadoBoton=Button_Up;
						}
						else
						{

						    buttonPressed();
						    EstadoBoton=Button_Down;
						}
					  break;
case Button_Down: 				if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))
						{

						EstadoBoton=Button_Rising;
						}
break;

case Button_Rising:
						delayRead(&delayBoton);
						if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))
						{


						EstadoBoton=Button_Down;
						}
						else
						{
						    buttonReleased();
						    EstadoBoton=Button_Up;
						}
break;
default: EstadoBoton= Button_Up;

    }
}
 void buttonPressed()
     {
     botonDes=true;
     }

 void buttonReleased()
      {
     botonAsc=true;
      }

 bool_t readKeyAsc()
     {
     if (botonAsc)
 	{
 	botonAsc=false;
 	botonDes=false;
 	return true;
 	}
     return false;
     }

bool_t readKeyDes()
    {
    if (botonDes)
	{
	botonAsc=false;
	botonDes=false;
	return true;
	}
    return false;
    }
bool_t readKeyPress()
    {
    tCenter=delayRead(&delayBotonEnter);
    if (botonDes)
	{
	if (tCenter)
	{
	botonAsc=false;
	botonDes=false;
	return true;
	}
	else
	    return false;
	}
    else{
	//delayReset(&delayBotonEnter);
	tCenter=false;
	}
    return false;
    }
