#include <iostream>
#include <ncurses.h>
#include <random>
#include <sstream>
#include "../roslina.h"
#include "../zwierze.h"
#include "barszcz.h"
#include "../swiat.h"
using namespace std;

Barszcz::Barszcz(int pozycja_x, int pozycja_y, Swiat* swiat) 
    : Roslina(99, pozycja_x, pozycja_y, swiat) {};

Barszcz::~Barszcz() {};

char Barszcz::rysowanie() const {
    return '!';
}

string Barszcz::nazwa() const {
    return "Barszcz Sosnowskiego";
}

Organizm* Barszcz::dodajPotomka(int x, int y) const {
    Organizm* mlodaBarszcz = new Barszcz(x,y,getSwiat());
    return mlodaBarszcz;
}

void Barszcz::kolizja(int from_x, int from_y, Organizm* other){
    ostringstream log;
    log<<nazwa()<<" zostal zjedzony - "<<other->nazwa()<<" ginie";
    other->setSila(-1); //zabija atakujacy organizm

    getSwiat()->nowyLog(log.str());
    setZyjeFalse();
}
void Barszcz::wplywNaSile(Organizm* atakujacy){
    ostringstream log;
    log<<nazwa()<<" zostal zjedzony - "<<atakujacy->nazwa()<<" ginie";
    getSwiat()->nowyLog(log.str());
    atakujacy->setSila(-1); //zmienijsza sile organizmu ponizej zera - zabija
}
void Barszcz::akcja(){
    ostringstream log;
    int barszczX = getPozycjaX();
    int barszczY = getPozycjaY();
    auto win = getSwiat()->getWin();

    int del_x[4] = { barszczX ,barszczX  ,barszczX-1,barszczX+1};
    int del_y[4] = {barszczY-1,barszczY+1,barszczY  ,barszczY};
    
    for (int i = 0; i < 4; ++i) {
        if (isInBounds(win,del_y[i],del_x[i])) {
            Organizm* sasiad = getSwiat()->findOrganismAt(del_x[i],del_y[i]);
            if (sasiad != nullptr && dynamic_cast<Zwierze*>(sasiad) != nullptr) {
                log<<nazwa()<<" zabija "<<sasiad->nazwa()<<" ktory byl za blisko";
                getSwiat()->nowyLog(log.str());
                sasiad->setZyjeFalse();
            }
        }
    }

    Roslina::akcja();
}