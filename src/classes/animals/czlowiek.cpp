#include <iostream>
#include <sstream>
#include <ncurses.h>
#include "czlowiek.h"
#include "../swiat.h"

using namespace std;

Czlowiek::Czlowiek(int pozycja_x, int pozycja_y, Swiat* swiat)
    : Zwierze(5, 4, pozycja_x, pozycja_y, swiat) {};

Czlowiek::~Czlowiek() = default;

char Czlowiek::rysowanie() const {return 'C';}

string Czlowiek::nazwa() const {
    return "Czlowiek";
}
//gettery
bool Czlowiek::getUmiejetnoscAktywna() const {
    return umiejetnoscAktywna;
}
int Czlowiek::getDlugoscUmiejetnosci() const {
    return dlugoscUmiejetnosci;
}
int Czlowiek::getDlugoscRegeneracji() const{
    return dlugoscRegeneracji;
}

//settery
void Czlowiek::setUmiejetnoscAktywna(bool zmianaStanu){
    umiejetnoscAktywna = zmianaStanu;
}
void Czlowiek::setDlugoscUmiejetnosci(int dlugoscUmiejetnosci){
    this->dlugoscUmiejetnosci = dlugoscUmiejetnosci;
}
void Czlowiek::setDlugoscRegeneracji(int dlugoscRegeneracji){
    this->dlugoscRegeneracji = dlugoscRegeneracji;
}

Organizm *Czlowiek::dodajPotomka(int x, int y) const {
    return nullptr; // powinien byc tylko jeden czlowiek!
}

bool Czlowiek::czyOdbilAtak(Organizm* atakujacy){
    ostringstream log;
    if(getUmiejetnoscAktywna()){
        log<<"Czlowiek odbija atak przy pomocy Tarczy Azura!";
        getSwiat()->nowyLog(log.str());
        return true;
    }else return false;
}

void Czlowiek::akcja() {
    ostringstream log;
    //tarcza alzuara//
    if(getDlugoscUmiejetnosci() > 0) setDlugoscUmiejetnosci(getDlugoscUmiejetnosci()-1);
    if(getDlugoscRegeneracji()>0){
        setUmiejetnoscAktywna(false);
        setDlugoscRegeneracji(getDlugoscRegeneracji()-1);
        log<<"Umiejetnosc regeneruje sie!";
        getSwiat()->nowyLog(log.str());
    }
    if(getDlugoscUmiejetnosci()==0 && getUmiejetnoscAktywna()){
        setUmiejetnoscAktywna(false); //wylacz umiejetnosc 
        setDlugoscRegeneracji(5);
        log<<"Umiejetnosc przestala dzialac!";
        getSwiat()->nowyLog(log.str());
    }

    //reszta akcji
    int from_x = getPozycjaX();
    int from_y = getPozycjaY();
    int akcja = getSwiat()->getCommand();
    //log<<"akcja: "<<(char)akcja;
    //getSwiat()->nowyLog(log.str());
    int move_x = from_x;
    int move_y = from_y;

    switch(akcja){
        case KEY_UP:
            move_y--;
            break;
        case KEY_DOWN:
            move_y++;
            break;
        case KEY_RIGHT:
            move_x++;
            break;
        case KEY_LEFT:
            move_x--;
            break;
        case '3':
            if(getUmiejetnoscAktywna()) getSwiat()->nowyLog("Umiejetnosc juz aktywna!");
            else if(getDlugoscRegeneracji()>0){
                log<<"Umiejetnosc bedzie dostepna za "<<getDlugoscRegeneracji()<<" tur!";
                getSwiat()->nowyLog(log.str());
            }
            else{
                setUmiejetnoscAktywna(true);
                setDlugoscUmiejetnosci(5);
                log<<"Tarcza Azura aktywowana! (5 tur)";
                getSwiat()->nowyLog(log.str());
            }
            break;
        default: break;
    }
    //jezeli nie wykonano zadnego ruchu
    if(from_x == move_x && from_y == move_y) return; 
    //ruch
    Organizm* other = getSwiat()->findOrganismAt(move_x,move_y);
    if(other == nullptr && isInBounds(getSwiat()->getWin(),move_y,move_x)){
        setPozycja(move_x,move_y);
        log<<"Czlowiek przesuwa sie na x:"<<move_x<<" y:"<<move_y;
        getSwiat()->nowyLog(log.str());
    }else if(other != nullptr){
        kolizja(from_x, from_y,other);
    }
}

void Czlowiek::kolizja(int from_x, int from_y, Organizm* other) {
    
    ostringstream log;
    Zwierze::kolizja(from_x, from_y, other);
    // TODO: implement later
}

