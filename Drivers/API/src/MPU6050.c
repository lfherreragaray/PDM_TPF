/*
 * LCD.c
 *
 *  Created on: Nov 26, 2023
 *      Author: ubuntu
 */
#include "MPU6050.h"
#include "I2C.h"
//Registros para configuracion del MPU6050
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

#define TIME_DELAY1S 1

//Macros para acomodo de las lecturas de x, y y z
#define MOVE_8BITS 8
#define ARRAY_XYZ_POS0 0
#define ARRAY_XYZ_POS1 1
#define ARRAY_XYZ_POS2 2
#define ARRAY_XYZ_POS3 3
#define ARRAY_XYZ_POS4 4
#define ARRAY_XYZ_POS5 5
#define COMP_X 0
#define COMP_Y 1
#define COMP_Z 2


uint8_t Parametro1=0x00;
uint8_t Parametro2=0x07;
uint8_t Parametro3=0x00;
uint8_t Parametro4=0x00;
float Acc[BYTE3];
float Gyro[BYTE3];



/*@brief MPU_Init : Inicializa al sensor MPU6050 y tambien se inicializa el protocolo I2C
 * @param void
 * @return void
*/
void MPU6050_Init()
{
  I2C_Init();


  MPU_WriteI2C(MPU_ADDR, PWR_MGMT_1_REG, &Parametro1);
  HAL_Delay(TIME_DELAY1S);
  MPU_WriteI2C(MPU_ADDR,PWR_MGMT_1_REG,&Parametro1);
  HAL_Delay(TIME_DELAY1S);
  MPU_WriteI2C(MPU_ADDR,SMPLRT_DIV_REG,&Parametro2);
  HAL_Delay(TIME_DELAY1S);
  MPU_WriteI2C(MPU_ADDR,ACCEL_CONFIG_REG,&Parametro3);
  HAL_Delay(TIME_DELAY1S);
  MPU_WriteI2C(MPU_ADDR,GYRO_CONFIG_REG,&Parametro4);
  HAL_Delay(TIME_DELAY1S);


}

/*@brief MPU_ReadAcc : usa la función mpuread que a su vez usa el transmit i2c
 * para pedir datos al imu, se le ingresa la dirección de la región de memoria
 * que se leerá y se indica la cantidad de datos que se desea extraer
 * @param void
 * @return float*
*/
float* MPU_ReadAcc()
    {
    uint8_t data[BYTE6]={0};
    MPU_ReadI2C(MPU_ADDR,ACCEL_XOUT_H_REG,(uint8_t*) &data,BYTE6);
    int16_t AccX = (int16_t)(data[ARRAY_XYZ_POS0] << MOVE_8BITS | data[ARRAY_XYZ_POS1]);
    int16_t AccY = (int16_t)(data[ARRAY_XYZ_POS2] << MOVE_8BITS | data[ARRAY_XYZ_POS3]);
    int16_t AccZ = (int16_t)(data[ARRAY_XYZ_POS4] << MOVE_8BITS | data[ARRAY_XYZ_POS5]);
    Acc[COMP_X]=(float)AccX/ACCFS;
    Acc[COMP_Y]=(float)AccY/ACCFS;
    Acc[COMP_Z]=(float)AccZ/ACCFS;
    return Acc;
    }


/*@brief MPU_ReadGyro : Retorna un vector de componentes del girocopio
 * @param void
 * @return float*
*/
float* MPU_ReadGyro()
    {
    uint8_t data[BYTE6]={0};
    MPU_ReadI2C(MPU_ADDR,GYRO_XOUT_H_REG,(uint8_t*) &data,BYTE6);
    int16_t GyrX = (int16_t)(data[ARRAY_XYZ_POS0] << MOVE_8BITS | data[ARRAY_XYZ_POS1]);
    int16_t GyrY = (int16_t)(data[ARRAY_XYZ_POS2] << MOVE_8BITS | data[ARRAY_XYZ_POS3]);
    int16_t GyrZ = (int16_t)(data[ARRAY_XYZ_POS4] << MOVE_8BITS | data[ARRAY_XYZ_POS5]);
    Gyro[COMP_X]=(float)GyrX/GYROFS;
    Gyro[COMP_Y]=(float)GyrY/GYROFS;
    Gyro[COMP_Z]=(float)GyrZ/GYROFS;
    return Gyro;
    }

/*@brief MPU_WriteI2C : Escribe en un registro por I2C al MPU
 * @param void
 * @return void
*/
void MPU_WriteI2C(uint8_t address,uint8_t regAddres,uint8_t *data)
    {
    I2C_transmitMem(address,regAddres,data);

    }
	
/*@brief MPU_ReadI2C : Lee un registro por I2C al MPU
 * @param void
 * @return uint8_t* datos leídos
*/
uint8_t* MPU_ReadI2C(uint8_t address,uint8_t regAddres,uint8_t *data,uint8_t size)
    {
    I2C_receiveMem(address,regAddres,data,size);
return data;
    }
	

