#include <iostream>
#include <ncurses.h>
#include <vector>
#include "swiat.h"

using namespace std;

Swiat::Swiat(WINDOW *new_win, WINDOW *new_log_win) : win(new_win), log_window(new_log_win) {}

Swiat::~Swiat(){

}

//gettery do okien, wazne przy wyświetlaniu zwierzat/informacji 
WINDOW* Swiat::getWin(){
    return win;
}
WINDOW* Swiat::getLog(){
    return log_window;
}

void Swiat::nowyOrganizm(Organizm* organizm){
    organizmy.push_back(organizm);
}

void Swiat::wykonajTure(){
    for(Organizm* organizm : organizmy){
        organizm->akcja();
    }
    rysujSwiat();
}

void Swiat::rysujSwiat() {
    wclear(win);
    //to zrobie pozniej
    //wclear(log_window) 
    for(Organizm* organizm : organizmy){
        mvwaddch(win,organizm->getPozycjaY(),organizm->getPozycjaY(),organizm->rysowanie());
        box(win,0,0);
        wrefresh(win);
    }

}