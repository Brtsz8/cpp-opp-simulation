#include <iostream>
#include <ncurses.h>
#include "config.h"
#include "classes/organizm.h"
#include "classes/swiat.h"
#include "classes/zwierze.h"
#include "classes/animals/wilk.h"
#include "classes/animals/owca.h"
using namespace std;

#define DEFAULT_HEIGHT  10
#define DEFAULT_WIDTH   30
#define DEFAULT_START_Y 5
#define DEFAULT_START_X 5

void simulation(WINDOW* win, WINDOW* log_window){
    Swiat swiat(win, log_window);
    Wilk wilk(2,2,&swiat);
    Owca owca(4,4,&swiat);
    swiat.nowyOrganizm(&wilk);
    swiat.nowyOrganizm(&owca);
    while(getchar() != 'q')     //q odpowiada za wyjscie z symulacji
    {
        swiat.wykonajTure();
    }
}

void setUpWindows(WINDOW *win,WINDOW *log_window, WINDOW *info_window){
    box(win, 0, 0);
    box(log_window, 0, 0);
    box(info_window, 0, 0);
    mvwprintw(info_window, 1, 1, "Bartosz Pacyga 203833");

    wrefresh(info_window);
    wrefresh(log_window);
    wrefresh(win);
}

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

    // Create a main window , log window and info window
    WINDOW *win = newwin(cfg.height, cfg.width, cfg.start_y, cfg.start_x);
    WINDOW *log_window = newwin(cfg.height/4,cfg.width,cfg.start_y+cfg.height,cfg.start_x);
    WINDOW *info_window = newwin(3,cfg.width,cfg.start_y-3,cfg.start_x);
    if (win == NULL || log_window == NULL || info_window == NULL ) {
        endwin();
        printf("Error creating window!\n");
        return 1;
    }

    setUpWindows(win,log_window,info_window);
    simulation(win,log_window);

    getch();
    delwin(log_window);
    delwin(win);
    delwin(info_window);
    endwin();
    return 0;
}