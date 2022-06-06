#include <compat/twi.h>
#include <stdio.h>
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define SCL_CLOCK 400000
#define STATUS_START_TRANSMITTED 0x08
#define STATUS_REPEATED_START_TRANSMITTED 0x10
#define STATUS_SLA_W_TRANSMITTED_ACK 0x18
#define STATUS_SLA_W_TRANSMITTED_NACK 0x20
#define STATUS_DATA_TRANSMITTED_ACK 0x28
#define STATUS_DATA_TRANSMITTED_NACK 0x30
#define STATUS_SLA_R_TRANSMITTED_ACK 0x40
#define STATUS_SLA_R_TRANSMITTED_NACK 0x48
#define STATUS_DATA_RECEIVED_ACK 0x50
#define STATUS_DATA_RECEIVED_NACK 0x58

#define OPERATION_READ 1
#define OPERATION_WRITE 0

void i2c_init()
{
    TWSR = 0;                              // geen prescaler
    TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2; // de formule is: SCL_CLOCK = CPU_CLOCK/(16+2(TWBR)*4^TWPS)
}

int i2c_wait_twint()
{
    uint16_t timer = UINT16_MAX;

    while (timer > 0 && !(TWCR & (1 << TWINT)))
    {
        timer--;
    }

    if (timer == 0)
    {
        printf("i2c error: i2c_wait_twint(): timeout\n");
        return 1;
    }
    return 0;
}

int i2c_send_start_condition()
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    if (i2c_wait_twint())
    {
        printf("i2c error: i2c_send_start_condition(): timeout\n");
        return 1;
    }

    if (!(((TWSR & 0xF8) == STATUS_START_TRANSMITTED) || ((TWSR & 0xF8) == STATUS_REPEATED_START_TRANSMITTED))) // Check value of TWI Status Register. Mask prescaler bits. If status different from START go to ERROR
    {
        printf("i2c error: i2c_send_start_condition(): start not transmitted (0x%X)\n", (TWSR & 0xF8));
        return 1;
    }
    return 0;
}

int i2c_send_operation(uint8_t address, uint8_t operation)
{
    TWDR = address | operation;
    TWCR = (1 << TWINT) | (1 << TWEN);

    if (i2c_wait_twint())
    {
        printf("i2c error: i2c_send_operation(): timeout\n");
        return 1;
    }

    if (!(((TWSR & 0xF8) == STATUS_SLA_W_TRANSMITTED_ACK) || ((TWSR & 0xF8) == STATUS_SLA_R_TRANSMITTED_ACK))) // Check value of TWI Status Register. Mask prescaler bits. If status different from MT_SLA_ACK go to ERROR
    {
        printf("i2c error: i2c_send_operation(): operation not transmitted (0x%X)\n", (TWSR & 0xF8));
        return 1;
    }
    return 0;
}

int i2c_write(uint8_t data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);

    if (i2c_wait_twint())
    {
        printf("i2c error: i2c_send_data(): timeout\n");
        return 1;
    }

    if ((TWSR & 0xF8) != STATUS_DATA_TRANSMITTED_ACK)
    {
        printf("i2c error: i2c_send_data(): data not transmitted (0x%X)\n", (TWSR & 0xF8));
        return 1;
    }
    return 0;
}

int i2c_stop()
{
    uint16_t timer = UINT16_MAX;
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

    while (timer > 0 && (TWCR & (1 << TWSTO)))
    {
        timer--;
    }

    if (timer == 0)
    {
        printf("i2c error: i2c_wait_twint(): timeout\n");
        return 1;
    }
    return 0;
}

uint8_t i2c_read_ack()
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    if (i2c_wait_twint())
    {
        printf("i2c error: i2c_read_ack(): timeout\n");
        return 0;
    }

    return TWDR;
}

uint8_t i2c_read_nak()
{
    TWCR = (1 << TWINT) | (1 << TWEN);
    if (i2c_wait_twint())
    {
        printf("i2c error: i2c_read_ack(): timeout\n");
        return 0;
    }
    return TWDR;
}

void i2c_write_register(uint8_t address, uint8_t reg, uint8_t data)
{
    i2c_send_start_condition();
    i2c_send_operation(address, OPERATION_WRITE);
    i2c_write(reg);
    i2c_write(data);
    i2c_stop();
}

uint8_t i2c_read_register(uint8_t address, uint8_t reg)
{
    i2c_send_start_condition();
    i2c_send_operation(address, OPERATION_WRITE);
    i2c_write(reg);
    i2c_send_start_condition();
    i2c_send_operation(address, OPERATION_READ);
    uint8_t value = i2c_read_nak();
    i2c_stop();
    return value;
}

uint16_t i2c_read_16bit_register(uint8_t address, uint8_t reg)
{
    i2c_send_start_condition();
    i2c_send_operation(address, OPERATION_WRITE);
    i2c_write(reg);
    i2c_send_start_condition();
    i2c_send_operation(address, OPERATION_READ);
    uint16_t value = i2c_read_ack() << 8;
    value |= i2c_read_nak();
    i2c_stop();
    return value;
}

void i2c_search()
{
    printf("i2c message: i2c_search(): searching..\n");
    for (uint8_t i = 0; i < 0b1111111; i++)
    {
        uint8_t address = (i << 1);
        printf("i2c message: i2c_search(): trying address (0x%X)\n", address);
        if (!i2c_send_start_condition() && !i2c_send_operation(address, OPERATION_WRITE))
        {
            printf("i2c message: i2c_search(): found address: (0x%X) <---------------------------------\n", address);
        }
        i2c_stop();
    }
    printf("i2c message: i2c_search(): done\n");
}

void i2c_test()
{
    while (1)
    {
        i2c_search();
        printf("i2c message: i2c_test(): waiting 10 seconds for next search..\n");
        _delay_ms(10000);
    }
}
