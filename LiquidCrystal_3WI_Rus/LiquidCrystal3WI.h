/*
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

For more information about LiquidCrystal_3WI library please visit us at
http://www.arduino.cc/en/Reference/LiquidCrystal

This library is the fork of LiquidCrystal:
For more information about LiquidCrystal library please visit us at
http://www.arduino.cc/en/Reference/LiquidCrystal
 */

#ifndef LiquidCrystal3WI_h
#define LiquidCrystal3WI_h

#include <inttypes.h>
#include "Print.h"

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

#define SEND_BIT(DATA_PIN, CLOCK_PIN, BIT) {digitalWrite(DATA_PIN, BIT); \
											digitalWrite(CLOCK_PIN, HIGH); \
											digitalWrite(CLOCK_PIN, LOW); \
											digitalWrite(DATA_PIN, LOW);}

PROGMEM const char toPage1_1[] = {	0x41, 0xA0, 0x42, 0xA1, 0xE0, 0x45, 0xA3, 0xA4, 0xA5, 0xA6, /* А Б В Г Д Е Ж З И Й */
									0x4B, 0xA7, 0x4D, 0x48, 0x4F, 0xA8, 0x50, 0x43, 0x54, 0xA9, /* К Л М Н О П Р С Т У */
									0xAA, 0x58, 0xE1, 0xAB, 0xAC, 0xE2, 0xAD, 0xAE, 0x08, 0xAF, /* Ф Х Ц Ч Ш Щ Ъ Ы Ь Э */
									0xB0, 0xB1, 0x61, 0xB2, 0xB3, 0xB4, 0xE3, 0x65, 0xB6, 0xB7, /* Ю Я а б в г д е ж з */
									0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0x6F, 0xBE				/* и й к л м н о п */
									};

PROGMEM const char toPage1_2[] = {	0x70, 0x63, 0xBF, 0x79, 0xE4, 0x78, 0xE5, 0xC0, 0xC1, 0xE6, /* р с т у ф х ц ч ш щ */
									0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7							/* ъ ы ь э ю я */
									};

template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
class LiquidCrystal3WI : public Print {
public:
  LiquidCrystal3WI();
  LiquidCrystal3WI(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);
  virtual ~LiquidCrystal3WI() {};

  void init();
    
  void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);

  void clear();
  void home();

  void noDisplay();
  void display();
  void noBlink();
  void blink();
  void noCursor();
  void cursor();
  void scrollDisplayLeft();
  void scrollDisplayRight();
  void leftToRight();
  void rightToLeft();
  void autoscroll();
  void noAutoscroll();

  void setRowOffsets(int row1, int row2, int row3, int row4);
  void createChar(uint8_t, uint8_t[]);
  void setCursor(uint8_t, uint8_t); 
  virtual size_t write(uint8_t);
  void command(uint8_t);
  
  void printUTF8(const char *utf8String);
  void printUTF8(uint16_t ch);

  void setBacklight(uint8_t srBacklightPin, bool on);

  using Print::write;
private:
  void send(uint8_t, uint8_t);
  void write4bits(uint8_t);
  void pulseEnable();

  void setupDisplayPins(uint8_t enablePin, uint8_t resetPin, uint8_t rwPin, uint8_t data, bool clearData);

  uint8_t _registerData;

  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;

  uint8_t _initialized;

  uint8_t _numlines;
  uint8_t _row_offsets[4];
};

template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
LiquidCrystal3WI()
{
  init();
}

template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
LiquidCrystal3WI(uint8_t cols, uint8_t rows, uint8_t charsize)
{
  init();
  begin(cols, rows, charsize);
}

template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
init()
{

	_registerData = 0;

	pinMode(arduinoDataPin, OUTPUT);
	digitalWrite(arduinoDataPin, LOW);
	pinMode(arduinoClockPin, OUTPUT);
	digitalWrite(arduinoClockPin, LOW);
	pinMode(arduinoLatchPin, OUTPUT);
	digitalWrite(arduinoLatchPin, LOW);

	_displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

	begin(16, 1);
}

template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
begin(uint8_t cols, uint8_t lines, uint8_t charsize) {
	if (lines > 1) {
		_displayfunction |= LCD_2LINE;
	}
	_numlines = lines;

	setRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);

	// for some 1 line displays you can select a 10 pixel high font
	if ((charsize != LCD_5x8DOTS) && (lines == 1)) {
		_displayfunction |= LCD_5x10DOTS;
	}

	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way before 4.5V so we'll wait 50
	delayMicroseconds(50000);
	// Now we pull both RS and R/W low to begin commands
	setupDisplayPins(LOW, LOW, LOW, 0, true);

	// this is according to the hitachi HD44780 datasheet
	// figure 24, pg 46

	// we start in 8bit mode, try to set 4 bit mode
	write4bits(0x03);
	delayMicroseconds(4500); // wait min 4.1ms

	// second try
	write4bits(0x03);
	delayMicroseconds(4500); // wait min 4.1ms

	// third go!
	write4bits(0x03);
	delayMicroseconds(150);

	// finally, set to 4-bit interface
	write4bits(0x02);

	// finally, set # lines, font size, etc.
	command(LCD_FUNCTIONSET | _displayfunction);

	// turn the display on with no cursor or blinking default
	_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	display();

	// clear it off
	clear();

	// Initialize to default text direction (for romance languages)
	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	// set the entry mode
	command(LCD_ENTRYMODESET | _displaymode);

}

/*
   in some 16x4 LCD when line 3 and 4 are not placed correctly you may try:
     setRowOffsets(0x00, 0x40, 0x14, 0x54)
   or
     setRowOffsets(0x00, 0x40, 0x10, 0x50)
 */
template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
setRowOffsets(int row0, int row1, int row2, int row3)
{
  _row_offsets[0] = row0;
  _row_offsets[1] = row1;
  _row_offsets[2] = row2;
  _row_offsets[3] = row3;
}

/********** high level commands, for the user! */
template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
clear()
{
  command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
home()
{
  command(LCD_RETURNHOME);  // set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
setCursor(uint8_t col, uint8_t row)
{
  const size_t max_lines = sizeof(_row_offsets) / sizeof(*_row_offsets);
  if ( row >= max_lines ) {
    row = max_lines - 1;    // we count rows starting w/0
  }
  if ( row >= _numlines ) {
    row = _numlines - 1;    // we count rows starting w/0
  }

  command(LCD_SETDDRAMADDR | (col + _row_offsets[row]));
}

// Turn the display on/off (quickly)
template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
noDisplay() {
  _displaycontrol &= ~LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
display() {
  _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
noCursor() {
  _displaycontrol &= ~LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
cursor() {
  _displaycontrol |= LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
noBlink() {
  _displaycontrol &= ~LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
blink() {
  _displaycontrol |= LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
scrollDisplayLeft(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
scrollDisplayRight(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
leftToRight(void) {
  _displaymode |= LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
rightToLeft(void) {
  _displaymode &= ~LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
autoscroll(void) {
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
noAutoscroll(void) {
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
createChar(uint8_t location, uint8_t charmap[]) {
  location &= 0x7; // we only have 8 locations 0-7
  command(LCD_SETCGRAMADDR | (location << 3));
  for (int i=0; i<8; i++) {
    write(charmap[i]);
  }
}

/*********** mid level commands, for sending data/cmds */
template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
inline void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
command(uint8_t value) {
  send(value, LOW);
}

template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
inline size_t LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
write(uint8_t value) {
  send(value, HIGH);
  return 1; // assume sucess
}

/************ low level data pushing commands **********/

// write either command or data, with automatic 4/8-bit selection
template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
send(uint8_t value, uint8_t mode) {
	//	digitalWrite(_rs_pin, mode);
	setupDisplayPins(-1, mode, -1, -1, false);

	// if there is a RW pin indicated, set it low to Write
	//	if (_rw_pin != 255) {
	//		digitalWrite(_rw_pin, LOW);
	//	}
	setupDisplayPins(-1, -1, LOW, -1, false);

	write4bits(value >> 4);
	write4bits(value);
}

template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
pulseEnable(void) {
	//	digitalWrite(_enable_pin, LOW);
	setupDisplayPins(LOW, -1, -1, -1, false);
	delayMicroseconds(1);
	//	digitalWrite(_enable_pin, HIGH);
	setupDisplayPins(HIGH, -1, -1, -1, false);
	delayMicroseconds(1);    // enable pulse must be >450ns
	//	digitalWrite(_enable_pin, LOW);
	setupDisplayPins(LOW, -1, -1, -1, false);
	delayMicroseconds(100);   // commands need > 37us to settle
}

template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
write4bits(uint8_t value) {
	setupDisplayPins(-1, -1, -1, value, true);
	pulseEnable();
}

template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
setupDisplayPins(uint8_t enablePin, uint8_t resetPin, uint8_t rwPin, uint8_t data, bool setData) {
	if (enablePin == 1) {
		_registerData |= 1 << srEnable;
	} else if (enablePin == 0) {
		_registerData &= ~(1 << srEnable);
	}

	// rwPin isn't used, no read operation

	if (resetPin == 1) {
		_registerData |= 1 << srReset;
	} else if (resetPin == 0) {
		_registerData &= ~(1 << srReset);
	}
	if (setData) {
		data &= 0x0F;
		if (data & 1) {
			_registerData |= 1 << srDB4;
		} else {
			_registerData &= ~(1 << srDB4);
		}
		if (data & 2) {
			_registerData |= 1 << srDB5;
		} else {
			_registerData &= ~(1 << srDB5);
		}
		if (data & 4) {
			_registerData |= 1 << srDB6;
		} else {
			_registerData &= ~(1 << srDB6);
		}
		if (data & 8) {
			_registerData |= 1 << srDB7;
		} else {
			_registerData &= ~(1 << srDB7);
		}
	}

	for (uint8_t i = 0b10000000; i > 0; i /= 2) {
		uint8_t b = i & _registerData ? HIGH : LOW;
		SEND_BIT(arduinoDataPin, arduinoClockPin, b);
	}
	digitalWrite(arduinoLatchPin, HIGH);
	digitalWrite(arduinoLatchPin, LOW);
}

template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
printUTF8(const char *utf8String) {
	const unsigned char *from = (unsigned char *) utf8String;
	for (size_t i = 0; from[i] != 0; i++) {
		if ((from[i] == 0xD0) || (from[i] == 0xD1)) {
			uint16_t ch = from[i++] * 0x100;
			ch += from[i];
			printUTF8(ch & 0xFFFF);
		} else {
			print(utf8String[i]);
		}
	}
}

template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::
printUTF8(uint16_t ch) {
	if (page2) {
		if ((ch >= 0xD090) && (ch <= 0xD0BF)) { // small letters 'а' .. 'п'
			ch &= 0xFF;
			print((char) (ch + 0x30));
		} else if ((ch >= 0xD180) && (ch <= 0xD18F)) { // small letters 'р' .. 'я'
			ch &= 0xFF;
			print((char) (ch + 0x70));
		} else if (ch == 0xD081) { // letter 'Ё'
			print((char) 0xA8);
		} else if (ch == 0xD191) { // letter 'ё'
			print((char) 0xB8);
		} else {
			print((char) ch);
		}
	} else {
		if ((ch >= 0xD090) && (ch <= 0xD0BF)) { // small letters 'а' .. 'п'
			ch &= 0xFF;
			print((char) pgm_read_byte(&toPage1_1[ch - 0x90]));
		} else if ((ch >= 0xD180) && (ch <= 0xD18F)) { // small letters 'р' .. 'я'
			ch &= 0xFF;
			print((char) pgm_read_byte(&toPage1_2[ch - 0x80]));
		} else if (ch == 0xD081) { // letter 'Ё'
			print((char) 0xA2);
		} else if (ch == 0xD191) { // letter 'ё'
			print((char) 0xB5);
		} else {
			print((char) ch);
		}
	}
}

template<uint8_t arduinoDataPin,
			uint8_t arduinoClockPin,
			uint8_t arduinoLatchPin,
			uint8_t srDB4,
			uint8_t srDB5,
			uint8_t srDB6,
			uint8_t srDB7,
			uint8_t srEnable,
			uint8_t srReset,
			bool page2>
void LiquidCrystal3WI<arduinoDataPin,arduinoClockPin,arduinoLatchPin,srDB4,srDB5,srDB6,srDB7,srEnable,srReset,page2>::setBacklight(uint8_t srBacklightPin, bool on) {
	if (on) {
		_registerData |= 1 << srBacklightPin;
	} else {
		_registerData &= ~(1 << srBacklightPin);
	}
	setupDisplayPins(-1, -1, -1, -1, false);
}

#endif
