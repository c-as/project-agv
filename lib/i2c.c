#include <compat/twi.h>
#include <stdio.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define SCL_CLOCK 400000
#define STATUS_START_TRANSMITTED 0x08
#define STATUS_SLA_W_TRANSMITTED 0x20
#define STATUS_SLA_W_TRANSMITTED_ACK 0x18
#define STATUS_DATA_TRANSMITTED 0x30
#define STATUS_DATA_TRANSMITTED_ACK 0x28

typedef enum
{
    OPERATION_READ,
    OPERATION_WRITE,
} I2COperation;

void i2c_init()
{
    TWSR = 0;                              // geen prescaler
    TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2; // de formule is: SCL_CLOCK = CPU_CLOCK/(16+2(TWBR)*4^TWPS)
}

void i2c_wait_twint()
{
    while (!(TWCR & (1 << TWINT)))
    {
    }
}

int i2c_send_start_condition()
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    i2c_wait_twint();
    if ((TWSR & 0xF8) != STATUS_START_TRANSMITTED) // Check value of TWI Status Register. Mask prescaler bits. If status different from START go to ERROR
    {
        printf("i2c error: start not transmitted\n");
        return 1;
    }
    return 0;
}

int i2c_send_operation(uint8_t address, I2COperation operation)
{
    TWDR = address;
    if (operation == OPERATION_WRITE)
    {
        TWCR = (1 << TWINT) | (1 << TWEN);
    }
    else if (operation == OPERATION_READ)
    {
        printf("i2c error: operation read not implemented\n");
        return 1;
    }
    i2c_wait_twint();
    if ((TWSR & 0xF8) != STATUS_SLA_W_TRANSMITTED_ACK) // Check value of TWI Status Register. Mask prescaler bits. If status different from MT_SLA_ACK go to ERRO
    {
        printf("i2c error: start not transmitted\n");
        return 1;
    }
    return 0;
}

void i2c_send_data(uint8_t data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
}

int i2c_write_register(uint8_t address, uint8_t data)
{
    i2c_send_start_condition();
    i2c_send_operation(address, OPERATION_WRITE);
}

void i2c_test()
{
    while (1)
    {
    }
}