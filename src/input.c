#include "input.h"


void put_input(int c)
{
    /**********************************
     * Print character to the screen  *
     * taking special characters into *
     * account as necessary.          *
     **********************************/
    int y, x;

    switch(c)
    {
        // 127: Backspace 8: Delete
        case 127:
        case 8:
            getyx(stdscr, y, x);
            mvdelch(y, x-1);
            refresh();
            break;
        // 13: Enter/Return
        case 13:
            getyx(stdscr, y, x);
            move(y+1, x-x);
            refresh();
            break;
        // 27: Esc - Do nothing.
        case 27:
            break;
        default:
            waddch(stdscr, c);
            refresh();
    }
}


void input_mgmt()
{
/******************
 *     state      *
 *  0 - edit mode *
 *  1 - cmd mode  *
 * -1 - quit      *
 ******************/
    int y_size, x_size;     // Main window dimensions.
    WINDOW *state_win;
    int state = 0;
    int c;

    getmaxyx(curscr, y_size, x_size);
    state_win = newwin(1, x_size, y_size-1, 0);

    display_state(state_win, state);
    while (state != -1) {
        c = getchar();
        state = get_state(c, state);
        display_state(state_win, state);

        if (state == 0) {
            put_input(c);
        }
        else if (state == 1) {
            //parse_cmd(c);
            ;
        }
        else {
            break;
        }
    }
}
