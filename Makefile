CFLAGS = -std=c99 -Wall -pedantic -D_XOPEN_SOURCE=700
LFLAGS = -lm -lncurses
OBJS = screen.o state.o input.o buffer.o main.o
PROG = txted
CXX = gcc

all: $(PROG)

%.o: src/%.c src/%.h
	$(CXX) $(CFLAGS) -g -c $<

$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG) $(LFLAGS)

clean:
	if [ -f txted ]; then rm txted; fi
	if [ -f *.out ]; then rm *.out; fi
	rm *.o
