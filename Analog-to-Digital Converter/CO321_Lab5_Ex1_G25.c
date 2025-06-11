#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
    DDRD = 0xFF; // PORTD as output
    // DDRC &= ~(1 << 1); // Set pin PC1 as input

    ADMUX = (1 << REFS0) | (1 << ADLAR) | (1 << MUX0);                               // AVCC with external capacitor at AREF pin, left adjusted, ADC1
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // ADC enabled, interrupt enable, prescaler 128

    sei(); // enable global interrupts

    ADCSRA |= (1 << ADSC); // start conversion

    while (1)
    {
    }
    return 0;
}

ISR(ADC_vect)
{
    PORTD = ADCH;          // output ADC value to PORTD
    ADCSRA |= (1 << ADSC); // start conversion so that the next ISR can recognize it.
}