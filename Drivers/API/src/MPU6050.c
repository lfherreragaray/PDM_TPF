/*
 * LCD.c
 *
 *  Created on: Nov 26, 2023
 *      Author: ubuntu
 */
#include "MPU6050.h"
#include "I2C.h"
#define SMPLRT_DIV_REG   0x19
#define GYRO_CONFIG_REG  0x1B
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG   0x41
#define GYRO_XOUT_H_REG  0x43
#define PWR_MGMT_1_REG   0x6B
#define MPU_ADDR	 0x68
#define BYTE6 		 6
#define BYTE3 		 3
#define GYROFS		 131
#define ACCFS		 16384
uint8_t Parametro1=0x00;
uint8_t Parametro2=0x07;
uint8_t Parametro3=0x00;
uint8_t Parametro4=0x00;
float Acc[BYTE3];
float Gyro[BYTE3];

void MPU6050_Init()
{
  I2C_Init();


  MPU_WriteI2C(MPU_ADDR, PWR_MGMT_1_REG, &Parametro1);
  HAL_Delay(1);
  MPU_WriteI2C(MPU_ADDR,PWR_MGMT_1_REG,&Parametro1);
  HAL_Delay(1);
  MPU_WriteI2C(MPU_ADDR,SMPLRT_DIV_REG,&Parametro2);
  HAL_Delay(1);
  MPU_WriteI2C(MPU_ADDR,ACCEL_CONFIG_REG,&Parametro3);
  HAL_Delay(1);
  MPU_WriteI2C(MPU_ADDR,GYRO_CONFIG_REG,&Parametro4);
  HAL_Delay(1);


}

float* MPU_ReadAcc()
    {
    uint8_t data[BYTE6]={0};
    MPU_ReadI2C(MPU_ADDR,ACCEL_XOUT_H_REG,(uint8_t*) &data,BYTE6);
    int16_t AccX = (int16_t)(data[0] << 8 | data[1]);
    int16_t AccY = (int16_t)(data[2] << 8 | data[3]);
    int16_t AccZ = (int16_t)(data[4] << 8 | data[5]);
    Acc[0]=(float)AccX/ACCFS;
    Acc[1]=(float)AccY/ACCFS;
    Acc[2]=(float)AccZ/ACCFS;
    return Acc;
    }



float* MPU_ReadGyro()
    {
    uint8_t data[BYTE6]={0};
    MPU_ReadI2C(MPU_ADDR,GYRO_XOUT_H_REG,(uint8_t*) &data,BYTE6);
    int16_t GyrX = (int16_t)(data[0] << 8 | data[1]);
    int16_t GyrY = (int16_t)(data[2] << 8 | data[3]);
    int16_t GyrZ = (int16_t)(data[4] << 8 | data[5]);
    Gyro[0]=(float)GyrX/GYROFS;
    Gyro[1]=(float)GyrY/GYROFS;
    Gyro[2]=(float)GyrZ/GYROFS;
    return Gyro;
    }
void MPU_WriteI2C(uint8_t address,uint8_t regAddres,uint8_t *data)
    {
    I2C_transmitMem(address,regAddres,data);

    }
	
uint8_t* MPU_ReadI2C(uint8_t address,uint8_t regAddres,uint8_t *data,uint8_t size)
    {
    I2C_receiveMem(address,regAddres,data,size);
return data;
    }
	

