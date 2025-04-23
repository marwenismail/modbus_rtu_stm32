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



uint8_t modbus_uart_get_readiness(){
    uint8_t ret_val=0,max_retry=10;
    
    do
        {
        HAL_Delay(200);
        ret_val=HAL_UART_GetState(&huart2);
        if (ret_val==HAL_UART_STATE_READY|| ret_val==HAL_UART_STATE_RESET)
        {
            ret_val=0;
            break;
        }
        max_retry--;
        } while (ret_val||max_retry);
    return ret_val;
}

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
