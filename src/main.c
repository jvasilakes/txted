#include "main.h"


int main(int argc, char *argv[])
{
    // Create a curses screen.
    SCRstart();

    // Get input and do something with it.
    mainloop();

    // Delete the screen.
    SCRend();

    return 0;
}
