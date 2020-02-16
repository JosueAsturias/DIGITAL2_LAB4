/*
 * File:   MasterMain.c
 * Author: jotas
 *
 * Created on February 11, 2020, 2:55 PM
 */
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


#include <xc.h>
#include <stdint.h>
#include <stdlib.h>
#include "UART.h"
#include "SPI.h"
#define _XTAL_FREQ 4000000
uint8_t order = 22;
uint8_t recibido_pot1 = 0;
uint8_t recibido_pot2 = 0;
uint8_t bandera_enviar = 0;
uint8_t valorSerial = 0;

void main(void) {
    TRISB = 0;
    PORTB = 0;
    SPI_init(SPI_MASTER_4,SPI_SAMPLE_MID,SPI_CLK_IDLE_LOW,SPI_IDLE_TO_ACTIVE);
    uart_init(300);
    
    while(1){
        if(PIR1bits.RCIF == 1){
            __delay_ms(50);
            PORTB = uartRC_Read();   
        }
//        PORTB = recibido_pot1;
        uartTX_Write(recibido_pot1);
        uartTX_Write(',');
//        __delay_ms(69);
        uartTX_Write(recibido_pot2);
        uartTX_Write('\n');
        switch(order){
            case 22:  //pedir pot1
                if (!bandera_enviar){
                    SPI_write(order);
                    __delay_ms(10);
                    bandera_enviar = 1;
                }
                if(BF){
                    recibido_pot1 = SSPBUF;
                    order = 66;
                    bandera_enviar = 0;
                }
                break;
            case 66:  //pedir pot2
                if(!bandera_enviar){
                    SPI_write(order);
                    __delay_ms(10);
                    bandera_enviar = 1;
                }
                if(BF){
                    recibido_pot2 = SSPBUF;
                    order = 22;
                    bandera_enviar = 0;
                }
                break;
            default:
                recibido_pot1 = 0;
                recibido_pot2 = 0;
        }
        
    }
    return;
}
