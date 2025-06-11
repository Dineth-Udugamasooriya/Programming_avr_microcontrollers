
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <time.h>

unsigned  char z =0;
unsigned char timer = 0;

int main(){

    DDRD &= ~((1<<2)|(1<<3)); //both port 2 and 3 are inputs

    DDRB = 0x3F; 

//For INT0 - works at rising edge
    EICRA |= (1<<ISC01);

    EICRA |= (1<<ISC00); 
//For INT1 - works at rising edge
    EICRA |= (1<<ISC11);

    EICRA |= (1<<ISC10); 

    sei ();

    EIMSK |= (1<<INT0); // for button A
    EIMSK |= (1<<INT1); // for button B
    //if we remove the above two lines the microcontroller will not respond to those external interrupt events, and the 
    //corresponding interrupt service routines (ISRs) defined for INT0_vect and INT1_vect will not be executed.

    while (1) {
        _delay_ms(470); //to solve debouncing issue
        timer = timer+1;

    }

    return 0;

} 

// input 0
ISR (INT0_vect) {
  
    if ( timer >= 1 ) {
        PORTB &= ~(1<<z);
        z += 1;
        timer = 0; //to avoid triggering two ISRs in a one loop
    }

}

//input 1
ISR (INT1_vect) {

    if ( timer >= 1 ) {
        PORTB |= 1<<z;
        z += 1;
        timer = 0; //to avoid triggering two ISRs in a one loop
    }

}