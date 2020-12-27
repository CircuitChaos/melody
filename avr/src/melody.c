#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include "tim0.h"
#include "adc.h"
#include "io.h"

int main(void)
{
	io_init();
	wdt_enable(WDTO_30MS);
	tim0_init();
	adc_init();
	sei();

	set_sleep_mode(SLEEP_MODE_IDLE);
	for (;;)
	{
		sleep_mode();
		wdt_reset();
	}

	/* NOTREACHED */
	return 0;
}
