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

void SCRaddchar(WINDOW *win, struct GapBuffer *Gbuf, char c)
{
    /* Add the character to the screen at the current cursor position. */

    // If the cursor is at the end of the line, just append it.
    if ( Gbuf->post == Gbuf->size ) {
        waddch(win, c);
    }
    // Otherwise, there are characters after it.
    // Move those right one character position.
    else {
        int y, x;
        getyx(win, y, x);
        int temp_y = y;
        int temp_x = x;
        // This effectively slices the buffer from Gbuf->post
        // to the end. Here this slice is moved one character
        // position to the right.
        mvwaddch(win, temp_y, temp_x, c);
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
