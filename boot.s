.section ".text.boot"

.globl _start

/*
     Entry point for the kernel.
     r15 -> should begin execution at 0x8000.
     r0 -> 0x00000000
     r1 -> 0x00000C42
     r2 -> 0x00000100 - start of ATAGS
     preserve these registers as argument for kmain
*/

_start:
	/* setup stack. */
	mov sp, #0x8000

	/* clear out bss. */
	ldr r4, =__bss_start
	ldr r9, =__bss_end
	mov r5, #0
	mov r6, #0
	mov r7, #0
	mov r8, #0
	b   need_fill

fill:
	stmia r4!, {r5-r8}

need_fill:
	/* If we are still below bss_end, loop. */
	cmp r4, r9
	bcc fill

	ldr r3, =kmain
	blx r3

halt:
	/* wait for event */
	wfe
	b halt
