IDIR=include
CC=gcc
CFLAGS=-I$(IDIR) -Wall -Wextra -Wshadow -Wdouble-promotion 

ODIR=src/obj
LDIR=lib

LIBS=-lm -lpng

_DEPS = png_utility.h cJSON.h scene.h def.h vec3_util.h ray_util.h color.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = png_utility.o main.o cJSON.o scene.o vec3_util.o ray_util.o color.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

go: $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

