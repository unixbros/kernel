.globl mmio_write
.globl mmio_read
.globl skip_cycles

mmio_read:
	ldr r0, [r0]
	bx lr

mmio_write:
	str r1, [r0]
	bx lr

skip_cycles:
	bx lr

