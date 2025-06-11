#include <avr/io.h>
#include <util/delay.h>

int main (void) {
    DDRB = 0xFF;

    while (1)
    {
        DDRB = 0xFF;
        PORTB = DDRB;
        _delay_ms(1000);
        PORTB = ~PORTB;
        _delay_ms(1000);
    }
    
    return 0;
}
