#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(){
    DDRD &= ~(1<<2); //DDRD = DDRD & ~(1<<2)
    DDRB |= (1<<0);

    EICRA |= (1<<ISC01); //this is not shifting. this i like assigning
    EICRA &= ~(1<<ISC00);

    sei();

    EIMSK |= (1<<INT0);

    while(1){

    }
    return 0;
}

ISR(INT0_vect){
    PORTB ^= (1<<0); //setting the bit
    _delay_ms(500);
}