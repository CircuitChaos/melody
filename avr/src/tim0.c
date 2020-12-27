#include <avr/io.h>
#include "tim0.h"
#include "io.h"

void tim0_init(void)
{
	/* - OC0A toggled on compare match
	 * - WGM set to 0b010 (CTC mode)
	 * - prescaler disabled
	 */

	TCCR0A	= _BV(WGM01) | _BV(COM0A0);
	TCCR0B	= _BV(CS00);
}

void tim0_set(uint8_t ocr)
{
	OCR0A = ocr;
}
