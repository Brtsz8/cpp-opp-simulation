#include <iostream>
#include <ncurses.h>
#include "lis.h"
#include "../swiat.h"
using namespace std;

Lis::Lis(int pozycja_x, int pozycja_y, Swiat* swiat) 
    : Zwierze(3, 7, pozycja_x, pozycja_y, swiat) {};

Lis::~Lis() {};

char Lis::rysowanie(){
    return 'L';
}

Organizm* Lis::dodajPotomka(int x, int y){
    Organizm* mlodyLis = new Lis(x,y,getSwiat());
    return mlodyLis;
}