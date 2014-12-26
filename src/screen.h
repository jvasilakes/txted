#include <ncurses.h>
#include "buffer.h"

int SCRstart();
int SCRend();
void SCRaddchar(WINDOW *win, struct GapBuffer *Gbuf, char c);
void SCRdelchar(WINDOW *win);
void SCRcursRight(WINDOW *win, struct GapBuffer *Gbuf);
void SCRcursLeft(WINDOW *win, struct GapBuffer *Gbuf);
