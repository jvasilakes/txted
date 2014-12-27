PROJ = txted
CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -D_XOPEN_SOURCE=700
LFLAGS = -lm -lncurses

ODIR = obj
build_folder := $(shell mkdir -p $(ODIR))
_OBJS = buffer.o screen.o state.o input.o main.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

all: $(PROJ)

$(ODIR)/%.o: src/%.c src/%.h
	$(CC) -g -c -o $@ $< $(CFLAGS)

$(PROJ): $(OBJS)
	$(CC) $(OBJS) -o $(PROJ) $(LFLAGS)

clean:
	rm $(ODIR)/*.o $(PROJ)
