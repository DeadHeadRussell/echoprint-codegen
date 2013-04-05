all:
	cd src/ && make

clean:
	cd src/ && make clean

install:
	cd src/ && make install

test:
	cd test/ && make

.PHONY: all clean install test

