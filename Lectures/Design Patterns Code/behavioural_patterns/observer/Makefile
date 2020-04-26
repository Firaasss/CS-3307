################################################################################
#
# Makefile for the Observer design pattern example.
#
# Author: Jeff Shantz
#
# To build, simply type 'make'.
#
################################################################################

BIN=spreadsheet

all: $(BIN)

spreadsheet: main.o Graph.o SpreadsheetCell.o Subject.o 
	g++ -o $@ $^ $(LFLAGS) $(LIBS)

%.o: %.cpp
	g++ -c $<

clean:
	rm -f *.o *.log $(BIN)

realclean: clean
	rm -f $(BIN)
