#include <inttypes.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>

static uint8_t note_to_ocr(uint8_t value)
{
	int tone, ocr;
	double freq;

	/* if it's pause, then return special value for the pause */
	if (value == 0)
		return 0xff;

	/* to make C0 first note */
	--value;

	/* transpose so the base octave is 4, note that tone can be
	 * negative now */
	tone = value - (12 * 4);

	/* calculate frequency, assuming that A4 is 440 Hz; we add 3 to
	 * the tone to make it relative to A, not to C */
	freq = 440. * pow(2, (double) (tone + 3) / 12);

	/* calculate OCR value */
	ocr = 128000. / 2 / freq;

	/* make sure that OCR is within range */
	assert(ocr < 0xFE);

	return ocr;
}

int main(void)
{
	uint8_t hdr[4];
	int row, num_rows;
	assert(fread(hdr, 4, 1, stdin) == 1);

	printf("\t");

	num_rows = hdr[2];
	for (row = 0; row < num_rows; ++row)
	{
		int track;

		for (track = 0; track < 32; ++track)
		{
			uint8_t data[5];
			assert(fread(data, 5, 1, stdin) == 1);

			/* use only first track */
			if (track != 0)
				continue;

			printf("0x%02x%s", note_to_ocr(data[0]), ((row + 1) % 8) ? ", " : ",\n\t");
		}
	}

	printf("0xfe\n");
	return 0;
}
