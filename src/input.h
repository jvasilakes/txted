#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ncurses.h>
#include "state.h"
#include "buffer.h"

void put_input(struct GapBuffer *Gbuf, int);
int parse_cmd(struct GapBuffer *Gbuf, int);
void input_mgmt();
