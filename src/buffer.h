#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct GapBuffer;
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
