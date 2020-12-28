#include <stddef.h>
#include <stdint.h>
#include "serial.h"
#include "printk.h"
#include "delay.h"
#include "led.h"

void kernel_main(uint32_t r0, uint32_t r1, uint32_t *atags) {

	int ch;

	(void) r0;	/* Ignore boot method */

	/* Initialize Hardware */
	uart_init();

	led_enable();

	/* Pause so we don't scroll away boot messages before */
	/* The terminal emulator is ready */
	printk("Press any key to continue...\r\n");
	uart_getc();

	/* Print boot message */
// YOUR CODE HERE

	/* Print hardware version */

	printk("Detected processor type %x\r\n",r1);

	printk("Starting message loop\r\n");

	/* Loop forever, echoing what is typed */
	while (1) {
		ch=uart_getc();

		/* Convert to uppercase */
		if ((ch>='a') && (ch<='z')) ch-=32;

		uart_putc(ch);
	}
}
