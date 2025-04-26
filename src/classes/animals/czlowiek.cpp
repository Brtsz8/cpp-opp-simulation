#include <iostream>
#include <sstream>
#include "czlowiek.h"

using namespace std;

Czlowiek::Czlowiek(int pozycja_x, int pozycja_y, Swiat* swiat) :
                    Zwierze(5, 4, pozycja_x, pozycja_y, swiat) {};
char Czlowiek::rysowanie() const {return 'C';}
string Czlowiek::nazwa() const {
    return "Czlowiek";
}


