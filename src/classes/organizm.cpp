#include <iostream>
#include <random>
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
//zwraca liczbe od 0 do 3 wlacznie, w celu wybrania kierunku ruchu przez organizm
int Organizm::getRandomDir(){
    //static urzywany zeby nie resetowac tego z kazdym wywolaniem funkcji 
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0,3);
    return dis(gen);
}

//funkcja sprawdza czy nie zwierze nie probuje wyjsc poza plansze
bool Organizm::isInBounds(WINDOW* win, int y, int x) {
    int h, w;
    getmaxyx(win, h, w);
    return y > 0 && y < h-1 && x > 0 && x < w-1;
}
pair<int, int> Organizm::znajdzWolnePoleObok(){
    static const int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

    for(auto [dx, dy] : dirs){
        int new_x = getPozycjaX() + dx;
        int new_y = getPozycjaY() + dy;

        //sprawdza czy nowo wybrana pozycja jest wolna i czy nie jest poza granicami swiata
        if( isInBounds(getSwiat()->getWin(), new_x, new_y) && 
            getSwiat()->findOrganismAt(new_x, new_y) == nullptr)
            return {new_x, new_y};
    }

    return {-1,-1}; //brak miejsca -> trzeba sprawdzic to w funckji wywolujacej
}

bool Organizm::czyOdbilAtak(Organizm* atakujacy){
    return false; //wersja podstawowa - roznica tylko dla zowia i tarczy alzuara
}
void Organizm::wplywNaSile(Organizm* atakujacy){}