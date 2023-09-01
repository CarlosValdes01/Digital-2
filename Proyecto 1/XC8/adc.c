/*
 * File:   adc.c
 * Author: Estuardo Castillo
 *
 * Created on July 14, 2023, 5:28 PM
 */

#include "adc_config.h"
#include <xc.h>
#define _XTAL_FREQ 8000000

adc_init(int channel){
    //configuracion de ADC
    ADCON1bits.ADFM = 0;
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;
    ADCON0bits.ADCS = 0b10;
    
    /*clock select bits:
     * 1MHz 00
     * 4MHz 01
     * 8MHz 10
     */
    //configuracion de pin
    int var = var | (1<<channel);
    switch(channel){
        case 0:
            ANSEL = ANSEL | var;
            TRISA = TRISA | var;
            break;
        case 1:
            ANSEL = ANSEL | var;
            TRISA = TRISA | var;
            break;
        case 2:
            ANSEL = ANSEL | var;
            TRISA = TRISA | var;
            break;
        case 3:
            ANSEL = ANSEL | var;
            TRISA = TRISA | var;
            break;
        default:
            break;
    }
    //seleccion del canal
    ADCON0bits.CHS = channel;
    ADCON0bits.ADON = 1;
    __delay_us(50);
}

int adc_read (){
    // Iniciar conversion ADC
    ADCON0bits.GO = 1;
    while (ADCON0bits.GO);
    //__delay_us(100);  
    return ADRESH; //regresar valor convertido
}
adc_change_channel(int channel){
    ADCON0bits.CHS = channel; //canal para conversion
    __delay_us(50);
}
int adc_get_channel(){
    return ADCON0bits.CHS;
}                 //input              //output
int map (int val, int minx, int maxx, int miny, int maxy){
    //aca va el codigo
    double pendiente = 1.0 * (maxy - miny) / (maxx - minx);
    int output = miny + pendiente * (val - minx);
    return output;
}

float MAP_2(uint8_t IN, uint8_t INmin, uint8_t INmax, uint8_t OUTmin, uint8_t OUTmax){
    float valor;    
    valor = (float) (IN - INmin)*(OUTmax - OUTmin)/(INmax - INmin) + OUTmin;
    return valor;
}