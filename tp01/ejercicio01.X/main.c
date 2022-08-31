/*
 * File:   main.c
 * Author: Alejandro Mejía
 *
 * Created on 30 de agosto de 2022, 08:34 PM
 */


#include <htc.h>

#define _XTAL_FREQ 1000000UL // 1MHz

uint8_t checkButton(uint8_t pin);

int main(void) {
    // RB4 y RB5 como salidas
    TRISB = 0b11001111;
    // Enciendo los LEDs
    //PORTB |= (1 << RB4) | (1 << RB5);
    RB4 = 1;
    RB5 = 1;
    // RA0 y RA1 como entradas
    TRISA |= (1 << RA0) | (1 << RA1);
    uint8_t pressed = 0;

    while(1) {
        pressed = checkButton(RA0);
        if (!pressed) {
            pressed = checkButton(RA1);
        }
        
        while (pressed) {
            RB4 = !RB4;
            RB5 = !RB5;
            __delay_ms(250);
        }
    }
    return 0; 
}

uint8_t checkButton(uint8_t pin) {
    if ((PORTA & (1 << pin)) == 0) {
        __delay_ms(10);
        while ((PORTA & (1 << pin)) == 0);
        __delay_ms(10);
        RB5 = 0;
        return 1;
    }
    return 0;
}
