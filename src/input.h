#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ncurses.h>
#include "state.h"
#include "buffer.h"
#include "screen.h"

#define EDIT 0
#define CMD 1
#define QUIT -1

bool input_mgmt(struct GapBuffer *Gbuf, int);
bool parse_cmd(struct GapBuffer *Gbuf, int);
void mainloop();
