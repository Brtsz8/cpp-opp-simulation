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

void simulation(WINDOW* win, WINDOW* log_window, WINDOW *turn_counter){
    char command;
    int turn_count = 0;

    Swiat swiat(win, log_window);
    Wilk wilk(2,2,&swiat);
    Owca owca(4,4,&swiat);
    swiat.nowyOrganizm(&wilk);
    swiat.nowyOrganizm(&owca);
    while((command = getchar()))     //q odpowiada za wyjscie z symulacji
    {   
        if(command == 'q') break;
        if(command == '1') {
            wscrl(log_window, 1);
            wrefresh(log_window);
            continue;
        }
        if(command == '2')
        {
            wscrl(log_window, -1);
            wrefresh(log_window);
            continue;
        }
        else{
            swiat.wykonajTure();
            turn_count++;
            mvwprintw(turn_counter, 1, 1, "Turn number: %d", turn_count);
            wrefresh(turn_counter);
        }
    }
}

void setUpWindows(WINDOW *win,WINDOW *log_window, WINDOW *info_window, WINDOW *turn_counter){
    box(win, 0, 0);
    //box(log_window, 0, 0);
    box(info_window, 0, 0);
    box(turn_counter, 0, 0);
    
    mvwprintw(info_window, 1, 1, "Bartosz Pacyga 203833");
    mvwprintw(turn_counter, 1, 1, "Turn number: ");

    scrollok(log_window, TRUE);

    wrefresh(info_window);
    wrefresh(log_window);
    wrefresh(win);
    wrefresh(turn_counter);
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

    // Create a main window , log window, info window and turn counter window
    WINDOW *win = newwin(cfg.height, cfg.width, cfg.start_y, cfg.start_x);
    WINDOW *log_window = newwin(cfg.height,cfg.width,cfg.start_y,cfg.start_x + cfg.width);
    WINDOW *info_window = newwin(3,cfg.width,cfg.start_y-3,cfg.start_x);
    WINDOW *turn_counter = newwin(3,cfg.width, cfg.start_y-3, cfg.start_x + cfg.width);
    if (win == NULL || log_window == NULL || info_window == NULL || turn_counter == NULL ) {
        endwin();
        printf("Error creating window!\n");
        return 1;
    }

    setUpWindows(win,log_window,info_window,turn_counter);
    simulation(win,log_window,turn_counter);

    getch();
    delwin(log_window);
    delwin(win);
    delwin(info_window);
    endwin();
    return 0;
}