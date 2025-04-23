/**
 * @file modbus.h
 * @author Marwen BENISMAIL (mbenismail52@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef MODBUS_H
#define MODBUS_H
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 256

typedef struct {
    uint8_t slave_adr;
    uint8_t function;
    uint8_t reg_adr[2];
    uint8_t quantity[2];
    uint8_t byte_count;
    uint8_t data[MAX_SIZE];
    uint8_t crc[2];
    } ModbusF3TypeDef;

#ifdef __cplusplus
extern "C" {
#endif

uint8_t modbus_init();
uint8_t modbus_deinit();

uint8_t read_modbus(uint8_t slave_adr,uint8_t function, uint16_t start_adress,uint16_t quantity);
uint8_t write_modbus_single(uint8_t slave_adr,uint8_t function, uint16_t start_adress,uint16_t quantity);
uint8_t write_modbus_multiple(ModbusF3TypeDef *data);
#ifdef __cplusplus
}
#endif

#endif // MODBUS_H
