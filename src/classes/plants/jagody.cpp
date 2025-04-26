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
string Jagody::nazwa() const {
    return "Wilcze Jagody";
}

Organizm* Jagody::dodajPotomka(int x, int y) const {
    Organizm* mlodaJagody = new Jagody(x,y,getSwiat());
    return mlodaJagody;
}

void Jagody::kolizja(int from_x, int from_y, Organizm* other){
    ostringstream log;
    log<<nazwa()<<" zjedzone - ginie "<<other->nazwa()
       <<" na polu x:"<<other->getPozycjaX()<<" y:"<<other->getPozycjaY();
    other->setSila(-1); //zabija atakujacy organizm

    getSwiat()->nowyLog(log.str());
    setZyjeFalse();
}
void Jagody::wplywNaSile(Organizm* atakujacy){
    ostringstream log;
    log<<nazwa()<<" zjedzone - ginie "<<atakujacy->nazwa()
       <<" na polu x:"<<atakujacy->getPozycjaX()<<" y:"<<atakujacy->getPozycjaY();
    getSwiat()->nowyLog(log.str());
    atakujacy->setSila(-1); //zmienijsza sile organizmu ponizej zera - zabija
}