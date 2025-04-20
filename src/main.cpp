#include <iostream>
#include <ncurses.h>
using namespace std;

int main(){
    initscr();
    cbreak();
    noecho();
    curs_set(0);      // Hide cursor
    refresh();        // Refresh main window

   //size of the window should be specified in the config file   
    int height = 10, width = 30;
    int start_y = 5, start_x = 10;

    // Create a new window
    WINDOW *win = newwin(height, width, start_y, start_x);
    if (win == NULL) {
        endwin();
        printf("Error creating window!\n");
        return 1;
    }

    box(win, 0, 0);

    mvwprintw(win, 1, 1, "Hello, ncurses window!");

    wrefresh(win);

    getch();

    delwin(win);
    endwin();
    return 0;
}