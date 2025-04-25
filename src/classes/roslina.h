#ifndef ROSLINA_H
#define ROSLINA_H

#include <iostream>
#include "organizm.h"

using namespace std;

class Roslina : public Organizm{
    public:
    Roslina(int sila, int inicjatywa, int pozycja_x, int pozycja_y, Swiat* swiat);
    virtual ~Roslina();

    virtual void akcja() override;
    virtual void kolizja(int from_x, int from_y, Organizm* other) override;
    pair<int, int> znajdzWolnePoleObok();
    int getRandomDir();
    bool isInBounds(WINDOW* win, int y, int x);
};
#endif