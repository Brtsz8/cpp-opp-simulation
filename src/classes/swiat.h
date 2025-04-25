#ifndef SWIAT_H
#define SWIAT_H

#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include "organizm.h"

using namespace std;

class Swiat{
    private:
        WINDOW *win;
        WINDOW *log_window;
        vector<Organizm*> organizmy;
        vector<Organizm*> nowe;
        vector<string> logs;
        int topLog = 0;
    public:
        Swiat(WINDOW *new_win, WINDOW *new_log_win);
        ~Swiat();

        //getter
        WINDOW* getWin();
        WINDOW* getLog();
        int getTopLogIndex();

        //settery
        void setTopLogIndex(int index);

        void wykonajTure();
        void rysujSwiat();
        //dodaje nowy organizm do swiata
        void nowyOrganizm(Organizm* organizm);
        //dodaj nowy log do tablicy logow
        void nowyLog(string log);

        //wyswietla logi od n'tego - tyle ile sie zmiesci
        void wyswietlLogi(int pierwszyLog);

        //zwraca pointer do organizmu na danych wspolrzednych
        Organizm* findOrganismAt(int x, int y);

        void usunOrganizmy();
        void sortujWszystkie();
        void usunZabite();
};

#endif