/**
 * @file mcu_interface.h
 * @author Marwen BENISMAIL (mbenismail52@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #ifndef MCU_INTERFACE_H
#define MCU_INTERFACE_H
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_SIZE 256

#ifdef __cplusplus
extern "C" {
#endif

uint8_t modbus_uart_send(uint8_t *data, uint8_t size);
uint8_t modbus_uart_receive(uint8_t *data, uint8_t size);
uint8_t modbus_uart_receive_timeout(uint8_t *data, uint8_t size, uint32_t timeout);
uint8_t modbus_uart_get_readiness();



#ifdef __cplusplus
}
#endif
#endif // MCU_INTERFACE_H