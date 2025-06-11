#include <avr/io.h>

void EEPROMWrite(unsigned int address, char data)
{
    //////// wait for completion of previous write ///////

    // EECR - The EEProm Control Register
    // EEPE bit must be written to 1 to write the value into the EEPROM
    // while the EEPE bit of EECR register is 1 the EEPROM is busy writing
    while (EECR & (1 << EEPE))
        ;

    //////// set up address and data regs ///////

    // EEAR - The EEPROM Address Register (EEARH + EEARL)
    EEAR = address;
    // for write. EEDR register contains the data to be written to the EEPROM in the address given by EEAR
    EEDR = data;

    ////// write logical 1 to EEMPE  //////

    // otherwise setting EEPE will have no effect (no write will occur)
    EECR |= (1 << EEMPE);

    ////// start eeprom write  ///////

    // setting EEPE within four clock cycles after setting EEMPE will write data to the EEPROM at the selected address
    EECR |= (1 << EEPE);
}

char EEPROMread(unsigned int address)
{
    /////// wait for completion of writes //////

    // while the EEPE bit of EECR register is 1 the EEPROM is busy writing
    while (EECR & (1 << EEPE))
        ;

    ///// set up address /////

    EEAR = address;

    ///// start eeprom read /////

    // EEPROM read enable
    EECR |= (1 << EERE);

    ///// return data /////

    // EEDR contains the data read from the EEPROM at the selected address
    return EEDR;
}

void usart_init(void)
{
    // baud rate 9600
    UBRR0H = 0x00;
    UBRR0L = 0x67;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // no parity, 1 stop bit, 8 bit data
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    // this can also write as
    // UCSR0C = (1<<UCSZ01)|(1<<UCSZ00)|(0<<UMSEL00)|(0<<USBS0);
    // UMSEL00 = 0, asynchronous mode
    // USBS0 = 0, 1 stop bit

    /* // normal mode, disable multi protocol
    UCSR0A = 0x00; */
}

unsigned char usart_receive()
{

    // wait for the data to be received -> when RXC0 is 1, the buffer is full
    while (!(UCSR0A & (1 << RXC0)))
        ;
    // read the data from UDR0
    return UDR0;
}

int main(void)
{

    usart_init();

    unsigned int address = 0;

    char sentence[1024];
    char data;
    unsigned int i = 0;
    unsigned int j = 0;

    while (data != '\r')
    {
        data = usart_receive(); // Get the character from serial communication
        sentence[i] = data;     // Store it in the sentence array
        i++;                    // Increment the i by one
    }

    while (j <= i)
    {
        EEPROMWrite(address, sentence[j]); // Get characters one by one from sentence array and store it in EEPROM
        address++;
        j++;
    }

    return 0;
}