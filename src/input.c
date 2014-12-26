#include "input.h"


void put_input(struct GapBuffer *Gbuf, int c)
{
    /**********************************
     * Print character to the screen  *
     * taking special characters into *
     * account as necessary.          *
     **********************************/

    switch(c)
    {
        // 27: Esc - Do nothing.
        case 27:
            break;

        case KEY_BACKSPACE:
            SCRdelchar(stdscr);
            GBdelchar(Gbuf);
            wnoutrefresh(stdscr);
            break;

        case KEY_RIGHT:
            SCRcursRight(stdscr, Gbuf);
            GBstepForw(Gbuf);
            wnoutrefresh(stdscr);
            break;

        case KEY_LEFT:
            SCRcursLeft(stdscr, Gbuf);
            GBstepBack(Gbuf);
            wnoutrefresh(stdscr);
            break;

        default:
            SCRaddchar(stdscr, Gbuf, c);
            GBaddchar(Gbuf, c);
            wnoutrefresh(stdscr);
    }
}


int parse_cmd(struct GapBuffer *Gbuf, int c)
{
    if (c == 'w') {
        // This is unclear.
        // I don't like the if X == 0 return 1,
        // with both indicating failure.
        if (GBwrite(Gbuf) == 0) {
            return 1;
        }
    }

    return 0;
}


void input_mgmt()
{
    /******************
     *     state      *
     *  0 : edit mode *
     *  1 : cmd mode  *
     * -1 : quit      *
     ******************/
    int y_size, x_size;     // Main window dimensions.
    int state = 0;
    int c;

    // Window to display the current state.
    WINDOW *state_win;
    getmaxyx(curscr, y_size, x_size);
    state_win = newwin(1, x_size, y_size-1, 0);

    // Text buffer.
    struct GapBuffer *Gbuf = GBmake();
    assert(Gbuf != NULL);
    GBinit(Gbuf);

    // Needed for immediate escape key behavior.
    if (getenv("ESCDELAY") == NULL) {
        ESCDELAY = 25;
    }

    while (state != -1) {
        c = getch();
        state = get_state(c, state);
        display_state(state_win, state);

        if (state == 0) {
            put_input(Gbuf, c);
        }
        else if (state == 1) {
            if ( parse_cmd(Gbuf, c) ) {
                wprintw(state_win, " written");
                wnoutrefresh(state_win);
            }
        }
        else {
            break;
        }
        doupdate();
    }
}
