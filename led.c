#include <stdint.h>

#include "bcm2835_periph.h"
#include "mmio.h"

/* main function */
int led_enable(void) {

	uint32_t old;

	/* Enable GPIO18 in the proper GPFSEL register */

	/* clear out old value */
	/* bit 24 of GPFSEL1 */
	old=mmio_read(GPIO_GPFSEL1);
	old &= ~(0x7 << 24);
	old |= (1<<24);
	mmio_write(GPIO_GPFSEL1,old);

	/* Write 1 to the proper SET register (turn on the LED) */

	mmio_write(GPIO_GPSET0,(1<<18));

	return 0;
}
