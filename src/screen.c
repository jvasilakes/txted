#include "screen.h"

int SCRstart()
{
    // Start the curses screen
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    return 0;
}

int SCRend()
{
    // End the curses screen.
    endwin();
    return 0;
}

void SCRdisplaybuffer(WINDOW *win, struct GapBuffer *Gbuf)
{
    int y, x;
    int pre;
    getyx(win, y, x);
    pre = Gbuf->pre;  // Starting gap position
    GBend(Gbuf);
    mvwaddstr(win, 0, 0, Gbuf->buf);
    wmove(win, y, x);
    // Move the gap back to where it was.
    while ( Gbuf->pre != pre ) {
        GBstepBack(Gbuf);
    }
}

void SCRaddchar(WINDOW *win, struct GapBuffer *Gbuf, char c)
{
    /* Add the character to the screen at the current cursor position. */

    // If the cursor is at the end of the line, just append it.
    if ( Gbuf->post == Gbuf->size ) {
        waddch(win, c);
    }
    // Otherwise, there are characters after it.
    else {
        int y, x;
        getyx(win, y, x);
        mvwaddch(win, y, x, c);
        // Just redisplay the buffer rather than moving the characters on screen.
        SCRdisplaybuffer(win, Gbuf);
    }
}

void SCRdelchar(WINDOW *win)
{
    /* Delete the character just before the cursor. */
    int y, x;
    getyx(win, y, x);
    mvwdelch(win, y, x-1);
}

void SCRcursRight(WINDOW *win, struct GapBuffer *Gbuf)
{
    /* Move the cursor one character position to the right.
     * Don't allow movement past the last character on the
     * line. */
    if (Gbuf->post < Gbuf->size) {
        int y, x;
        getyx(win, y, x);
        wmove(win, y, x+1);
    }
}

void SCRcursLeft(WINDOW *win, struct GapBuffer *Gbuf)
{
    /* Move the cursor one character position to the left.*/
    int y, x;
    getyx(win, y, x);
    if (wmove(win, y, x-1) == ERR) {
        int ymax, xmax;
        getmaxyx(win, ymax, xmax);
        wmove(win, y-1, xmax-1);
    }
}
