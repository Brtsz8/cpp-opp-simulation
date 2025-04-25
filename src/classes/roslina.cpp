#include <iostream>
#include <random>
#include <sstream>
#include "roslina.h"
#include "swiat.h"

using namespace std;

//konstruktor
Roslina::Roslina(int sila, int pozycja_x, int pozycja_y, Swiat* swiat)
    : Organizm(sila, 0, pozycja_x, pozycja_y,swiat) {}

int Roslina::czyRosnie(){
    //static urzywany zeby nie resetowac tego z kazdym wywolaniem funkcji 
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0,9);
    return dis(gen);
}


//akcja ktora zalezy od typu zwierzecia
void Roslina::akcja(){
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

    if(czyRosnie()%3!=0) return;


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
        if(new_x == -1 && new_y == -1) return; //gdy nie ma miejsca na nowy organizm to konczymy
        
        Organizm* potomek = this->dodajPotomka(new_x, new_y);
        log<<"Dodano nowy organizm na x:"<<new_x<<" y:"<<new_y;
        if(potomek == nullptr) { cout<<"Nie udało sie stworzyc potomka - błąd programu :(";};
        if(potomek) getSwiat()->nowyOrganizm(potomek);
        return;
    }
    //w przeciwnym razie kolizja
    else{
       //kolizja(from_x, from_y, other);
    }
    getSwiat()->nowyLog(log.str());
}

void Roslina::kolizja(int from_x, int from_y, Organizm* other){}