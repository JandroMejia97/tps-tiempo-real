/*
 * File:   main.c
 * Author: Alejandro Mejía
 *
 * Created on 30 de agosto de 2022, 08:34 PM
 */


#include <htc.h>

#define _XTAL_FREQ 1000000UL // 1MHz

int main(void) {
    // RB4 y RB5 como salidas
    TRISB = 0b11001111;
    // Enciendo los LEDs
    RB4 = 1;
    RB5 = 1;
    // RA0 y RA1 como entradas
    TRISA |= (1 << RA0) | (1 << RA1);

    while(1) {
    
    }
    return 0; 
}
