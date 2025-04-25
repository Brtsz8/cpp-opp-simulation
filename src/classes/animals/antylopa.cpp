#include <iostream>
#include <ncurses.h>
#include "antylopa.h"
#include "../swiat.h"
using namespace std;

Antylopa::Antylopa(int pozycja_x, int pozycja_y, Swiat* swiat) 
    : Zwierze(4, 4, pozycja_x, pozycja_y, swiat) {};

Antylopa::~Antylopa() {};

char Antylopa::rysowanie() const {
    return 'A';
}

Organizm* Antylopa::dodajPotomka(int x, int y) const {
    Organizm* mlodaAntylopa = new Antylopa(x,y,getSwiat());
    return mlodaAntylopa;
}