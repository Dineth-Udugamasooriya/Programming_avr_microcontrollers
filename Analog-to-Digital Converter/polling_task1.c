#include <avr/io.h>
#include <util/delay.h>

void init_adc()
{
    // Set voltage reference to AVcc
    ADMUX |= (1 << REFS0);
    // Set ADC enable and prescaler to 128
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t read_adc_0()
{
    // ADC channel 0 is selected by default

    // Start ADC conversion
    ADCSRA |= (1 << ADSC);
    // Wait for conversion to complete
    while (ADCSRA & (1 << ADSC))
        ;
    // while (!(ADCSRA & (1 << ADIF)));
    // Return ADC result
    return ADC;
}

int main()
{
    // Initialize ADC
    init_adc();

    DDRD = 0xFF;  // Set PORTD as output
    PORTD = 0x00; // Set PORTD to 0

    while (1)
    {
        // Read analog input from ADC channel
        uint16_t adc_value = read_adc_0();

        // Code to display ADC value on PORTD as level meter
        if (adc_value < 64)
        {
            PORTD = 0b00000000;
        }
        else if (adc_value < 128)
        {
            PORTD = 0b00000001;
        }
        else if (adc_value < 256)
        {
            PORTD = 0b00000011;
        }
        else if (adc_value < 384)
        {
            PORTD = 0b00000111;
        }
        else if (adc_value < 512)
        {
            PORTD = 0b00001111;
        }
        else if (adc_value < 640)
        {
            PORTD = 0b00011111;
        }
        else if (adc_value < 768)
        {
            PORTD = 0b00111111;
        }
        else if (adc_value < 896)
        {
            PORTD = 0b01111111;
        }
        else if (adc_value < 1024)
        {
            PORTD = 0b11111111;
        }

        // Wait 50ms before updating output
        _delay_ms(50);
    }

    return 0;
}