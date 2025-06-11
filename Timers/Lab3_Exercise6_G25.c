#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char trigger_counter_0 = 1;

int main(void){
    DDRB = 0x03; //PB0 and PB1 are output

    TCNT0 = 0; //timer 0 initial value
    TCNT1 = 34286; //timer 1 initial value

    //Timer 0 mode
    TCCR0A = 0x00; //normal mode
    TCCR0B = 0x05; //prescaler 1024

    //Timer 1 mode
    TCCR1A = 0x00; //normal mode
    TCCR1B = 0x04; //prescaler 256

    sei(); //enable global interrupt

    TIMSK0 |= (1<<TOIE0); //Enable Timer 0 overflow interrupt
    TIMSK1 |= (1<<TOIE1); //Enable Timer 1 overflow interrupt

    while(1){

    }

    return 0;

}

//max value from timer 0 with 1024 (highest prescalar) = 16 ms
//to measure 100 ms number of times the ISR should trigger = 50ms/16ms = 3.125 ~ 3
//3 times

//Timer 0 interrupt service
ISR(TIMER0_OVF_vect){ //Timer 0 overflow vector
    trigger_counter_0++;
    if(trigger_counter_0 == 3){
        PORTB ^= (1<<0);
        trigger_counter_0 = 0; 
    }

}


//Timer 1 interrupt service
ISR(TIMER1_OVF_vect){ //Timer 1 overflow vector
    PORTB ^= (1<<1);
    TCNT1 = 34286;

}