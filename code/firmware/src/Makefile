CC=m68k-elf-gcc
CPU=68010
OUTDIR=out/
CFLAGS= -c -nostdlib -mcpu=$(CPU) -o0 -std=gnu11 -Wall
LDFLAGS= -nostdlib -mcpu=$(CPU) -T firmware.ld -Wl,-Map=firmware.map
all: main.o boot.o mc68681.o firmware.elf firmware.bin
main.o:main.c
	$(CC) $(CFLAGS) $^ -o $@

boot.o:boot.c
	$(CC) $(CFLAGS) $^ -o $@ 

mc68681.o:mc68681.c
	$(CC) $(CFLAGS) $^ -o $@ 

firmware.elf: boot.o main.o mc68681.o
	$(CC) $(LDFLAGS) $^ -o $@

firmware.bin: firmware.elf
	m68k-elf-objcopy -O binary firmware.elf firmware.bin
	m68k-elf-objcopy -O srec firmware.elf firmware.h68

clean:
	rm -rf *.o *.elf *.map *.bin *h68 *.s19 *.srec

