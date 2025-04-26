#include <iostream>
#include <ncurses.h>
#include <sstream>
#include "../roslina.h"
#include "mlecz.h"
#include "../swiat.h"
using namespace std;

Mlecz::Mlecz(int pozycja_x, int pozycja_y, Swiat* swiat) 
    : Roslina(0, pozycja_x, pozycja_y, swiat) {};

Mlecz::~Mlecz() {};

char Mlecz::rysowanie() const {
    return '@';
}
string Mlecz::nazwa() const {
    return "Mlecz";
}

Organizm* Mlecz::dodajPotomka(int x, int y) const {
    Organizm* mlodyMlecz = new Mlecz(x,y,getSwiat());
    return mlodyMlecz;
}

void Mlecz::akcja(){
    ostringstream log;  //do wypisywania logow
    if (getSwiat() == nullptr) {
        std::cerr << "Błąd: getSwiat() == nullptr\n";
        abort();
    }

    WINDOW* win = getSwiat()->getWin();
    if (win == nullptr) {
        std::cerr << "Błąd: getWin() == nullptr\n";
        abort();
    }
    int proby=3;
    while(proby){
        proby--;
        if(czyRosnie()%3!=0) continue;


        int dir = getRandomDir();
        int move_x[] = {0, 0, -1, 1};
        int move_y[] = {-1, 1, 0, 0};
        
        int from_x = getPozycjaX();
        int from_y = getPozycjaY();
    
        int new_x = from_x + move_x[dir];
        int new_y = from_y + move_y[dir];
    
        
        if(!isInBounds(win, new_y, new_x )) continue;;
        //znajduje organizm na miejsu do ktorego chce sie ruszyc
        Organizm* other = getSwiat()->findOrganismAt(new_x,new_y);
        
        //jezeli w dany miejsu nie ma zadnego organizmu
        if(other == nullptr)
        {
            if(new_x == -1 && new_y == -1) continue; //gdy nie ma miejsca na nowy organizm to konczymy
            
            Organizm* potomek = this->dodajPotomka(new_x, new_y);
            log<<"Dodano nowy"<<potomek->nazwa()<<" na x:"<<new_x<<" y:"<<new_y<<" ";
            if(potomek == nullptr) { cout<<"Nie udało sie stworzyc potomka - błąd programu :(";};
            if(potomek) getSwiat()->nowyOrganizm(potomek);
            getSwiat()->nowyLog(log.str());
            continue;
        }
        //w przeciwnym razie kolizja
        else{
            //kolizja(from_x, from_y, other);
        }
    }
   
}
