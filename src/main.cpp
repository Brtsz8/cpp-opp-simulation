#include <iostream>
#include <ncurses.h>
#include "config.h"
using namespace std;

#define DEFAULT_HEIGHT  10
#define DEFAULT_WIDTH   30
#define DEFAULT_START_Y 5
#define DEFAULT_START_X 5
#define CONFIG_FILE '../cfg/config.txt'

int main(){
    //initialization of config with default values
    WinConfig cfg = {
        .height = DEFAULT_HEIGHT,
        .width = DEFAULT_WIDTH,
        .start_y = DEFAULT_START_Y,
        .start_x = DEFAULT_START_X
    };
    load_config("../cfg/config.txt",&cfg);
    
    initscr();
    cbreak();
    noecho();
    curs_set(0);      // Hide cursor
    refresh();        // Refresh main window

    // Create a new window
    WINDOW *win = newwin(cfg.height, cfg.width, cfg.start_y, cfg.start_x);
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