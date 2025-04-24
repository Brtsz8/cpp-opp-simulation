#ifndef ZWIERZE_H
#define ZWIERZE_H

#include <iostream>
#include "organizm.h"

using namespace std;

class Zwierze : public Organizm{
    public:
    Zwierze(int sila, int inicjatywa, int pozycja_x, int pozycja_y, Swiat* swiat);
    virtual ~Zwierze();

    virtual void akcja() override;
    virtual void kolizja(int from_x, int from_y, Organizm* other) override;
    pair<int, int> znajdzWolnePoleObok();
    int getRandomDir();
    bool isInBounds(WINDOW* win, int y, int x);
};
#endif