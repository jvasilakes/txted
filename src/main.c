#include "main.h"


int main(int argc, char *argv[])
{
    // Create a curses screen.
    scr_start();

    // Get input and do something
    // with it.
    input_mgmt();

    // Delete the screen.
    scr_end();

    return 0;
}
