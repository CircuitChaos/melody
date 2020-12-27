#include <avr/interrupt.h>
#include <avr/io.h>
#include "note.h"
#include "adc.h"
#include "tim0.h"
#include "io.h"

/* Called at 7,4 Hz */
static void beat(void)
{
	const uint8_t note = note_get();
	if (note != 0xFF)
	{
		tim0_set(note);
		io_set_envelope();
	}
}

/* Called at 74 Hz */
ISR(ADC_vect)
{
	/* Divisor to divide ADC frequency by 10 */
	static uint8_t div = 0;

	if (++div < 10)
	{
		if (div == 4)
			io_clr_envelope();

		return;
	}

	div = 0;
	beat();
}

void adc_init(void)
{
	ADMUX	= 0;
	ADCSRA	= _BV(ADEN) | _BV(ADSC) | _BV(ADATE) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
	ADCSRB	= 0;
}
