/*
 * I2C.h
 *
 *  Created on: Nov 20, 2023
 *      Author: ubuntu
 */

#ifndef API_INC_I2C_H_
#define API_INC_I2C_H_
#ifndef __STDINT_H
#include "stdint.h"
#endif
#ifndef __STDBOOL_H
#include "stdbool.h"
#endif
#include "main.h"
#include "string.h"
typedef bool bool_t;
void I2C_Gpio(void);
bool_t I2C_Init(void);
void I2C_transmit(uint8_t addr, uint8_t *p_data, uint8_t size);
void I2C_transmitMem(uint8_t addr,uint8_t regAddr, uint8_t *p_data);
uint32_t I2C_receiveMem(uint8_t addr,uint8_t regAddr,uint8_t* p_data,uint8_t size);
uint8_t I2C_device(void);
#endif /* API_INC_I2C_H_ */
