
#ifndef LCD_H
#define LCD_H

#include "font.h"
#include <string.h>
#include <inttypes.h>
#include <avr/pgmspace.h>
#include "i2c.h"				// library for I2C-communication

/* TODO: define display controller */
#define SH1106

/* TODO: define display mode */
#define TEXTMODE				// TEXTMODE for only text to display

/* TODO: define font */
#define FONT ssd1306oled_font	// set font here, refer font-name at font.h/font.c

/* TODO: define I2C-address for display */
#define LCD_I2C_ADR 0x3C		//I2C slave-address

#ifndef YES
#define YES        1
#endif

#define NORMALSIZE 1
#define DOUBLESIZE 2

#define LCD_DISP_OFF        0xAE
#define LCD_DISP_ON         0xAF

#define WHITE				0x01
#define BLACK				0x00

#define DISPLAY_WIDTH        128
#define DISPLAY_HEIGHT        64

void lcd_command(uint8_t cmd[], uint8_t size);		// transmit command to display
void lcd_data(uint8_t data[], uint16_t size);		// transmit data to display
void lcd_init(uint8_t dispAttr);					// initialize lcd
void lcd_home(void);								// set cursor to 0,0
void lcd_invert(uint8_t invert);					// invert display
void lcd_sleep(uint8_t sleep);						// display goto sleep (power off)
void lcd_set_contrast(uint8_t contrast);			// set contrast for display
void lcd_puts(const char* s);						// print string, \n-terminated, from ram on screen
void lcd_puts_pF(const char* progmem_s);			// print string from flash on screen

void lcd_clrscr(void);								// clear screen
void lcd_gotoxy(uint8_t x, uint8_t y);				// set curser at pos x, y
// x means character
// y means line (page, refer lcd manual)
void lcd_putc(char c);								// print character on screen
void lcd_charMode(uint8_t mode);					// set size of chars
#endif /*  LCD_H  */
