#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
    DDRC &= ~(1 << 1);                      // Set pin PC1 as input
    DDRD |= (1 << 5);                       // Set pins PD2 as output
    ADCSRA |= (1 << ADEN);                  // Enable ADC
    ADCSRA |= (1 << ADPS2);                 // Set ADC prescaler to 16
    // ADMUX |= ((1 << REFS0) | (1 << REFS1)); // Set ADC reference voltage to AREF
    ADCSRA |= (1 << ADIE);                  // Enable ADC complete interrupt
    sei();                                  // Enable global interrupts
    ADCSRA |= (1 << ADIE);                  // Enable ADC complete interrupt

    while (1)
    {
    }

    return 0;
}

ISR(ADC_vect)
{
    ADCSRA |= (1 << ADSC); // Start ADC conversion
    while (ADCSRA & (1 << ADSC))
        ; // Wait for conversion to complete
    if (ADC >200)
    {
        PORTD |= (1 << 5); // Turn on the LED
    }
    else
    {
        PORTD &= ~(1 << 5); // Turn off the LED
    }
    _delay_ms(500); // Add a delay to avoid rapid changes (optional)
}