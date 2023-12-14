/*
 * MPU6050.h
 *
 *  Created on: Dec 6, 2023
 *      Author: ubuntu
 */

#ifndef API_INC_MPU6050_H_
#define API_INC_MPU6050_H_
#include "API_debounce.h"
void MPU6050_Init(void);
uint8_t *MPU_ReadI2C(uint8_t address,uint8_t regAddres,uint8_t *data,uint8_t size);
void MPU_WriteI2C(uint8_t address,uint8_t regAddres,uint8_t *data);
float* MPU_ReadAcc();
float* MPU_ReadGyro();
#endif /* API_INC_MPU6050_H_ */
