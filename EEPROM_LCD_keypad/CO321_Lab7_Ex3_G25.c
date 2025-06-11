/*************************************************************************
Title:    Testing output to a HD44780 based LCD display.
Author:   Peter Fleury  <pfleury@gmx.ch>  http://tinyurl.com/peterfleury
File:     $Id: test_lcd.c,v 1.8 2015/01/31 18:04:08 peter Exp $
Software: AVR-GCC 4.x
Hardware: HD44780 compatible LCD text display
          AVR with external SRAM interface if memory-mapped LCD interface is used
          any AVR with 7 free I/O pins if 4-bit IO port mode is used
**************************************************************************/
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <lcd.h>

#define ROWS 4
#define COLS 4

// Define the keypad layout
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// Define the pin connections
uint8_t rowPins[ROWS] = {PD6, PD7, PB0, PB1};
uint8_t colPins[COLS] = {PB2, PB3, PB4, PB5};

char getKeypadInput()
{
    for (int i = 0; i < ROWS; i++)
    {
        // Set row i low
        // PORTD &= ~(1 << rowPins[i]);
        if (i < 2)
        {
            PORTD &= ~(1 << rowPins[i]);
        }
        else
        {
            PORTB &= ~(1 << rowPins[i]);
        }

        for (int j = 0; j < COLS; j++)
        {
            // Check if column j is low
            if (!(PINB & (1 << colPins[j])))
            {
                // If it is, a button is pressed
                return keys[i][j];
            }
            // _delay_ms(20);
        }

        // Set row i high again
        PORTD |= (1 << rowPins[i]);
        PORTB |= (1 << rowPins[i]);
    }

    // No button was pressed
    return '\0';
}

void EEPROMWrite(unsigned int address, char data)
{
    while (EECR & (1 << EEPE))
        ;

    EEAR = address;
    EEDR = data;

    EECR |= (1 << EEMPE);

    EECR |= (1 << EEPE);
}

char EEPROMread(unsigned int address)
{

    while (EECR & (1 << EEPE))
        ;

    EEAR = address;

    EECR |= (1 << EERE);

    return EEDR;
}

char caesarCipherChar(char ch, int shift)
{
    // Encrypt uppercase letters
    if (ch >= 'A' && ch <= 'Z')
    {
        return (ch - 'A' + shift) % 26 + 'A';
    }

    // Encrypt lowercase letters
    else if (ch >= 'a' && ch <= 'z')
    {
        return (ch - 'a' + shift) % 26 + 'a';
    }

    // Return the original character if it's not a letter
    return ch;
}

void show_encrypt_text()
{
    char input = '\0';
    char text = '\0';
    char cipher_key;
    int i = 0;
    while (i < 10)
    {
        input = EEPROMread(i);
        if (input != '\0')
        {
            cipher_key = EEPROMread(12);
            text = caesarCipherChar(input, cipher_key);
            lcd_putc(text);
            i++;
        }
    }
}

void store_encrypt_text()
{
    lcd_clrscr();
    lcd_puts("Enter 10 characters: ");
    lcd_gotoxy(0, 1);

    char input;
    int i = 0;
    input = '\0';
    _delay_ms(100);
    while (i < 10)
    {
        _delay_ms(175);
        input = getKeypadInput();
        if (input != '\0')
        {
            lcd_putc(input);
            EEPROMWrite(i, input);
            i++;
        }

        input = '\0';
    }

    _delay_ms(1000);

    lcd_clrscr();
    lcd_puts("Encrpting Text:");
    _delay_ms(1000);
    lcd_clrscr();
    lcd_puts("Encrypted Text:");
    _delay_ms(1000);
    lcd_clrscr();
    lcd_puts("Go Back '#'");
    lcd_gotoxy(0, 1);
    show_encrypt_text();

    while (getKeypadInput() != '#')
    {
    }

    lcd_clrscr();
}

void change_key()
{
    lcd_clrscr();
    lcd_puts("Enter new key: ");
    lcd_gotoxy(0, 1);

    char input;
    // int i = 0;
    int j = 12;
    input = '\0';
    _delay_ms(100);
    while (1)
    {
        _delay_ms(175);
        input = getKeypadInput();
        if (input != '\0' && input != 'A' && input != 'B' && input != 'C' && input != 'D')
        {
            lcd_putc(input);
            EEPROMWrite(j, input - '0');
            _delay_ms(1000);
            break;
        }

        input = '\0';
    }

    _delay_ms(1000);

    lcd_clrscr();
    lcd_puts("New key set!");
    _delay_ms(1000);
    lcd_clrscr();
}

int main(void)
{
    /* initialize display, cursor off */
    lcd_init(LCD_DISP_ON);
    lcd_clrscr();

    // lcd_scroll(0, "Welcome to CeaserCipher V1.0!", "Choose action-~");

    lcd_puts("1. Encrypt\n2. Change secret");

    // from my keypad loop

    char key = '\0';

    // Set row pins (PD6, PD7) as outputs
    DDRD |= (1 << PD6) | (1 << PD7);

    // Set row pins (PB0, PB1) as outputs
    DDRB |= (1 << PB0) | (1 << PB1);

    // Set column pins (PB2-PB5) as inputs
    DDRB &= ~(1 << PB2) | ~(1 << PB3) | ~(1 << PB4) | ~(1 << PB5);

    // Enable internal pull-up resistors for column pins
    PORTB |= (1 << PB2) | (1 << PB3) | (1 << PB4) | (1 << PB5);

    // Loop
    while (1)
    {
        lcd_gotoxy(0, 0);
        lcd_puts("1. Encrypt\n2. Change Secret");

        key = getKeypadInput();

        if (key != '\0')
        {
            if (key == '1')
            {
                store_encrypt_text();
            }
            if (key == '2')
            {
                change_key();
            }
        }
    }

    return 0;
}
