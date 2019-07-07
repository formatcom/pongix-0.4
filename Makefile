all: build

build:
	make -C src
	mv src/pongix .
clean:
	rm -f pongix *.elf *.ELF *.exe
	make -C src clean
