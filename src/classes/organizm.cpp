#include <iostream>
#include "organizm.h"
#include "swiat.h"

using namespace std;

//konstruktor
Organizm::Organizm(int sila, int inicjatywa, int pozycja_x, int pozycja_y, Swiat* swiat)
    :sila(sila), inicjatywa(inicjatywa), pozycja_x(pozycja_x), pozycja_y(pozycja_y), swiat(swiat) {}
//destruktor
Organizm::~Organizm() {};

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
bool Organizm::getZyje() const{
    return zyje;
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

void Organizm::setZyjeFalse(){
    zyje = false;
}

bool Organizm::wiekszaSilaOd(Organizm* other){
    if(this->sila >= other->getSila()) return true;
    else return false;
}