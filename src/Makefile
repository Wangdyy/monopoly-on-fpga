IDIR =.
CC=gcc
CFLAGS=-I$(IDIR) -Wall -W -pedantic -Wno-unused-parameter 

ODIR=obj
LDIR =../lib

LIBS=

_DEPS = gamestate.h helpers.h players.h squares.h presets.h munit.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = monopoly.o load_presets.o unittests.o munit.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

monopoly_test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	del obj\monopoly.o
	