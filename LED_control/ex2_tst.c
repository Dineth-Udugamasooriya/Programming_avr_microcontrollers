#include <avr/io.h>
#include <util/delay.h>

int main (void) {
    unsigned char z;
    

    while(1){
      for (z = 0; z <= 4; z++) {
        PORTB = DDRB | (1<<z);
        _delay_ms(150);    
      }
      for (z = 3; z > 1; z--) {
          PORTB = DDRB | (1<<z);
          _delay_ms(150);  
        }
    }

    return 0;    
}
