CC=m68k-elf-gcc
CPU=68010
OUTDIR=../out
CFLAGS= -c -mcpu=$(CPU) -o0

boot.o:boot.c
	$(CC) $(CFLAGS) $^ -o $(OUTDIR)/$@ 
	

clean:
	rm -rf $(OUTDIR)/*.o *.elf
