/*********************
 * Simple gap buffer *
 * implementation.   *
 *********************/

#include "buffer.h"
#define BUFSIZE 100


struct GapBuffer {
    int size;
    char buf[BUFSIZE];
    int pre;            //Cursor position.
    int post;           //The end of the gap.
};

struct GapBuffer *GBinit()
{
    /*********************
     * Construct a new   *
     * character buffer. *
     *********************/
    struct GapBuffer *buf;
    buf = malloc(sizeof(struct GapBuffer));
    buf->size = BUFSIZE;
    buf->pre = 0;
    buf->post = buf->size;

    return buf;
}

int GBwrite(struct GapBuffer *buf)
{
    FILE *fp;
    fp = fopen("txted.out", "wb");
    fwrite(buf->buf, sizeof(char), sizeof(buf->buf), fp);
    fclose(fp);

    return 0;
}

void GBaddchar(struct GapBuffer *buf, char c)
{
    /**************************
     * Add a new character    *
     * at the cursor position *
     **************************/
    if (buf->pre == buf->post) {
        expand(buf);
    }

    buf->buf[buf->pre] = c;
    buf->pre++;
}

void GBdelchar(struct GapBuffer *buf)
{
    /***************************
     * Delete the character    *
     * just before the cursor. *
     ***************************/
    if (buf->pre > 0) { 
        buf->buf[buf->pre] = '\0';
        buf->pre--;
    }
}

void GBstepForward(struct GapBuffer *buf)
{
    /***********************
     * Move the cursor one *
     * step forward.       *
     ***********************/
    if (buf->post < buf->size) {
        buf->post++;
        buf->pre = buf->post;
        buf->pre++;
    }
}

void GBstepBackward(struct GapBuffer *buf)
{
    /***********************
     * Move the cursor one *
     * step backward.      *
     ***********************/
    if (buf->pre > 0) {
        buf->pre--;
        buf->post = buf->buf[buf->pre];
        buf->post--;
    }
}

void expand(struct GapBuffer *buf) {
    ;
}
