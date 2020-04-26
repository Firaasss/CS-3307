################################################################################
#
# Makefile for the Command design pattern example.
#
# Author: Jeff Shantz
#
# To build, simply type 'make'.
#
################################################################################

BIN=cmd

all: $(BIN)

cmd: main.o Menu.o MenuItem.o Light.o Stereo.o
	g++ -o $@ $^ $(LFLAGS) $(LIBS)

%.o: %.cpp
	g++ -c $<

clean:
	rm -f *.o *.log $(BIN)

realclean: clean
	rm -f $(BIN)
