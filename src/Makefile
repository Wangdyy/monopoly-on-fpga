IDIR =.
CC=gcc
CFLAGS=-I$(IDIR) -Wall -W -pedantic -Wno-unused-parameter

ODIR=obj
LDIR =../lib

LIBS=

_DEPS = gamestate.h helper_functions.h players.h squares.h
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