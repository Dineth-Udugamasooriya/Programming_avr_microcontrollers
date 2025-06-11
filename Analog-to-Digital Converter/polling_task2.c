#include <avr/io.h>
#include <util/delay.h>

void init_adc()
{
    // Set voltage reference to AREF
    // By default
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

        // Turn on LED if ADC value is less than 500 (threshold value)
        // This threshold can be also adjusted using AREF
        if (adc_value < 500)
        {
            PORTD = 0xFF;
        }
        else
        {
            PORTD = 0x00;
        }

        // Wait 50ms before updating output
        _delay_ms(50);
    }

    return 0;
}