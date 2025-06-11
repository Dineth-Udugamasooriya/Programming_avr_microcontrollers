#include <avr/io.h>
#include <util/delay.h>

int main(void){
    DDRD = DDRD & ~(1<<7);
    DDRB = 0x3F;

    unsigned char z = 0;
    // unsigned char a = 0;

    while(1){
        unsigned int a =  PIND & (1<<7);
        _delay_ms(100);
        if(a){
            if(a != (PIND & (1<<7))){
                z += 1;
                PORTB = z;
            }
        }
        // _delay_ms(100);
    }

    return 0;
}