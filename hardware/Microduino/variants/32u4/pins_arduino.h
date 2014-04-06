#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>

// Workaround for wrong definitions in "iom32u4.h".
// This should be fixed in the AVR toolchain.
#undef UHCON
#undef UHINT
#undef UHIEN
#undef UHADDR
#undef UHFNUM
#undef UHFNUML
#undef UHFNUMH
#undef UHFLEN
#undef UPINRQX
#undef UPINTX
#undef UPNUM
#undef UPRST
#undef UPCONX
#undef UPCFG0X
#undef UPCFG1X
#undef UPSTAX
#undef UPCFG2X
#undef UPIENX
#undef UPDATX
#undef TCCR2A
#undef WGM20
#undef WGM21
#undef COM2B0
#undef COM2B1
#undef COM2A0
#undef COM2A1
#undef TCCR2B
#undef CS20
#undef CS21
#undef CS22
#undef WGM22
#undef FOC2B
#undef FOC2A
#undef TCNT2
#undef TCNT2_0
#undef TCNT2_1
#undef TCNT2_2
#undef TCNT2_3
#undef TCNT2_4
#undef TCNT2_5
#undef TCNT2_6
#undef TCNT2_7
#undef OCR2A
#undef OCR2_0
#undef OCR2_1
#undef OCR2_2
#undef OCR2_3
#undef OCR2_4
#undef OCR2_5
#undef OCR2_6
#undef OCR2_7
#undef OCR2B
#undef OCR2_0
#undef OCR2_1
#undef OCR2_2
#undef OCR2_3
#undef OCR2_4
#undef OCR2_5
#undef OCR2_6
#undef OCR2_7

#define NUM_DIGITAL_PINS  22
#define NUM_ANALOG_INPUTS 6

#define TX_RX_LED_INIT	DDRD |= (1<<5), DDRB |= (1<<0)
#define TXLED0			PORTD |= (1<<5)
#define TXLED1			PORTD &= ~(1<<5)
#define RXLED0			PORTB |= (1<<0)
#define RXLED1			PORTB &= ~(1<<0)

static const uint8_t SDA = 18;
static const uint8_t SCL = 19;

static const uint8_t SS   = 10;
static const uint8_t MOSI = 11;
static const uint8_t MISO = 12;
static const uint8_t SCK  = 13;

// Mapping of analog pins as digital I/O
static const uint8_t A0 = 14;
static const uint8_t A1 = 15;
static const uint8_t A2 = 16;
static const uint8_t A3 = 17;
static const uint8_t A4 = 20;
static const uint8_t A5 = 21;


#define digitalPinToPCICR(p)    ((((p) >= 8 && (p) <= 13)) ? (&PCICR) : ((uint8_t *)0))
#define digitalPinToPCICRbit(p) 0
#define digitalPinToPCMSK(p)    ((((p) >= 8 && (p) <= 13)) ? (&PCMSK0) : ((uint8_t *)0))
#define digitalPinToPCMSKbit(p) 0

//	__AVR_ATmega32U4__ has an unusual mapping of pins to channels
extern const uint8_t PROGMEM analog_pin_to_channel_PGM[];
#define analogPinToChannel(P)  ( pgm_read_byte( analog_pin_to_channel_PGM + (P) ) )

#ifdef ARDUINO_MAIN

// On the Arduino board, digital pins are also used
// for the analog output (software PWM).  Analog input
// pins are a separate set.

// ATMEL ATMEGA32U4 / ARDUINO LEONARDO
//
// D0				PD2					RXD1/INT2
// D1				PD3					TXD1/INT3
// D2				PD1		SDA			SDA/INT1
// D3#				PD0		PWM8/SCL	OC0B/SCL/INT0
// D4		A6		PD4					ADC8
// D5#				PC6		???			OC3A/#OC4A
// D6#		A7		PD7		FastPWM		#OC4D/ADC10
// D7				PE6					INT6/AIN0
//
// D8		A8		PB4					ADC11/PCINT4
// D9#		A9		PB5		PWM16		OC1A/#OC4B/ADC12/PCINT5
// D10#		A10		PB6		PWM16		OC1B/0c4B/ADC13/PCINT6
// D11#				PB7		PWM8/16		0C0A/OC1C/#RTS/PCINT7
// D12		A11		PD6					T1/#OC4D/ADC9
// D13#				PC7		PWM10		CLK0/OC4A
//
// A0		D18		PF7					ADC7
// A1		D19		PF6					ADC6
// A2		D20 	PF5					ADC5
// A3		D21 	PF4					ADC4
// A4		D22		PF1					ADC1
// A5		D23 	PF0					ADC0
//
// New pins D14..D17 to map SPI port to digital pins
//
// MISO		D14		PB3					MISO,PCINT3
// SCK		D15		PB1					SCK,PCINT1
// MOSI		D16		PB2					MOSI,PCINT2
// SS		D17		PB0					RXLED,SS/PCINT0
//
// TXLED			PD5
// RXLED		    PB0
// HWB				PE2					HWB

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint16_t PROGMEM port_to_mode_PGM[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,
	(uint16_t) &DDRE,
	(uint16_t) &DDRF,
};

const uint16_t PROGMEM port_to_output_PGM[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
	(uint16_t) &PORTE,
	(uint16_t) &PORTF,
};

const uint16_t PROGMEM port_to_input_PGM[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t) &PINB,
	(uint16_t) &PINC,
	(uint16_t) &PIND,
	(uint16_t) &PINE,
	(uint16_t) &PINF,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
	PD, // D0 - PD2
	PD,	// D1 - PD3
	PD, // D2 - PD4
	PD,	// D3 - PD6
	PD,	// D4 - PD7
	PC, // D5 - PC6
	PC, // D6 - PC7
	PE, // D7 - PE6
	
	PB, // D8 - PB6
	PB,	// D9 - PB5
	PB, // D10 - PB4
	PB,	// D11 - MOSI - PB2
	PB, // D12 -MISO -  PB3
	PB, // D13 -SCK -  PB1

	PF,	// D14 - A0 - PF7
	PF, // D15 - A1 - PF6
	PF, // D16 - A2 - PF5
	PF, // D17 - A3 - PF4

	PD, // D18 - PD1
	PD, // D19 - PD0

	PF, // D20 - A4 - PF1
	PF, // D21 - A5 - PF0
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
	_BV(2), // D0 - PD2
	_BV(3),	// D1 - PD3
	_BV(4), // D2 - PD4
	_BV(6),	// D3 - PD6
	_BV(7),	// D4 - PD7
	_BV(6), // D5 - PC6
	_BV(7), // D6 - PC7
	_BV(6), // D7 - PE6

	_BV(6), // D8 - PB6
	_BV(5),	// D9 - PB5
	_BV(4), // D10 - PB4
	_BV(2),	// D11 - MOSI - PB2
	_BV(3), // D12 -MISO -  PB3
	_BV(1), // D13 -SCK -  PB1
			
	_BV(7),	// D14 - A0 - PF7
	_BV(6), // D15 - A1 - PF6
	_BV(5), // D16 - A2 - PF5
	_BV(4), // D17 - A3 - PF4
	
	_BV(1), // D18 - PD1
	_BV(0), // D19 - PD0
	
	_BV(1), // D20 - A4 - PF1
	_BV(0), // D21 - A5 - PF0
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
	NOT_ON_TIMER,	
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	TIMER4D,		/* 4 */
	TIMER3A,		/* 5 */
	TIMER4A,		/* 6 */
	NOT_ON_TIMER,	
	TIMER1B,		/* 8 */
	TIMER1A,		/* 9 */
	NOT_ON_TIMER,

	NOT_ON_TIMER,	
	NOT_ON_TIMER,	
	NOT_ON_TIMER,

	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,

	NOT_ON_TIMER,
	TIMER0B,		/* 19 */

	NOT_ON_TIMER,
	NOT_ON_TIMER,
};

const uint8_t PROGMEM analog_pin_to_channel_PGM[] = {
	7,	// A0				PF7					ADC7
	6,	// A1				PF6					ADC6	
	5,	// A2				PF5					ADC5	
	4,	// A3				PF4					ADC4
	1,	// A4				PF1					ADC1
	0,	// A5				PF0					ADC0	
};

#endif /* ARDUINO_MAIN */
#endif /* Pins_Arduino_h */
