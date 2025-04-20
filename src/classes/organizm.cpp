#include <iostream>
#include "organizm.h"
#include "swiat.h"

using namespace std;

//gettery
int Organizm::getSila() const{
    return sila;
}
int Organizm::getInicjatywa() const{
    return inicjatywa;
}
int Organizm::getPozycjaX() const{
    return pozycja_x;
}
int Organizm::getPozycjaY() const{
    return pozycja_y;
}
Swiat* Organizm::getSwiat() const{
    return swiat;
}
//settery
void Organizm::setSila(int newSila){
    this->sila = newSila;
}
void Organizm::setInicjatywa(int newInicjatywa){
    this->inicjatywa = newInicjatywa;
}
void Organizm::setPozycja(int newX, int newY){
    this->pozycja_x = newX;
    this->pozycja_y = newY;
}