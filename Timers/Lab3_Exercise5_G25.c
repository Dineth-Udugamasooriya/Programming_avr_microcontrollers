#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char trigger_counter = 0;

int main(void){
    DDRB = 0x20; //PB5 is output

    TCNT0 = 0; //timer 0 initial value

    //Timer 0 interrupt
    TCCR0A = 0x00;
    TCCR0B = 0x05; //prescaler 1024

    sei();

    TIMSK0 |= (1<<TOIE0); //Enable Timer 0 overflow interrupt

    while(1){

    }

    return 0;

}

//max value from timer 0 with 1024 (highest prescalar) = 16 ms
//to measure 100 ms number of times the ISR should trigger = 100ms/16ms = 6.25 ~ 6
//6 times

ISR(TIMER0_OVF_vect){ //Timer 0 overflow vector
    trigger_counter++;
    if(trigger_counter == 6){
        PORTB ^= (1<<5);
        trigger_counter = 0; 
    }

}