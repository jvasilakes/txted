#include "input.h"


void put_input(int c)
{
    /*************************
     * Change to a switch*****
     * ***********************/

    // 127: Backspace 8: Delete
    if (c == 127 || c == 8) {
        int y, x;
        getyx(curscr, y, x);
        mvdelch(y, x-1);
    }
    // 13: Enter/Return
    else if (c == 13) {
        int y, x;
        getyx(curscr, y, x);
        move(y+1, x-x);
    }
    else {
        addch(c);
    }


    refresh();
}


void input_mgmt()
{
    int c;

    while ((c = getchar()) != 'q') {
        put_input(c);
    }
}
