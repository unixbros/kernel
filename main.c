#include <sys/types.h>
#include <uart.h>

void
kmain(word r0, word r1, word atags) {
	uart_init();
	uart_puts("Hello World\r\n");


	for (;;)
		uart_putc(uart_getc());
}
