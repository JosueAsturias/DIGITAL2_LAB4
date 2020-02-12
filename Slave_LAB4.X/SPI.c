 /*
 * File            : spi.c
 * Author          : Ligo George
 * Company         : electroSome
 * Project         : SPI Library for MPLAB XC8
 * Microcontroller : PIC 16F877A
 * Created on April 15, 2017, 5:59 PM
 */

#include <xc.h>
#include "SPI.h"


void SPI_init(spi_modo modo, spi_sample muestra, spi_clk_idle idle, 
              spi_transmit_edge edge){
    TRISC5 = 0; //SDO salida
    if (modo & 0x04){  // si es esclavo
        SSPSTAT = edge;
        TRISC3 = 1;   // SCK entra
    }
    else{ //master
        SSPSTAT = muestra | edge; 
        TRISC3 = 0; // SCK salida
    }
    SSPCON = modo | idle;
}

void SPI_write(uint8_t dato){
    SSPBUF = dato;
}

uint8_t SPI_read(){
    while(!SSPSTATbits.BF);
    return(SSPBUF);
}