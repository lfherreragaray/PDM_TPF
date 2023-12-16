/*
 * MEF_MENU.h
 *
 *  Created on: Dec 6, 2023
 *      Author: ubuntu
 */

#ifndef API_INC_API_MEF_MENU_H_
#define API_INC_API_MEF_MENU_H_
#include <API_MPU6050.h>

#ifndef NC_LCD_H_
#include <API_LCD.h>
#endif

#ifndef API_INC_I2C_H_
#include <API_I2C.h>
#endif
#ifndef API_INC_STDIO_H_
#include "stdio.h"
#endif

#ifndef INC_API_DELAY_H_
#include "API_delay.h"
#endif /* INC_API_DELAY_H_ */

#ifndef INC_API_DEBOUNCE_H_
#include "API_debounce.h"
#endif

void MenuMEF_Init(void);
void MenuMEF_Uptade(void);

#endif /* API_INC_API_MEF_MENU_H_ */
