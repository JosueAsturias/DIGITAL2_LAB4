/*
 * File:   SlaveMain.c
 * Author: josue
 *
 * Created on February 11, 2020, 2:53 PM
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
#include "ADC.h"
uint8_t banderaADC = 0;
uint8_t valorADC_CH5 = 0;
uint8_t valorADC_CH0 = 0;
uint8_t instruccion = 0;

void __interrupt() ISR(){
    if(ADIE && ADIF){
        banderaADC = 1;
    }
}
void main(void) {
    ADConfig(4,0,'H');
    SPI_init(SPI_SLAVE_SS_DI,SPI_SAMPLE_MID,SPI_CLK_IDLE_LOW,SPI_IDLE_TO_ACTIVE);
    while(1){
        if (banderaADC){
            switch (ADCON0bits.CHS){
                case 5:
                    valorADC_CH5 = AnalogRead_8('H');
                    ADC_CHselect(0);
                    break;
                case 0:
                    valorADC_CH0 = AnalogRead_8('H');
                    ADC_CHselect(5);
                    break;
                default:
                    valorADC_CH0 = 0;
                    valorADC_CH5 = 0; 
            }
            banderaADC = 0;
            PIR1bits.ADIF = 0;
            PIE1bits.ADIE = 1;
            ADCON0bits.GO_nDONE = 1;
        }
        //enviar /recibir
    }
    return;
}
