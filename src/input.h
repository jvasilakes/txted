#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "state.h"
#include "buffer.h"

void put_input(struct GapBuffer *buf, int);
int parse_cmd(struct GapBuffer *buf, int);
void input_mgmt();
