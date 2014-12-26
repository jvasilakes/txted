#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct GapBuffer {
    int size;
    char *buf;
    int pre;      //Cursor position.
    int post;     //The end of the gap.
};

struct GapBuffer *GBmake();
int GBinit(struct GapBuffer *Gbuf);
int GBwrite(struct GapBuffer *Gbuf);
void GBclear(struct GapBuffer *Gbuf);
void GBprint(struct GapBuffer *Gbuf);
void GBaddchar(struct GapBuffer *Gbuf, char c);
void GBdelchar(struct GapBuffer *Gbuf);
void GBstepForw(struct GapBuffer *Gbuf);
void GBstepBack(struct GapBuffer *Gbuf);
void GBend(struct GapBuffer *Gbuf);

#endif
