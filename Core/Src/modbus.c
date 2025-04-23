/**
 * @file modbus.c
 * @author Marwen BENISMAIL (mbenismail52@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#include "modbus.h"
#include "mcu_interface.h"



typedef enum{
    READ_COLIS=0x01,
    READ_DISCRETE_INPUT=0x02,
    READ_HOLDING_REG=0x03,
    READ_INPUT_REG=0x04,
    WRITE_SINGLE_COIL=0x05,
    WRITE_SINGLE_REG=0x06,
    WRITE_MULTIPLE_COILS=0x0F,
    WRITE_MULTIPLE_REG=0x10,
    /*DIAGNOSTICS=0x08,
    GET_COM_EVENT_COUNTER=0x0B,
    WRITE_MASK_REG=0x16,
    READ_WRITE_MULTIPLE_REG=0x17,
    REPORT_SLAVE_ID=0x11,*/
    UNDEFINED=0xFF
} ModbusFunctionCodeTypeDef;


typedef struct {
uint8_t slave_adr;
uint8_t function;
uint8_t reg_adr[2];
uint8_t quantity[2];
uint8_t crc[2];
} ModbusF1TypeDef;




/**
 * @brief this funtction used to init the bus 
 * 
 * @return uint8_t 
 */
uint8_t modbus_init(){

    // Get the bus readiness
    if (modbus_uart_get_readiness() != 0) {
        return 1; // Error in bus readiness
    }
    return 0;
}
/**
 * @brief this funtction used to init the bus
 * 
 * @return uint8_t 
 */
uint8_t modbus_deinit(){

    return 0;
}

/**
 * @brief this function is used to read  from the slave device 
 * 
 * @param slave_adr 
 * @param function 
 * @param start_adress 
 * @param quantity 
 * @return uint8_t 
 */
uint8_t read_modbus(uint8_t slave_adr,uint8_t function, uint16_t start_adress,uint16_t quantity)
{
    ModbusF1TypeDef modbus_data;
    uint8_t ret_val=0;
    modbus_data.slave_adr=slave_adr;
    switch (function)
    {
    case READ_COLIS :
    case READ_DISCRETE_INPUT:
    case READ_HOLDING_REG:
    case READ_INPUT_REG:
        modbus_data.function=function;
        break;
    default:
        // Invalid function code
        return 1;
    }
    
    modbus_data.reg_adr[1]=start_adress>>8;
    modbus_data.reg_adr[0]=start_adress&0x00FF;
    modbus_data.quantity[1]=quantity>>8;
    modbus_data.quantity[0]=quantity&0x00FF;
    modbus_data.crc[0]=0x00; // CRC low byte
    modbus_data.crc[1]=0x00; // CRC high byte
    // Calculate CRC (for simplicity, using a dummy value here)

    // send the data over uart
    ret_val=modbus_uart_send((uint8_t *)&modbus_data, sizeof(modbus_data));
    return ret_val;
}

/**
 * @brief this function is used to write single register to the slave device 
 * 
 * @param slave_adr 
 * @param function 
 * @param start_adress 
 * @param quantity 
 * @return uint8_t 
 */
uint8_t write_modbus_single(uint8_t slave_adr,uint8_t function, uint16_t start_adress,uint16_t quantity)
{
    ModbusF1TypeDef modbus_data;
    uint8_t ret_val=0;
    modbus_data.slave_adr=slave_adr;
    switch (function)
    {
    case WRITE_SINGLE_COIL:
    case WRITE_SINGLE_REG:
        modbus_data.function=function;
        break;
    default:
        // Invalid function code
        return 1;
    }
    
    modbus_data.reg_adr[1]=start_adress>>8;
    modbus_data.reg_adr[0]=start_adress&0x00FF;
    modbus_data.quantity[1]=quantity>>8;
    modbus_data.quantity[0]=quantity&0x00FF;
    modbus_data.crc[0]=0x00; // CRC low byte
    modbus_data.crc[1]=0x00; // CRC high byte
    // Calculate CRC (for simplicity, using a dummy value here)

    // send the data over uart
    ret_val=modbus_uart_send((uint8_t *)&modbus_data, sizeof(modbus_data));
    return ret_val;
}

uint8_t write_modbus_multiple(ModbusF3TypeDef *data)
{
    uint8_t modbus_data[ 9+ data->byte_count];
    uint8_t ret_val=0;
    modbus_data[0]=data->slave_adr;
    switch (data->function)
    {
    case WRITE_MULTIPLE_COILS:
    case WRITE_MULTIPLE_REG:
        modbus_data[1]=data->function;
        break;
    default:
        // Invalid function code
        return 1;
    }
    modbus_data[2]=(data->reg_adr[1]) ;
    modbus_data[3]=(data->reg_adr[0]);
    modbus_data[4]=(data->quantity[1]);
    modbus_data[5]=(data->quantity[0]);
    modbus_data[6]=data->byte_count;
    memcpy(&modbus_data[7],data->data,data->byte_count);

    // Calculate CRC (for simplicity, using a dummy value here)
    modbus_data[7+(data->byte_count)]=0x00; // CRC low byte
    modbus_data[8+(data->byte_count)]=0x00; // CRC high byte

    // send the data over uart
    ret_val=modbus_uart_send((uint8_t *)&modbus_data, sizeof(modbus_data));
    return ret_val;
}
