/*
 * File:   main.c
 * Author: Alejandro Mej?a
 *
 * Created on 30 de agosto de 2022, 08:34 PM
 */


#include <htc.h>

#define _XTAL_FREQ 1000000UL // 1MHz

void interrupt manejador(void) {
	RB4 = !RB4;
	RB5 = !RB5;
    T0IF = 0;
    TMR0 = 12;
}

int main(void) {
    // RB4 y RB5 como salidas
    TRISB = 0b11001111;
    // Enciendo los LEDs
    RB4 = 1;
    RB5 = 1;
    // RA0 y RA1 como entradas
    TRISA |= (1 << RA0) | (1 << RA1);
	PSA = 0;
	OPTION_REG = (OPTION_REG & 0b11111110) | 0b111;
	T0CS = 0;
    while(1) {
		if ((PORTA & (1 << RA0)) == 0) {
			__delay_ms(30);
			if ((PORTA & (1 << RA0)) == 0){
				RB4 = !RB4;
				INTCON = 0b10100000;
				TMR0 = 12;
			}
		}
	}	
    return 0; 
}