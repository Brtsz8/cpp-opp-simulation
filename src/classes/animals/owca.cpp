#include <iostream>
#include <ncurses.h>
#include "owca.h"
#include "../swiat.h"
using namespace std;

Owca::Owca(int pozycja_x, int pozycja_y, Swiat* swiat) 
    : Zwierze(4, 4, pozycja_x, pozycja_y, swiat) {};

Owca::~Owca() {};

char Owca::rysowanie() const {
    return 'O';
}

Organizm* Owca::dodajPotomka(int x, int y) const {
    Organizm* mlodaOwca = new Owca(x,y,getSwiat());
    if (mlodaOwca == nullptr) {
        cerr << "[BŁĄD] Nie udało się zaalokować pamięci dla młodej owcy!" << endl;
        return nullptr;
    }
    return mlodaOwca;
}