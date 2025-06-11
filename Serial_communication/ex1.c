#include <avr/io.h>

void usart_init(void)
{
    // bauda rate 9600
    UBRR0H = 0x00;
    UBRR0L = 0x67;

    // no parity, 1 stop bit, 8 data
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    // this can also write as
    // UCSR0C = (1<<UCSZ01)|(1<<UCSZ00)|(0<<UMSEL00)|(0<<USBS0);
    // UMSEL00 = 0, asynchronous mode
    // USBS0 = 0, 1 stop bit

    // normal mode, disable multi protocol
    UCSR0A = 0x00;
}

void usart_send(unsigned char data)
{
    // enable transmitter
    UCSR0B = (1 << TXEN0);
    // wait for the empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    // write data to UDR0
    UDR0 = data;
}

unsigned char usart_recieve()
{
    // enable reciever
    UCSR0B = (1 << RXEN0);
    // wait for the data to be received -> when RXC0 is 1, the buffer is full
    while (!(UCSR0A & (1 << RXC0)))
        ;
    // read the data from UDR0
    return UDR0;
}