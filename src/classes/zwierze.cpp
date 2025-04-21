#include <iostream>
//nie uzywam rand ze wzgledu na thread safety
#include <random>
#include "zwierze.h"
#include "swiat.h"

using namespace std;

//zwraca liczbe od 0 do 3 wlacznie, w celu wybrania kierunku ruchu przez organizm
int getRandomDir(){
    //static urzywany zeby nie resetowac tego z kazdym wywolaniem funkcji 
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0,3);
    return dis(gen);
}

//funkcja sprawdza czy nie zwierze nie probuje wyjsc poza plansze
bool isInBounds(WINDOW* win, int y, int x) {
    int h, w;
    getmaxyx(win, h, w);
    return y > 0 && y < h-1 && x > 0 && x < w-1;
}

//konstruktor
Zwierze::Zwierze(int sila, int inicjatywa, int pozycja_x, int pozycja_y, Swiat* swiat)
                :Organizm(sila, inicjatywa, pozycja_x, pozycja_y,swiat) {}

//Destruktor
Zwierze::~Zwierze() {};

//akcja ktora zalezy od typu zwierzecia
void Zwierze::akcja(){
    int dir = getRandomDir();
    int move_x[] = {0, 0, -1, 1};
    int move_y[] = {-1, 1, 0, 0};

    int new_x = getPozycjaX() + move_x[dir];
    int new_y = getPozycjaY() + move_y[dir];
    
    if(isInBounds(getSwiat()->getWin(), new_y, new_x ))
    {
        setPozycja(new_x,new_y);
        mvwprintw(getSwiat()->getLog(),1,1,"Przesuwam na nową pozycje x: %d, y: %d",new_x,new_y);
        wrefresh(getSwiat()->getLog());
    }
    
}

//opisuje co dzieje sie przy kolizji miedzy dwoma zwierzetami
void Zwierze::kolizja(){
}