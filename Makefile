CFLAGS = -std=c99 -Wall -pedantic -D_XOPEN_SOURCE=700
LFLAGS = -lm -lncurses
OBJS = screen.o input.o main.o
PROG = txted
CXX = gcc

all: $(PROG)

%.o: src/%.c src/%.h
	$(CXX) $(CFLAGS) -g -c $<

$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG) $(LFLAGS)

clean:
	if [ -f txted ]; then rm txted; fi
	rm *.o
