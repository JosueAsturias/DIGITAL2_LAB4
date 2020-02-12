 /*
 * File            : spi.h
 * Author          : Ligo George
 * Company         : electroSome
 * Project         : SPI Library for MPLAB XC8
 * Microcontroller : PIC 16F877A
 * Created on April 15, 2017, 5:59 PM
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __SPI_H_
#define	__SPI_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

typedef enum {
    SPI_MASTER_4    = 0b00100000,
    SPI_MASTER_16   = 0b00100001,
    SPI_MASTER_64   = 0b00100010,
    SPI_MASTER_TMR2 = 0b00100011,
    SPI_SLAVE_SS_EN = 0b00100100,
    SPI_SLAVE_SS_DI = 0b00100101                 
}spi_modo;

typedef enum{
    SPI_SAMPLE_END = 0b10000000,
    SPI_SAMPLE_MID = 0b00000000
}spi_sample;

typedef enum{
    SPI_CLK_IDLE_LOW  = 0b00000000,
    SPI_CLK_IDLE_HIGH = 0b00010000
}spi_clk_idle;

typedef enum{
    SPI_IDLE_TO_ACTIVE = 0b00000000,
    SPI_ACTIVE_TO_IDLE = 0b01000000
}spi_transmit_edge;

void SPI_init(spi_modo modo, spi_sample muestra, spi_clk_idle idle, spi_transmit_edge edge);
void SPI_write(uint8_t dato);
uint8_t SPI_read();
#endif	