include Makefile.inc

all:	kernel7.img kernel7.dis

kernel7.img:	kernel7.elf
	$(CROSS)objcopy kernel7.elf -O binary kernel7.img



kernel7.elf:	kernel_main.o \
		boot.o console_io.o led.o printk.o serial.o
	$(CROSS)ld $(LFLAGS) \
		kernel_main.o boot.o console_io.o led.o printk.o serial.o \
		-Map serial.map -o kernel7.elf


kernel_main.o:	kernel_main.c
	$(CROSS)$(CC) $(CFLAGS) -o kernel_main.o -c kernel_main.c

console_io.o:	console_io.c
	$(CROSS)$(CC) $(CFLAGS) -o console_io.o -c console_io.c

led.o:	led.c
	$(CROSS)$(CC) $(CFLAGS) -o led.o -c led.c

printk.o:	printk.c
	$(CROSS)$(CC) $(CFLAGS) -o printk.o -c printk.c

serial.o:	serial.c bcm2835_periph.h
	$(CROSS)$(CC) $(CFLAGS) -o serial.o -c serial.c

boot.o:	boot.s
	$(CROSS)as $(ASFLAGS) -o boot.o boot.s




kernel7.dis:	kernel7.elf
	$(CROSS)objdump --disassemble-all kernel7.elf > kernel7.dis

clean:
	rm -f *~ *.o *.map *.elf kernel7.img *.dis


submit:
	tar -czvf hw3_submit.tar.gz *.c *.h *.s *.ld Makefile README Makefile.inc

