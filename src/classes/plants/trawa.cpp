#include <iostream>
#include <ncurses.h>
#include <random>
#include <sstream>
#include "../roslina.h"
#include "trawa.h"
#include "../swiat.h"
using namespace std;

Trawa::Trawa(int pozycja_x, int pozycja_y, Swiat* swiat) 
    : Roslina(0, pozycja_x, pozycja_y, swiat) {};

Trawa::~Trawa() {};

char Trawa::rysowanie() const {
    return 'T';
}
string Trawa::nazwa() const {
    return "Trawa";
}

Organizm* Trawa::dodajPotomka(int x, int y) const {
    Organizm* mlodaTrawa = new Trawa(x,y,getSwiat());
    return mlodaTrawa;
}
