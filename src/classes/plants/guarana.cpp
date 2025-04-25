#include <iostream>
#include <ncurses.h>
#include <random>
#include <sstream>
#include "../roslina.h"
#include "guarana.h"
#include "../swiat.h"
using namespace std;

Guarana::Guarana(int pozycja_x, int pozycja_y, Swiat* swiat) 
    : Roslina(0, pozycja_x, pozycja_y, swiat) {};

Guarana::~Guarana() {};

char Guarana::rysowanie() const {
    return '&';
}

Organizm* Guarana::dodajPotomka(int x, int y) const {
    Organizm* mlodaGuarana = new Guarana(x,y,getSwiat());
    return mlodaGuarana;
}

void Guarana::kolizja(int from_x, int from_y, Organizm* other){
    ostringstream log;
    log<<"Zwiekszono sile organizmu na polu x:"<<getPozycjaX()<<" y:"<<getPozycjaY();
    auto silaOther = other -> getSila();
    other->setSila(silaOther + 3); //zwieksza sile atakujacego o 3

    getSwiat()->nowyLog(log.str());
    setZyjeFalse();
}
void Guarana::wplywNaSile(Organizm* atakujacy){
    ostringstream log;
    log << "Guarana zostala zjedzona - sila organizmu zwiekszona o 3!";
    getSwiat()->nowyLog(log.str());
    atakujacy->setSila(getSila()+3); //zwieksza sile zwierzecia ktore zjadlo o 3
}