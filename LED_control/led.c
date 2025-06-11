#include <avr/io.h>
#include <util/delay.h>

int main (void) {
    unsigned char z;
    DDRB = 0xFF;

    while(1){
        for (z = 1; z <= 16;) {
            PORTB = z;
            _delay_ms(250); // Add a delay of 500 milliseconds
             z = z<<1;
        }

        for (z = 16; z > 1;) {
            PORTB = z;
            _delay_ms(250); // Add a delay of 500 milliseconds
             z = z>>1;
        }


    }
    
        /* for (z = 8; z >= 1; z/2) {
            PORTB = z;
            _delay_ms(500); // Add a delay of 500 milliseconds
        } */
        // z = 1;




    return 0;
    // DDRB = 0xFF;

    /* while (1)
    {
        DDRB = 0xFF;
        PORTB = DDRB;
        _delay_ms(1000);
        DDRB = 0x00;
        PORTB = DDRB;
        _delay_ms(1000);
    } */
    
}
