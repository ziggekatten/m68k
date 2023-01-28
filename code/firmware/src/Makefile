CC=m68k-elf-gcc
CPU=68010
OUTDIR=../out
CFLAGS= -c -nostdlib -mcpu=$(CPU) -o0 -std=gnu11 -Wall
LDFLAGS= -nostdlib -mcpu=$(CPU) -T firmware.ld -Wl,-Map=final.map
all: main.o boot.o firmware.elf
main.o:main.c
	$(CC) $(CFLAGS) $^ -o $@ 

boot.o:boot.c
	$(CC) $(CFLAGS) $^ -o $@ 

firmware.elf: boot.o main.o
	$(CC) $(LDFLAGS) $^ -o $@ 
clean:
	rm -rf *.o *.elf *.map

