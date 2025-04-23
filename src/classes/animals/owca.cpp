#include <iostream>
#include <ncurses.h>
#include "owca.h"
#include "../swiat.h"
using namespace std;

Owca::Owca(int pozycja_x, int pozycja_y, Swiat* swiat) 
    : Zwierze(4, 4, pozycja_x, pozycja_y, swiat) {};

Owca::~Owca() {};

char Owca::rysowanie(){
    return 'O';
}

Organizm* Owca::dodajPotomka(int x, int y){
    Organizm* mlodaOwca = new Owca(x,y,getSwiat());
    return mlodaOwca;
}