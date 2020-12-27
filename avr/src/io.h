#pragma once

#include <avr/io.h>

static inline void io_init()
{
	PORTB	= 0xe6;
	DDRB	= 0x11;
}

static inline void io_set_envelope()
{
	PORTB |= _BV(3) | _BV(4);
	DDRB |= _BV(3);
}

static inline void io_clr_envelope()
{
	DDRB &= (uint8_t) ~_BV(3);
	PORTB &= (uint8_t) ~(_BV(3) | _BV(4));
}
