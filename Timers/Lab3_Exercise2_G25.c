#include <avr/io.h>
#include <util/delay.h>

void delay_timer0(){
       

        TCNT0 = 131;

        TCCR0A = 0x00;
        TCCR0B = 0x04; //prescaler 256

        while((TIFR0 & 0x01) == 0); //wait while overflow occurs

        TCCR0A = 0x00;
        TCCR0B = 0x00;

        TIFR0 = 0x01;


        
}

int main(void){
    DDRB = 0x3F;

    while(1){

        PORTB = PORTB ^ (1<<5);
        for (int i=0; i<250; ++i){ // 2ms x 250 = 500 ms
            delay_timer0();
        }
        

        
        //_delay_ms(100);

        /* PORTB = PORTB & ~(1<<5);
        _delay_ms(500); */
    }
}