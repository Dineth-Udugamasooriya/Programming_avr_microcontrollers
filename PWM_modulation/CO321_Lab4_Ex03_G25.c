//fade-in fade-out

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD |= 0x60;  // 0110 0000

    PORTD |= (1<<5);

    OCR0A = 150;  // Set PWM for 58.98% duty cycle at 8-bit

    TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
    // Set non-inverting mode, set fast PWM Mode with TOP = 0xFF

    uint8_t freequencies[] = {0x02, 0x03, 0x04, 0x05};

    

    while (1)
    {
        for (int i=0; i<4; ++i){
            TCCR0B = freequencies[i];
            _delay_ms(1000);
        }
        

    }

    return 0;
}
