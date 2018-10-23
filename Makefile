.PHONY: all clean

all:
	cd avr && make
	cd loadavg-led && make
	cd toggle-dtr && make

clean:
	cd avr && make clean
	cd loadavg-led && make clean
	cd toggle-dtr && make clean

