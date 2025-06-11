#include <avr/io.h>

void usart_init()
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

int main(void)
{

    usart_init();

    /* while (1)
    {
        usart_send('a');
    }
    return 0; */

    char member1[] = {'U', 'D', 'U', 'G', 'A', 'M', 'A', 'S', 'O', 'O', 'R', 'I', 'Y', 'A', ' ', 'D', '.', 'P', '.', ' ', 'E', '/', '1', '9', '/', '4', '0', '9'};
    char member2[] = {'V', 'I', 'D', 'U', 'R', 'A', 'N', 'G', 'A', ' ', 'G', '.', 'G', '.', 'N', '.', ' ', 'E', '/', '1', '9', '/', '4', '1', '3'};
    char member3[] = {'W', 'E', 'E', 'R', 'A', 'S', 'H', 'I', 'N', 'G', 'H', 'A', ' ', 'W', '.', 'A', '.', 'C', '.', 'J', '.', ' ', 'E', '/', '1', '9', '/', '4', '2', '3'};

    int i = 0;
    while (member1[i] != '\0')
    {
        usart_send(member1[i]);
        i++;
    }

    i = 0;
    while (member2[i] != '\0')
    {
        usart_send(member2[i]);
        i++;
    }

    i = 0;
    while (member3[i] != '\0')
    {
        usart_send(member3[i]);
        i++;
    }

    return 0;
}