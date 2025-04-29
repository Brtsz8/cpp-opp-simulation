#include <iostream>
#include <ncurses.h>
#include <sstream>
#include "config.h"
#include "classes/organizm.h"
#include "classes/swiat.h"
#include "classes/zwierze.h"
#include "classes/animals/wilk.h"
#include "classes/animals/owca.h"
#include "classes/animals/zolw.h"
#include "classes/animals/antylopa.h"
#include "classes/animals/lis.h"
#include "classes/animals/czlowiek.h"
#include "classes/plants/trawa.h"
#include "classes/plants/mlecz.h"
#include "classes/plants/guarana.h"
#include "classes/plants/jagody.h"
#include "classes/plants/barszcz.h"

using namespace std;

#define DEFAULT_HEIGHT  10
#define DEFAULT_WIDTH   30
#define DEFAULT_START_Y 5
#define DEFAULT_START_X 5

void simulation(WINDOW* win, WINDOW* log_window, WINDOW *turn_counter){
    int command;
    int turn_count = 0;
    cout<<"Test: ";
    int test;
    cin >> test;
    Swiat* swiat = new Swiat(win, log_window);
    if(test == 1){
        swiat->nowyOrganizm(new Wilk(34, 14, swiat));
        swiat->nowyOrganizm(new Wilk(34, 13, swiat));
        swiat->nowyOrganizm(new Wilk(34, 12, swiat));
        swiat->nowyOrganizm(new Wilk(34, 11, swiat));
        swiat->nowyOrganizm(new Czlowiek(1,1, swiat));
        swiat->nowyOrganizm(new Trawa(38,28,swiat));
    }
    if(test == 2)
    {
        swiat->nowyOrganizm(new Jagody(1, 1, swiat));
        swiat->nowyOrganizm(new Owca(2, 2, swiat));
        swiat->nowyOrganizm(new Guarana(3, 2, swiat));
        swiat->nowyOrganizm(new Lis(4, 2, swiat));
        swiat->nowyOrganizm(new Antylopa(5, 2, swiat));
        swiat->nowyOrganizm(new Zolw(6, 2, swiat));
        swiat->nowyOrganizm(new Jagody(7, 2, swiat));
        swiat->nowyOrganizm(new Trawa(8, 2, swiat));
        swiat->nowyOrganizm(new Mlecz(9, 2, swiat));
        swiat->nowyOrganizm(new Zolw(10, 2, swiat));
        swiat->nowyOrganizm(new Lis(11, 2, swiat));
        swiat->nowyOrganizm(new Antylopa(12, 2, swiat));
        swiat->nowyOrganizm(new Barszcz(1, 1, swiat));
    }
    if(test == 3)
    {
        swiat->nowyOrganizm(new Barszcz(38, 28, swiat));
        swiat->nowyOrganizm(new Guarana(1, 28, swiat));
        swiat->nowyOrganizm(new Jagody(1, 1, swiat));
        swiat->nowyOrganizm(new Trawa(38, 1, swiat));
        
    }
    if(test == 4)
    {
        swiat->nowyOrganizm(new Barszcz(38, 28, swiat));
        swiat->nowyOrganizm(new Guarana(1, 28, swiat));
        swiat->nowyOrganizm(new Jagody(1, 1, swiat));
        swiat->nowyOrganizm(new Mlecz(38, 1, swiat));
    }    
    if(test == 5)
    {
        swiat->nowyOrganizm(new Barszcz(38, 28, swiat));
        swiat->nowyOrganizm(new Guarana(1, 28, swiat));
        swiat->nowyOrganizm(new Jagody(1, 1, swiat));
        swiat->nowyOrganizm(new Mlecz(38, 1, swiat));
    }
    if(test == 6){

    }
    if(test == 7){

    }

    swiat->rysujSwiat();
    while((command = getch())) {
        swiat->setCommand(command);
        if(command == 'q') break;

        if(command == '1') {
            int new_index = swiat->getTopLogIndex() + 1;
            swiat->setTopLogIndex(new_index);
            swiat->wyswietlLogi(swiat->getTopLogIndex());
            wrefresh(log_window);
            continue;
        }

        if(command == '2') {
            int new_index = swiat->getTopLogIndex() - 1;
            swiat->setTopLogIndex(new_index);
            swiat->wyswietlLogi(swiat->getTopLogIndex());
            wrefresh(log_window);
            continue;
        }
        if(command == '4'){
            swiat->save("save.txt");
            continue;
        } 
        if(command == '5'){
            swiat->load("save.txt");
            swiat->rysujSwiat();
            swiat->wyswietlLogi(swiat->getTopLogIndex());
            continue;
        } 

        swiat->wykonajTure();
        turn_count++;
        ostringstream log;
        log << "---Tura numer: "<<turn_count<<"----------------------";
        swiat->nowyLog(log.str());
        mvwprintw(turn_counter, 1, 1, "Turn number: %d", turn_count);
        wrefresh(turn_counter);
    }

    delete swiat;
}


void setUpWindows(WINDOW *win,WINDOW *log_window, WINDOW *info_window, WINDOW *turn_counter){
    box(win, 0, 0);
    box(log_window, 0, 0);
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
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    refresh();
    keypad(stdscr, TRUE);


    // Create a main window , log window, info window and turn counter window
    WINDOW *win = newwin(cfg.height, cfg.width, cfg.start_y, cfg.start_x);
    WINDOW *log_window = newwin(20,60,cfg.start_y,cfg.start_x + cfg.width);
    WINDOW *info_window = newwin(3,cfg.width,cfg.start_y-3,cfg.start_x);
    WINDOW *turn_counter = newwin(3,60, cfg.start_y-3, cfg.start_x + cfg.width);
    if (win == NULL || log_window == NULL || info_window == NULL || turn_counter == NULL ) {
        endwin();
        printf("Error creating window!\n");
        return 1;
    }

    box(win, 0, 0);
    box(log_window, 0, 0);
    box(info_window, 0, 0);
    box(turn_counter, 0, 0);
    
    mvwprintw(info_window, 1, 1, "Bartosz Pacyga 203833");
    mvwprintw(turn_counter, 1, 1, "Turn number: ");

    scrollok(log_window, TRUE);

    wrefresh(info_window);
    wrefresh(log_window);
    wrefresh(win);
    wrefresh(turn_counter);
    //setUpWindows(win,log_window,info_window,turn_counter);
    simulation(win,log_window,turn_counter);

    delwin(log_window);
    delwin(win);
    delwin(info_window);
    endwin();
    return 0;
}