################################################################################
#
# Makefile for the Prototype design pattern example.  This will probably not
# build on your system since it uses Boost and is configured for the location
# of Boost on my system.
#
# You will need to modify CFLAGS, LFLAGS, LIBS according to your installation.
#
# Author: Jeff Shantz
#
# To build, simply type 'make'.
#
################################################################################

CFLAGS=-I /opt/local/include/
LFLAGS=-L /opt/local/lib/
LIBS=-lboost_timer-mt -lboost_system-mt

BIN=cfg

all: $(BIN)

cfg: main.o DatabaseConfig.o FileConfig.o 
	g++ -o $@ $^ $(LFLAGS) $(LIBS)

%.o: %.cpp
	g++ -c $(CFLAGS) $<

clean:
	rm -f *.o *.log $(BIN)

realclean: clean
	rm -f $(BIN)
