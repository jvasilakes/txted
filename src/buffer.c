/**************************************************
 *      Simple gap buffer implementation.         *
 * How to implement a struct in the .c file here: *
 * http://stackoverflow.com/a/2483358/2544396     *
 **************************************************/

#include "buffer.h"


void GBinit(struct GapBuffer *Gbuf)
{
    /* Construct a new character buffer. */

    Gbuf->next = NULL;
    Gbuf->prev = NULL;
    memset(Gbuf->buf, 0, BUFSIZE+1);
    Gbuf->size = BUFSIZE;
    Gbuf->pre = 0;
    Gbuf->post = BUFSIZE;
}

bool GBwrite(struct GapBuffer *Gbuf)
{
    /* Save the current buffer to a file. */

    bool success = true;

    FILE *fp;
    fp = fopen("test.ted", "wb");
    if (fp == NULL) {
        success = false;
    }
    else {
        while (Gbuf != NULL) {
            GBend(Gbuf);
            fprintf(fp, "%s\n", Gbuf->buf);
            Gbuf = Gbuf->next;
        }
        fclose(fp);
    }

    return success;
}

void GBclear(struct GapBuffer *Gbuf)
{
    /* Clear the current buffer string. */

    memset(Gbuf->buf, 0, BUFSIZE);
    Gbuf->pre = 0;
    Gbuf->post = BUFSIZE;
}

void GBprint(struct GapBuffer *Gbuf)
{
    /* Print the contents of the buffer to stdout. */

    GBend(Gbuf);
    printf("%s\n", Gbuf->buf);
}

bool GBaddchar(struct GapBuffer *Gbuf, char c)
{
    /* Add a new character at the cursor position.
     * Advance the current position in the buffer. */

    bool success = true;
    if (Gbuf->pre < Gbuf->post) {
        Gbuf->buf[Gbuf->pre] = c;
        Gbuf->pre++;
    }
    else {
        success = false;
    }
    return success;
}

bool GBdelchar(struct GapBuffer *Gbuf)
{
    /* Deletes the character just before the cursor. */

    bool success = true;
    if ( Gbuf->pre > 0 ) {
        Gbuf->buf[--Gbuf->pre] = 0;
    }
    else if (Gbuf->pre == 0) {
        if (Gbuf->prev != NULL) {
            Gbuf = Gbuf->prev;
            Gbuf->buf[--Gbuf->pre] = 0;
        }
        else {
            success = false;
        }
    }
    return success;
}

bool GBstepForw(struct GapBuffer *Gbuf)
{
    bool success = true;
    /* Move the gap one character position right. */
    if (Gbuf->post < Gbuf->size) {
        Gbuf->buf[Gbuf->pre] = Gbuf->buf[Gbuf->post];
        Gbuf->pre++;
        Gbuf->post++;
    }
    // If the cursor is at the end of the buffer, change to the next buffer.
    else if (Gbuf->post == Gbuf->size) {
        if (Gbuf->next != NULL) {
            Gbuf = Gbuf->next;
            Gbuf->buf[Gbuf->pre] = Gbuf->buf[Gbuf->post];
            Gbuf->pre++;
            Gbuf->post++;
        }
        // If this is the last buffer, fail.
        else {
            success = false;
        }
    }
    return success;
}

bool GBstepBack(struct GapBuffer *Gbuf)
{
    /* Move the gap one character position left. */

    bool success = true;
    if (Gbuf->pre > 0) {
        Gbuf->pre--;
        Gbuf->post--;
        Gbuf->buf[Gbuf->post] = Gbuf->buf[Gbuf->pre];
    }
    // If the cursor is at the beginning of the buffer, change to the previous.
    else if (Gbuf->pre == 0) {
        if (Gbuf->prev != NULL) {
            Gbuf = Gbuf->prev;
        }
        else {
            success = false;
        }
    }
    return success;
}

void GBend(struct GapBuffer *Gbuf)
{
    /* Move the gap to the end of the buffer. */

    while (Gbuf->post != BUFSIZE) {
        GBstepForw(Gbuf);
    }
}
