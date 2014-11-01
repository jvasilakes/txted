#include "state.h"

int get_state(int c, int current_state)
{
    // If in edit mode:
    if (current_state == 0) {
        if (c == 27) {  // 27: Esc
            return 1;
        }
        else {
            return current_state;
        }
    }
    // If in cmd mode:
    else if (current_state == 1) {
        if (c == 27) {  // 27: Esc
            return 0;
        }
        else if (c == 'q') {
            return -1;
        }
        else {
            return current_state;
        }
    }
    else {
        return current_state;
    }
}

void display_state(WINDOW *state_win, int state)
{
/*****************************
 * Display current state at  *
 * the bottom of the screen. *
 * ***************************/
    char state_name[4];

    // Where the cursor is currently
    // so we can move back to it later.
    //int old_y, old_x;

    if (state == 0) {
        strcpy(state_name, "EDIT");
    }
    else if (state == 1) {
        strcpy(state_name, "CMD");
    }
    else {
        strcpy(state_name, "?");
    }

    // Print the current state.
    wclear(state_win);
    mvwprintw(state_win, 0, 0, "%s", state_name);
    wrefresh(state_win);
}
