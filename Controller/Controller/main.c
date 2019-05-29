#include <avr/io.h>
#include "lcd.h"
#include "uart.h"
#include "i2c.h"

uint16_t ADCValue;
uint16_t ADCValue2;

uint8_t up;
uint8_t right;

unsigned char message;

void main_print(int right, int up, int character)
{
	right = -right;
	uint8_t x = 10 + right;
	uint8_t y = 3 + up;
	
	lcd_gotoxy(x,y);  //line x column y
	i2c_start(LCD_I2C_ADR << 1);
	i2c_write(0x40);
	for (uint8_t i = 0; i < 6; i++)
	{
		i2c_write(pgm_read_byte(&(FONT[character][i])));
	}
	
	i2c_stop();
}

void clear_screen()
{
	lcd_clrscr();
}

int main(void)
{
	lcd_init(LCD_DISP_ON);  // init lcd and turn on
	
    while (1) 
    {
		//Toggle the LSB in the ADMUX register to switch between ADC0 and ADC1
		ADMUX ^= (1 << 0);
		
		ADCSRA |= (1<<ADSC); //In Free Running mode no external trigger, write this bit to 1 to start conversion
		
		// wait for conversion to complete...then ADSC becomes 0 again...till then, run loop continuously
		while(ADCSRA & (1<<ADSC));
		
		ADCValue = ADC; //Store ADC value
		
		up = (ADCValue/146)-3;
		
		ADMUX ^= (1 << 0);
		
		ADCSRA |= (1<<ADSC); //In Free Running mode, write this bit to 1 to start conversion
		
		// wait for conversion to complete...then ADSC becomes ’0? again...till then, run loop continuously
		while(ADCSRA & (1<<ADSC));
		
		ADCValue2 = ADC; //Store ADC value
		
		right = (ADCValue2/50)-10;
		
		if (right <= 1 && right >= -1)
		{
			if (up > 3)
			{
				message = 'F';
			}
			else if (up > 1)
			{
				message = 'f';
			}
			else if (up < -3)
			{
				message = 'B';
			}
			else if (up < -1)
			{
				message = 'b';
			}
			else
			{
				message = 'S';
			}
		}
		else if (up > 0)
		{
			if (right > 5)
			{
				message = 'R';
			}
			else if (right > 1)
			{
				message = 'r';
			}
			else if (right < -5)
			{
				message = 'L';
			}
			else if (right < -1)
			{
				message = 'l';
			}
		}
		else
		{
			message = 'S';
		}
//		uart0_putc(message);
//		main_print(0, 0, message);
		main_print(0, 3, 'w');
	}
}