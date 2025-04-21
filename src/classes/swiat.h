#ifndef SWIAT_H
#define SWIAT_H

#include <iostream>
#include <ncurses.h>
#include <vector>
#include "organizm.h"

using namespace std;

class Swiat{
    private:
        WINDOW *win;
        WINDOW *log_window;
        vector<Organizm*> organizmy;
    public:
        Swiat(WINDOW *new_win, WINDOW *new_log_win);
        ~Swiat();

        //getter
        WINDOW* getWin();
        WINDOW* getLog();

        void wykonajTure();
        void rysujSwiat();
        //dodaje nowy organizm do swiata
        void nowyOrganizm(Organizm* organizm);

        //zwraca pointer do organizmu na danych wspolrzednych
        Organizm* findOrganismAt(int x, int y);
};

#endif