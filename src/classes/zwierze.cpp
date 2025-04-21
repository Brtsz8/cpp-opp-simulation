#include <iostream>
#include "zwierze.h"
#include "swiat.h"

using namespace std;

//konstruktor
Zwierze::Zwierze(int sila, int inicjatywa, int pozycja_x, int pozycja_y, Swiat* swiat)
                :Organizm(sila, inicjatywa, pozycja_x, pozycja_y,swiat) {}

//Destruktor
Zwierze::~Zwierze() {};

//akcja ktora zalezy od typu zwierzecia
void Zwierze::akcja(){
    setPozycja(getPozycjaX() +1, getPozycjaY() +1);
}

//opisuje co dzieje sie przy kolizji miedzy dwoma zwierzetami
void Zwierze::kolizja(){
}