#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
    DDRD = 0xFF; // PORTD as output
    // DDRC &= ~(1 << 1); // Set pin PC1 as input (this is not required since we are configuring ADC1 using ADCMUX register)

    ADMUX = (1 << ADLAR) | (1 << MUX0);                                              // Internal VREF turned off [(0<<REFS1)|(0<<REFS0), left adjusted, ADC1
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
    // usart_send(ADCH);
    if (ADCH < 85)
    {

        PORTD = 0x0F;
    }
    else
    {

        PORTD = 0x00;
    }
    ADCSRA |= (1 << ADSC); // start conversion so that the next ISR can recognize it.
}