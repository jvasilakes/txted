#include "screen.h"

int scr_start()
{
    // Start the curses screen
    initscr();
    keypad(stdscr, TRUE);
    noecho();

    return 0;
}

int scr_end()
{
    // End the curses screen.
    endwin();

    return 0;
}
