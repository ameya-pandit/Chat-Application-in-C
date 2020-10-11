##################################################
#
# Makefile for the simple GTK example
# author: Weiwei Chen (updates by Rainer Doemer)
# initial version: 01/22/13 EECS22L Winter 2013
# patched version: 01/14/15 EECS22L Winter 2015
#
##################################################

GTKINC	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --cflags gtk+-2.0`
GTKLIBS	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --libs gtk+-2.0`

INC	= $(GTKINC)
LIBS	= $(GTKLIBS)

OPTS	= -g

PROJECT	= simple

all: $(PROJECT)

simple.o: GUI_LC.c simple.h
	gcc -c GUI_LC.c $(INC) $(OPTS) -o simple.o

simple: simple.o
	gcc simple.o $(LIBS) $(OPTS) -o simple

clean:
	rm -rf *.o $(PROJECT)
