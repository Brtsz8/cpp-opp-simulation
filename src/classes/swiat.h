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
        void nowyOrganizm(Organizm* organizm);
};

#endif