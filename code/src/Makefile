CC=m68k-elf-gcc
CPU=68010
OUTDIR=../out
CFLAGS= -c -mcpu=$(CPU) -o0

main.o:main.c
	$(CC) $(CFLAGS) -o $(OUTDIR)/$@ $^

#vectors.o:vectors.c
#	$(CC) $(CFLAGS) -o $(OUTDIR)/$@ $^

clean:
	rm -rf *.o *.elf
