#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void){

    DDRB |= 0x2F; // 0010 1111 = 2F --> PB0, PB1, PB02, PB3 for knight rider and PB5 for blink led

    // PORTB = 0x00; //before going into the while loop PORTB is zero

    TCNT1 = 3036; // initial timer 1 counter value

    TCCR1A = 0x00; //normal mode
    TCCR1B = 0x04; //prescalar 256

    sei();        // Enable global interrupts
    
    TIMSK1 |= (1 << TOIE1) ;   // Enable timer1 overflow interrupt(TOIE1); 

    /////// knight rider pattern
    unsigned char z;
    
    
    while(1){
      for (z = 0; z < 4; z++) {
        PORTB |= (1<<z); // Turn on LED at position z without affecting other bits in port B
        _delay_ms(1000);   
        PORTB &= ~(1<<z); 
      }
      for (z = 3; z >= 1; z--) {
          PORTB |= (1<<z); // Turn on LED at position z
          _delay_ms(1000);
          PORTB &= ~(1<<z);  
        }
    }
    //// end of knight rider pattern

    return 0; 
}

ISR(TIMER1_OVF_vect){
    PORTB = PORTB ^ (1 << 5); //toggle PB5
    TCNT1 = 3036; //after triggring ISR program return inside the while loop. In there we haven't defined any initial value for timer 1.
    //without that we can't identify how many increments needed before an overflow
    //therefore we define this again
}

ISR(TIMER_0VF_vect){
    PORTB = PORTB ^ (1 << 5); //toggle PB5
    TCNT0 = 3036; //after triggring ISR program return inside the while loop. In there we haven't defined any initial value for timer 1.
    //without that we can't identify how many increments needed before an overflow
    //therefore we define this again
    }