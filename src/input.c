#include "input.h"


bool input_mgmt(struct GapBuffer *currentGbuf, int c)
{
    /**********************************
     * Print character to the screen  *
     * taking special characters into *
     * account as necessary.          *
     **********************************/

    bool success = true;

    switch(c)
    {
        // 27: Esc - Do nothing.
        case 27:
            break;

//      In OSX KEY_BACKSPACE is misdefined. Should be 127 but it isn't.
        case 127:
            if (GBdelchar(currentGbuf)) {
                SCRdelchar(stdscr);
            }
            wnoutrefresh(stdscr);
            break;

        case KEY_RIGHT:
            if (GBstepForw(currentGbuf)) {
                SCRcursRight(stdscr, currentGbuf);
            }
            wnoutrefresh(stdscr);
            break;

        case KEY_LEFT:
            if (GBstepBack(currentGbuf)) {
                SCRcursLeft(stdscr, currentGbuf);
            }
            wnoutrefresh(stdscr);
            break;

        default:
            if (GBaddchar(currentGbuf, c)) {
                SCRaddchar(stdscr, currentGbuf, c);
                wnoutrefresh(stdscr);
            }
            else {
                // TODO: where should this go?
                currentGbuf->next = malloc(sizeof(struct GapBuffer));
                currentGbuf->prev = currentGbuf;
                assert(currentGbuf->next != NULL);
                GBinit(currentGbuf->next);
                currentGbuf = currentGbuf->next;
                success = false;
            }
    }
    return success;
}


bool parse_cmd(struct GapBuffer *Gbuf, int c)
{
    bool success = false;
    if (c == 'w') {
        if (GBwrite(Gbuf)) {
            success = true;
        }
    }
    return success;
}


void mainloop()
{
    int y_size, x_size;     // Main window dimensions.
    int state = 0;
    int c;

    // Window to display the current state.
    WINDOW *state_win;
    getmaxyx(curscr, y_size, x_size);
    state_win = newwin(1, x_size, y_size-1, 0);

    // Text buffer.
    struct GapBuffer Gbuf;
    struct GapBuffer *currentGbuf = &Gbuf;
    GBinit(currentGbuf);

    // Needed for immediate escape key behavior.
    if (getenv("ESCDELAY") == NULL) {
        ESCDELAY = 25;
    }

    wprintw(curscr, "%d", KEY_BACKSPACE);
    wnoutrefresh(state_win);
    while (state != -1) {
        c = getch();
        state = get_state(c, state);
        display_state(state_win, state);

        if (state == EDIT) {
            // if input_mgmt fails, rerun it.
            if (!input_mgmt(currentGbuf, c)) {
                input_mgmt(currentGbuf, c);
            }
        }
        else if (state == CMD) {
            if (parse_cmd(&Gbuf, c)) {
                wprintw(state_win, " written");
                wnoutrefresh(state_win);
            }
        }
        // state == QUIT
        else {
            break;
        }
        doupdate();
    }
}
