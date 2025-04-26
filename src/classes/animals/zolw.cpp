#include <iostream>
#include <ncurses.h>
#include "zolw.h"
#include "../swiat.h"
using namespace std;

Zolw::Zolw(int pozycja_x, int pozycja_y, Swiat* swiat) 
    : Zwierze(2, 1, pozycja_x, pozycja_y, swiat) {};

Zolw::~Zolw() {};

void Zolw::akcja(){
    if(getRandomDir()==0) Zwierze::akcja();     //75% przypadkow sie nie rusza
}

char Zolw::rysowanie() const {
    return 'Z';
}
string Zolw::nazwa() const {
    return "Zolw";
}

Organizm* Zolw::dodajPotomka(int x, int y) const {
    Organizm* mlodyZolw = new Zolw(x,y,getSwiat());
    return mlodyZolw;
}

bool Zolw::czyOdbilAtak(Organizm* atakujacy){
    if(atakujacy->getSila() < 5) return true;
    return false;
}