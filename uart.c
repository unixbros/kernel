#include <sys/types.h>
#include <mmio.h>
#include <uart.h>

/*
 * GPIO14  TXD0 and TXD1
 * GPIO15  RXD0 and RXD1
 * alt function 5 for uart1
 * alt function 0 for uart0
 */

void
uart_putc(word c) {
	for (;;)
		if (mmio_read(AUX_MU_LSR_REG) & 0x20)
			break;

	mmio_write(AUX_MU_IO_REG, c);
}

word
uart_getc(void) {
	for (;;)
		if (mmio_read(AUX_MU_LSR_REG) & 0x01)
			break;

	return mmio_read(AUX_MU_IO_REG);
}

void
uart_puts(byte *str) {
	byte *p = str;

	while (*p)
		uart_putc(*p++);
}

void
uart_init() {
	word ra;

	mmio_write(AUX_ENABLES, 1);
	mmio_write(AUX_MU_IER_REG, 0);
	mmio_write(AUX_MU_CNTL_REG, 0);
	mmio_write(AUX_MU_LCR_REG, 3);
	mmio_write(AUX_MU_MCR_REG, 0);
	mmio_write(AUX_MU_IER_REG, 0);
	mmio_write(AUX_MU_IIR_REG, 0xC6);

	/* ((250,000,000/115200)/8)-1 = 270 */
	mmio_write(AUX_MU_BAUD_REG, 270);

	ra = mmio_read(GPFSEL1);
	ra &= ~(7 << 12); /* gpio14 */
	ra |=  (2 << 12); /* alt5   */
	ra &= ~(7 << 15); /* gpio15 */
	ra |=  (2 << 15); /* alt5   */
	mmio_write(GPFSEL1, ra);

	mmio_write(GPPUD, 0);

	for(ra = 0; ra < 150; ra++)
		skip_cycles(ra);

	mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));

	for(ra = 0; ra < 150; ra++)
		skip_cycles(ra);

	mmio_write(GPPUDCLK0, 0);
	mmio_write(AUX_MU_CNTL_REG, 3);
}
