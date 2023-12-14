/*
 * I2C.c
 *
 *  Created on: Nov 20, 2023
 *      Author: ubuntu
 */
#include "I2C.h"
#include "strings.h"
#define TIMEOUT 10
#define CORRIMIENTO_1 <<1
I2C_HandleTypeDef I2C1_handle;
uint16_t ADDR = 0;
bool_t i = true;
void I2C1_Gpio(void)
    {
    GPIO_InitTypeDef gpio_I2C =
	{
	0
	};
    __HAL_RCC_GPIOB_CLK_ENABLE();
    gpio_I2C.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    gpio_I2C.Mode = GPIO_MODE_AF_OD;
    gpio_I2C.Pull = GPIO_PULLUP;
    gpio_I2C.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio_I2C.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &gpio_I2C);
    }

/*@brief I2C_Init: Inicializa el protocolo I2C
 * @param void
 * @return bool_t HAL_OK o HAL_ERROR
*/
bool_t I2C_Init(void)
    {
    I2C1_Gpio();
    __HAL_RCC_I2C1_CLK_ENABLE();
    I2C1_handle.Instance = I2C1;
    I2C1_handle.Init.ClockSpeed = 100000;
    I2C1_handle.Init.DutyCycle = I2C_DUTYCYCLE_2;
    I2C1_handle.Init.OwnAddress1 = 0;
    I2C1_handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    I2C1_handle.Init.OwnAddress2 = 0;
    I2C1_handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    I2C1_handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    I2C1_handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(&I2C1_handle) == HAL_OK)
	{
	return false;
	}

    return true;
    }

/*@brief I2C_device: Busca un dispositivo que conteste a una direccion y la retorna
 * @param void
 * @return uint8_t Addres del dispositivo que está listo
*/
uint8_t I2C_device(void)
    {
    int i=0;
    for(;i<128;i++)
	{
	HAL_I2C_IsDeviceReady(&I2C1_handle, (i) << 1, 1, TIMEOUT);
	}
    return i;

    }

/*@brief I2C_transmit: Transmite dato a un dispositivo
 * @param void
 * @return void
*/
void I2C_transmit(uint8_t addr, uint8_t *p_data, uint8_t size)
    {
    HAL_I2C_Master_Transmit(&I2C1_handle, addr << 1, p_data, size, TIMEOUT);


    }

/*@brief I2C_transmitMem: transmite datos usando modo bloqueante a una direccion de memoria
 * @param void
 * @return void
*/
void I2C_transmitMem(uint8_t addr,uint8_t regAddr, uint8_t *p_data)
    {
    HAL_I2C_Mem_Write(&I2C1_handle, addr<<1, regAddr, sizeof(regAddr), p_data, sizeof(*p_data), TIMEOUT);

    }

/*@brief I2C_receiveMem: Lee datos usando modo bloqueante a una direccion de memoria
 * @param void
 * @return uint32_t
*/
uint32_t I2C_receiveMem(uint8_t addr,uint8_t regAddr,uint8_t* p_data,uint8_t size)
    {
    HAL_I2C_Mem_Read(&I2C1_handle, addr<<1, regAddr, sizeof(regAddr), p_data,size, TIMEOUT);
    return *p_data;
    }

/*@brief I2C_receive:  Recibe de modo Master una cantidad de datos en modo bloqueante
 * @param void
 * @return void
*/
void I2C_receive(uint8_t addr, uint8_t *p_data)
    {
    HAL_I2C_Master_Receive(&I2C1_handle, addr << 1, p_data, sizeof(p_data), TIMEOUT);
    }
