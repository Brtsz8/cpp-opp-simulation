#include <iostream>
#include <ncurses.h>
#include <random>
#include <sstream>
#include "../zwierze.h"
#include "lis.h"
#include "../swiat.h"
using namespace std;

Lis::Lis(int pozycja_x, int pozycja_y, Swiat* swiat) 
    : Zwierze(3, 7, pozycja_x, pozycja_y, swiat) {};

Lis::~Lis() {};

char Lis::rysowanie(){
    return 'L';
}

Organizm* Lis::dodajPotomka(int x, int y){
    Organizm* mlodyLis = new Lis(x,y,getSwiat());
    return mlodyLis;
}


void Lis::akcja() {
    ostringstream log;
    
    if (getSwiat() == nullptr) {
        std::cerr << "Błąd: getSwiat() == nullptr\n";
        abort();
    }

    WINDOW* win = getSwiat()->getWin();
    if (win == nullptr) {
        std::cerr << "Błąd: getWin() == nullptr\n";
        abort();
    }

    int dir = getRandomDir();
    int move_x[] = {0, 0, -1, 1};
    int move_y[] = {-1, 1, 0, 0};
    
    int from_x = getPozycjaX();
    int from_y = getPozycjaY();

    int new_x = from_x + move_x[dir];
    int new_y = from_y + move_y[dir];

    
    if(!isInBounds(win, new_y, new_x )) return;
    //znajduje organizm na miejsu do ktorego chce sie ruszyc
    Organizm* other = getSwiat()->findOrganismAt(new_x,new_y);
    
    //jezeli w dany miejsu nie ma zadnego organizmu
    if(other == nullptr)
    {
        setPozycja(new_x,new_y);
        
        log << "Przesuwam na nowa pozycje x:"<<new_x<<", y: "<<new_y;
    }
    //w przeciwnym razie kolizja
    else if(wiekszaSilaOd(other)){
        log << "Próba ataku!";
        kolizja(from_x, from_y, other);
    }else{
        log<<"Lis nie rusza sie na pole x:"<<new_x<<" y:"<<new_y<<" -jest slabszy!";
    }
    getSwiat()->nowyLog(log.str());
}