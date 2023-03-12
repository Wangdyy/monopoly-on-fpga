IDIR =.
CC=gcc
CFLAGS=-I$(IDIR) -Wall -W -pedantic -Wno-unused-parameter 

ODIR=obj
LDIR =../lib

LIBS=

_DEPS = gamestate.h helpers.h players.h squares.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = monopoly.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

monopoly: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	del obj\monopoly.o