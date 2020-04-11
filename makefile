IDIR=include
CC=gcc
CFLAGS=-I$(IDIR) -Wall -Wextra -Wshadow -Wdouble-promotion 

ODIR=src/obj
LDIR=lib

LIBS=-lm -lpng

_DEPS = png_utility.h cJSON.h scene.h def.h vec3_util.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = png_utility.o main.o cJSON.o scene.o vec3_util.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

go: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

