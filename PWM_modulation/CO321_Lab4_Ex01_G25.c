#include <avr/io.h>

int main(void)
{
    DDRD |= 0x60;  // 0110 0000

    PORTD |= (1<<5);

    OCR0A = 127;  // Set PWM for 50% duty cycle at 8-bit

    TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
    // Set non-inverting mode, set fast PWM Mode with TOP = 0xFF

    TCCR0B |= 0x03;  // Set prescaler to 64 and start PWM

    while (1)
    {
        // Your main code here
    }

    return 0;
}
