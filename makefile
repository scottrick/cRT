IDIR=include
CC=gcc
CFLAGS=-I$(IDIR) -Wall

ODIR=src/obj
LDIR=lib

LIBS=-lm -lpng

_DEPS = png_utility.h cJSON.h scene.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = png_utility.o main.o cJSON.o scene.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

go: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

