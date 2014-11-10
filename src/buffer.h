#include <stdio.h>
#include <stdlib.h>

struct GapBuffer *buf;
struct GapBuffer *GBinit();
int GBwrite(struct GapBuffer *buf);
void GBaddchar(struct GapBuffer *buf, char c);
void GBdelchar(struct GapBuffer *buf);
void GBstepForward(struct GapBuffer *buf);
void GBstepBackward(struct GapBuffer *buf);
void expand(struct GapBuffer *buf);
