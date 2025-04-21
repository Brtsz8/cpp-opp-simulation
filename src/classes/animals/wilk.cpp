#include <iostream>
#include <ncurses.h>
#include "wilk.h"

using namespace std;

Wilk::Wilk(int pozycja_x, int pozycja_y, Swiat* swiat) 
    : Zwierze(9, 5, pozycja_x, pozycja_y, swiat) {};

Wilk::~Wilk() {};

char Wilk::rysowanie(){
    return 'W';
}
