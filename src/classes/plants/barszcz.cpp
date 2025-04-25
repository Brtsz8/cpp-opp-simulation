#include <iostream>
#include <ncurses.h>
#include <random>
#include <sstream>
#include "../roslina.h"
#include "barszcz.h"
#include "../swiat.h"
using namespace std;

Barszcz::Barszcz(int pozycja_x, int pozycja_y, Swiat* swiat) 
    : Roslina(99, pozycja_x, pozycja_y, swiat) {};

Barszcz::~Barszcz() {};

char Barszcz::rysowanie() const {
    return '!';
}

Organizm* Barszcz::dodajPotomka(int x, int y) const {
    Organizm* mlodaBarszcz = new Barszcz(x,y,getSwiat());
    return mlodaBarszcz;
}

void Barszcz::kolizja(int from_x, int from_y, Organizm* other){
    ostringstream log;
    log<<"Barszcz sosnowskiego zostal zjedzony - ... ginie";
    other->setSila(-1); //zabija atakujacy organizm

    getSwiat()->nowyLog(log.str());
    setZyjeFalse();
}
void Barszcz::wplywNaSile(Organizm* atakujacy){
    ostringstream log;
    log << "Barszcz sosnowskiego zostal zjedzony - ... ginie!";
    getSwiat()->nowyLog(log.str());
    atakujacy->setSila(-1); //zmienijsza sile organizmu ponizej zera - zabija
}