all: build

build:
	make -C src
	mv src/pongix .
clean:
	rm -f pongix pongix.elf pongix.exe
	make -C src clean
