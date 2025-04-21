#ifndef ORGANIZM_H
#define ORGANIZM_H

#include <iostream>
#include <ncurses.h>
using namespace std;

class Swiat;

//abstract base
class Organizm{
    private:
        int sila;
        int inicjatywa;
        int pozycja_x;
        int pozycja_y;
        Swiat* swiat;
    public:
        Organizm(int sila, int inicjatywa, int pozycja_x, int pozycja_y, Swiat* swiat);
        virtual ~Organizm();
        virtual void akcja() = 0 ;
        virtual void kolizja(int from_x, int from_y, Organizm* other) = 0;
        //zwraca symbol do narysowania
        virtual char rysowanie() = 0;
        
        //gettery
        int getSila() const;
        int getInicjatywa() const;
        int getPozycjaX() const;
        int getPozycjaY() const;
        Swiat* getSwiat() const;
        //settery
        void setSila(int newSila);
        void setInicjatywa(int newInicjatywa);
        void setPozycja(int newX, int newY);
};
#endif