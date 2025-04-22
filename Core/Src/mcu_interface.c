/**
 * @file mcu_interface.c
 * @author Marwen BENISMAIL (mbenismail52@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "mcu_interface.h"
#include "periph_init.h"

#include "stm32f4xx_hal.h"



extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart1;



/**
 * @brief this function is used to send data over uart on stm32 board
 * 
 * @param data 
 * @param size 
 */
uint8_t modbus_uart_send(uint8_t *data, uint8_t size)
{
    return HAL_UART_Transmit(&huart2, data, size, 2000);
}

/**
 * @brief this function is used to receive data over uart on stm32 board
 * 
 * @param data 
 * @param size 
 * @return uint8_t 
 */
uint8_t modbus_uart_receive(uint8_t *data, uint8_t size)
{
    return HAL_UART_Receive(&huart2, data, size, 2000);
}
/**
 * @brief this function is used to recieve data over uart with timeout on stm32 board
 * 
 * @param data 
 * @param size 
 * @param timeout 
 * @return uint8_t 
 */
uint8_t modbus_uart_receive_timeout(uint8_t *data, uint8_t size, uint32_t timeout)
{
    return HAL_UART_Receive(&huart2, data, size, timeout);
}
