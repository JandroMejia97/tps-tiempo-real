/*
 * File:   main.c
 * Author: Alejandro Mejía
 *
 * Created on 30 de agosto de 2022, 08:34 PM
 */


#include <htc.h>

#define _XTAL_FREQ 1000000UL // 1MHz

uint8_t checkButton(uint8_t pin);
static uint8_t pressed = 0;

void interrupt(void) {
    if (pressed) {
        RB4 = !RB4;
        RB5 = !RB5;
    }
    T0IF = 0;
    TMR0 = 10;
}

int main(void) {
    // RB4 y RB5 como salidas
    TRISB = 0b11001111;
    // Enciendo los LEDs
    RB4 = 1;
    RB5 = 1;
    // RA0 y RA1 como entradas
    TRISA |= (1 << RA0) | (1 << RA1);

    while(1) {
        if (!pressed) {
            pressed = checkButton(RA0);
            if (!pressed) {
                pressed = checkButton(RA1);
            }
            
            if (pressed) {
                // Timer
                PSA = 0;
                OPTION_REG = (OPTION_REG & 0b11111110) | 0b111;
                T0CS = 0;
                INTCON = 0b10100000;
                TMR0 = 10;
            }
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
