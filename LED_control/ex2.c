#include <avr/io.h>
#include <util/delay.h>

int main (void) {
    unsigned char z;
    
    DDRB = 0x3F;
    
    while(1){
      for (z = 0; z < 4; z++) {
        PORTB = (1<<z); // Turn on LED at position z
        _delay_ms(150);    
      }
      for (z = 3; z >= 1; z--) {
          PORTB = (1<<z); // Turn on LED at position z
          _delay_ms(150);  
        }
    }

    return 0;    
}
