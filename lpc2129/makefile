NAME   = lpc2129

CC      = arm-elf-gcc
LD      = arm-elf-ld -v
AR      = arm-elf-ar
AS      = arm-elf-as
CP      = arm-elf-objcopy
OD		= arm-elf-objdump

CFLAGS  = -I./ -c  -fno-common -O0 -g
AFLAGS  = -ahls -mapcs-32 -o crt.o
LFLAGS  =  -Map main.map -T MyBlinker.cmd
CPFLAGS = -O binary
HEXFLAGS = -O ihex
ODFLAGS	= -x --syms

all: test

clean:
	-rm crt.lst main.o main.out main.hex main.map main.dmp main.bin 
	
test: main.out
	@ echo "...copying"
	$(CP) $(CPFLAGS) main.out main.bin
	$(OD) $(ODFLAGS) main.out > main.dmp
	@echo "...building hex"
	$(CP) $(HEXFLAGS) main.out main.hex

main.out: crt.o ENC28J60.o spi.o main.o MyBlinker.cmd 
	@ echo "..linking"
	$(CC) -o main.out crt.o spi.o ENC28J60.o main.o -nostartfiles -TMyBlinker.cmd

spi.o: spi.c

	 $(CC) $(CFLAGS) spi.c
	 
	 
ENC28J60.o: ENC28J60.c

	 $(CC) $(CFLAGS) ENC28J60.c

crt.o: crt.s
	@ echo ".assembling"
	$(AS) $(AFLAGS) crt.s > crt.lst
	 
	 