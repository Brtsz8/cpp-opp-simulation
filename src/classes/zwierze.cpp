#include <iostream>
#include "zwierze.h"
#include "swiat.h"

using namespace std;

//konstruktor
Zwierze::Zwierze(int sila, int inicjatywa, int pozycja_x, int pozycja_y, Swiat* swiat)
                :Organizm(sila, inicjatywa, pozycja_x, pozycja_y,swiat) {}

//Destruktor
Zwierze::~Zwierze() {};

void Zwierze::akcja(){
    cout<<"akcja\n";
    setPozycja(getPozycjaX() +1, getPozycjaY() +1);
}

void Zwierze::kolizja(){
    cout<<"kolizja\n";
}