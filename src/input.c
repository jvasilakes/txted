#include "input.h"


void put_input(struct GapBuffer *buf, int c)
{
    /**********************************
     * Print character to the screen  *
     * taking special characters into *
     * account as necessary.          *
     **********************************/

    int y, x;
    getyx(stdscr, y, x);

    switch(c)
    {
        // 27: Esc - Do nothing.
        case 27:
            break;

        case KEY_BACKSPACE:
            // Delete from the buffer.
            GBdelchar(buf);
            // Delete from the screen.
            mvdelch(y, x-1);
            wnoutrefresh(stdscr);
            break;

        case KEY_RIGHT:
            GBstepForward(buf);
            move(y, x+1);
            wnoutrefresh(stdscr);
            break;

        case KEY_LEFT:
            GBstepBackward(buf);
            move(y, x-1);
            wnoutrefresh(stdscr);
            break;

        default:
            // Add to the buffer.
            GBaddchar(buf, c);
            // Add to the screen.
            waddch(stdscr, c);
            wnoutrefresh(stdscr);
    }
}


int parse_cmd(struct GapBuffer *buf, int c)
{
    if (c == 'w') {
        GBwrite(buf);
        return 1;
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
    struct GapBuffer *buf;
    buf = GBinit();

    // Needed for immediate escape key behavior.
    if (getenv("ESCDELAY") == NULL) {
        ESCDELAY = 25;
    }


    while (state != -1) {
        c = getch();
        state = get_state(c, state);
        display_state(state_win, state);

        if (state == 0) {
            put_input(buf, c);
        }
        else if (state == 1) {
            if ( parse_cmd(buf, c) ) {
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
