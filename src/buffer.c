/**************************************************
 *      Simple gap buffer implementation.         *
 * How to implement a struct in the .c file here: *
 * http://stackoverflow.com/a/2483358/2544396     *
 **************************************************/

#include "buffer.h"
#define BUFSIZE 100


struct GapBuffer {
    int size;
    char *buf;
    int pre;      //Cursor position.
    int post;     //The end of the gap.
};

struct GapBuffer *GBmake()
{
    struct GapBuffer *Gbuf = malloc(sizeof(struct GapBuffer));
    if (Gbuf != NULL) {
        return Gbuf;
    }
    else {
        return NULL;
    }
}

int GBinit(struct GapBuffer *Gbuf)
{
    /* Construct a new character buffer. */

    Gbuf->buf = malloc(BUFSIZE);
    if (Gbuf->buf) {
        Gbuf->buf[0] = '\0';
        Gbuf->size = BUFSIZE;
        Gbuf->pre = 0;
        Gbuf->post = BUFSIZE;
        // Return true if we have a buffer.
        return 1;
    }
    else {
        // If malloc failed, return False.
        return 0;
    }
}

int GBwrite(struct GapBuffer *Gbuf)
{
    /* Save the current buffer to a file. */

    // Send the gap to the end of the buffer.
    GBend(Gbuf);

    FILE *fp;
    fp = fopen("test.ted", "wb");
    if (fp == NULL) {
        return 1;
    }
    fprintf(fp, Gbuf->buf);
    fclose(fp);

    return 0;
}

void GBclear(struct GapBuffer *Gbuf)
{
    /* Clear the current buffer string. */

    Gbuf->buf[0] = '\0';
    Gbuf->pre = 0;
    Gbuf->post = BUFSIZE;
}

void GBprint(struct GapBuffer *Gbuf)
{
    /* Print the contents of the buffer to stdout. */

    GBend(Gbuf);
    printf("%s\n", Gbuf->buf);
}

void GBaddchar(struct GapBuffer *Gbuf, char c)
{
    /* Add a new character at the cursor position.
     * Advance the current position in the buffer. */

    if ( Gbuf->pre == Gbuf->post) {
        // For now, don't let any more than BUFSIZE characters.
        //printf("Gotta expand.");
        return;
    }

    Gbuf->buf[ Gbuf->pre ] = c;
    Gbuf->pre++;
}

void GBdelchar(struct GapBuffer *Gbuf)
{
    /* Deletes the character just before the cursor. */

    if ( Gbuf->pre > 0 ) {
        Gbuf->buf[ --Gbuf->pre ] = '\0';
    }
}

void GBstepForw(struct GapBuffer *Gbuf)
{
    /* Move the gap one character position right. */

    if (Gbuf->post < Gbuf->size) {
        Gbuf->buf[ Gbuf->pre ] = Gbuf->buf[ Gbuf->post ];
        Gbuf->pre++;
        Gbuf->post++;
    }
}

void GBstepBack(struct GapBuffer *Gbuf)
{
    /* Move the gap one character position left. */

    if (Gbuf->pre > 0) {
        Gbuf->pre--;
        Gbuf->post--;
        Gbuf->buf[ Gbuf->post ] = Gbuf->buf[ Gbuf->pre ];
    }
}

void GBend(struct GapBuffer *Gbuf)
{
    /* Move the gap to the end of the buffer. */

    while (Gbuf->post != BUFSIZE) {
        GBstepForw(Gbuf);
    }
}
