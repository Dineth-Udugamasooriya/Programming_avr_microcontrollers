
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <time.h>

unsigned  char z =0;
unsigned char timer = 0;

int main(){

    DDRD &= ~(1<<2); 

    DDRB = 0x3F; 

    EICRA |= (1<<ISC01);

    EICRA &= ~(1<<ISC00); 

    sei ();

    EIMSK |= (1<<INT0);

    while (1) {
        _delay_ms(470); //to solve debouncing issue
        timer = timer+1;

    }

    return 0;

} 


ISR (INT0_vect) {
  

  if ( timer >= 1 ) {
    z += 1;
    PORTB = z;
    timer = 0; //to avoid triggering two ISRs in a one loop
  }


  
}