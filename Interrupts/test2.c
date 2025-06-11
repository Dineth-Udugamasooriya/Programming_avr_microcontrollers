#include <avr/io.h>
#include <util/delay.h>

int main(void){
    DDRD = DDRD & ~(1<<7);
    DDRB = 0x3F;

    unsigned char z = 0;
    unsigned char a = 0;

    while(1){
        _delay_ms(100);
        if((PIND & (1<<7)) & ~a){
            z += 1;
            PORTB = z;
            a = 0;
        }
        else{
            a= 1;
        }
        
        // _delay_ms(100);
    }

    return 0;
}