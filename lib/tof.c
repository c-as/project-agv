#include <inttypes.h>
#include <util/delay.h>
#include <stdio.h>
#include "i2c.h"

#define TOF_ADDRESS_DEFAULT 0x52
#define VHV_CONFIG_PAD_SCL_SDA_EXTSUP_HV 0x89

void tof_init()
{
    i2c_write_register(TOF_ADDRESS_DEFAULT, VHV_CONFIG_PAD_SCL_SDA_EXTSUP_HV, i2c_read_register(TOF_ADDRESS_DEFAULT, VHV_CONFIG_PAD_SCL_SDA_EXTSUP_HV) | 0x01); // set tof in high voltage mode
    i2c_write_register(TOF_ADDRESS_DEFAULT, 0x88, 0x00);
    i2c_write_register(TOF_ADDRESS_DEFAULT, 0x80, 0x01);
    i2c_write_register(TOF_ADDRESS_DEFAULT, 0xFF, 0x01);
    i2c_write_register(TOF_ADDRESS_DEFAULT, 0x00, 0x00);
    i2c_write_register(TOF_ADDRESS_DEFAULT, 0x00, 0x01);
    i2c_write_register(TOF_ADDRESS_DEFAULT, 0xFF, 0x00);
    i2c_write_register(TOF_ADDRESS_DEFAULT, 0x80, 0x00);
}

uint8_t tof_measure()
{
    return 0;
}

void tof_test()
{
    while (1)
    {
        // VL53L0X test addresses
        //  address  ->  default value
        //  0xC0     ->  0xEE
        //  0xC1     ->  0xAA
        //  0xC2     ->  0x10
        //  0x51     ->  0x0099
        //  0x61     ->  0x0000
        uint8_t value1 = i2c_read_register(TOF_ADDRESS_DEFAULT, 0xC0);
        uint8_t value2 = i2c_read_register(TOF_ADDRESS_DEFAULT, 0xC1);
        uint8_t value3 = i2c_read_register(TOF_ADDRESS_DEFAULT, 0xC2);
        uint16_t value4 = i2c_read_16bit_register(TOF_ADDRESS_DEFAULT, 0x51);
        uint16_t value5 = i2c_read_16bit_register(TOF_ADDRESS_DEFAULT, 0x61);
        printf("i2c message: i2c_test(): register value: (0x%X)\n", value1);
        printf("i2c message: i2c_test(): register value: (0x%X)\n", value2);
        printf("i2c message: i2c_test(): register value: (0x%X)\n", value3);
        printf("i2c message: i2c_test(): register value: (0x%X)\n", value4);
        printf("i2c message: i2c_test(): register value: (0x%X)\n", value5);
        _delay_ms(2000);
    }
}
