IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -Wall -W -pedantic -Wno-unused-parameter

ODIR=obj
LDIR =../lib

LIBS=

_DEPS = Gamestate.h helper_functions.h Players.h Squares.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Monopoly.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Monopoly: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	del obj\Monopoly.o