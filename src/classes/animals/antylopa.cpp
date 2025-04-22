#include <iostream>
#include <ncurses.h>
#include "antylopa.h"
#include "../swiat.h"
using namespace std;

Antylopa::Antylopa(int pozycja_x, int pozycja_y, Swiat* swiat) 
    : Zwierze(4, 4, pozycja_x, pozycja_y, swiat) {};

Antylopa::~Antylopa() {};

char Antylopa::rysowanie(){
    return 'A';
}
