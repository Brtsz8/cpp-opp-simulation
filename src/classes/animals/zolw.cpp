#include <iostream>
#include <ncurses.h>
#include "zolw.h"
#include "../swiat.h"
using namespace std;

Zolw::Zolw(int pozycja_x, int pozycja_y, Swiat* swiat) 
    : Zwierze(2, 1, pozycja_x, pozycja_y, swiat) {};

Zolw::~Zolw() {};

char Zolw::rysowanie(){
    return 'Z';
}

Organizm* Zolw::dodajPotomka(int x, int y){
    Organizm* mlodyZolw = new Zolw(x,y,getSwiat());
    return mlodyZolw;
}