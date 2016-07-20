#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define BUFSIZE 100

struct GapBuffer {
    struct GapBuffer *next;
    struct GapBuffer *prev;
    int size;
    char buf[BUFSIZE+1];
    int pre;      //Cursor position.
    int post;     //The end of the gap.
};

void GBinit(struct GapBuffer *Gbuf);
bool GBwrite(struct GapBuffer *Gbuf);
void GBclear(struct GapBuffer *Gbuf);
void GBprint(struct GapBuffer *Gbuf);
bool GBaddchar(struct GapBuffer *Gbuf, char c);
bool GBdelchar(struct GapBuffer *Gbuf);
bool GBstepForw(struct GapBuffer *Gbuf);
bool GBstepBack(struct GapBuffer *Gbuf);
void GBend(struct GapBuffer *Gbuf);

#endif
