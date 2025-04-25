#include <iostream>
#include <ncurses.h>
#include <random>
#include <sstream>
#include "../roslina.h"
#include "jagody.h"
#include "../swiat.h"
using namespace std;

Jagody::Jagody(int pozycja_x, int pozycja_y, Swiat* swiat) 
    : Roslina(10, pozycja_x, pozycja_y, swiat) {};

Jagody::~Jagody() {};

char Jagody::rysowanie() const {
    return '%';
}

Organizm* Jagody::dodajPotomka(int x, int y) const {
    Organizm* mlodaJagody = new Jagody(x,y,getSwiat());
    return mlodaJagody;
}

void Jagody::kolizja(int from_x, int from_y, Organizm* other){
    ostringstream log;
    log<<"Wilcze jagody zostal zjedzony - ... ginie";
    other->setSila(-1); //zabija atakujacy organizm

    getSwiat()->nowyLog(log.str());
    setZyjeFalse();
}
void Jagody::wplywNaSile(Organizm* atakujacy){
    ostringstream log;
    log << "Wilcze jagody zostal zjedzony - ... ginie!";
    getSwiat()->nowyLog(log.str());
    atakujacy->setSila(-1); //zmienijsza sile organizmu ponizej zera - zabija
}