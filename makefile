LDFLAGS = -nostdlib -O2 -static -T linker.ld
CFLAGS  = -mcpu=arm1176jzf-s -fpic -ffreestanding -I./include -Wall

CROSS_PREFIX = arm-none-eabi-
OBJCOPY      = ${CROSS_PREFIX}objcopy
CC           = ${CROSS_PREFIX}gcc
AS           = ${CROSS_PREFIX}as
LD           = ${CROSS_PREFIX}ld

OBJ = boot.o mmio.o uart.o main.o string.o

all: ${OBJ} elf kernel.bin
elf: ${OBJ}
	${LD} -o $@ ${LDFLAGS} ${OBJ}
kernel.bin: elf
	${OBJCOPY} elf -O binary $@

clean:
	rm -rf ${OBJ} elf kernel.bin
