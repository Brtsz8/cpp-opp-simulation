#include <iostream>
#include <ncurses.h>
#include <algorithm>
#include <vector>
#include "swiat.h"

using namespace std;

Swiat::Swiat(WINDOW *new_win, WINDOW *new_log_win) : win(new_win), log_window(new_log_win) {}

Swiat::~Swiat(){
    usunOrganizmy(); //prevents memory leaks, clear-up after simulation
}

void Swiat::usunOrganizmy() {
    for (Organizm* organizm : organizmy) {
        if(organizm != nullptr) delete organizm; 
    }
    organizmy.clear(); 
}

//gettery do okien, wazne przy wyświetlaniu zwierzat/informacji 
WINDOW* Swiat::getWin(){
    return win;
}
WINDOW* Swiat::getLog(){
    return log_window;
}

//getter do okienka z logami
int Swiat::getTopLogIndex(){
    return topLog;
}

//setter do okienka z logami
void Swiat::setTopLogIndex(int index){
    topLog = index;
}

void Swiat::nowyOrganizm(Organizm* organizm){
    organizmy.push_back(organizm);
}

void Swiat::nowyLog(string log){
    logs.push_back(log);
}

void Swiat::wyswietlLogi(int pierwszyLog){
    werase(log_window);         //czysci okno logow
    box(log_window, 0, 0);

    long unsigned int maxLines = getmaxy(log_window)-2;  //to -2 ze wzgl na ramke
    for(size_t i=0; i < maxLines && i <logs.size(); ++i){
        long unsigned int logIndex = pierwszyLog + i;

        //sprawdzenie czy urzytkownik nie wyskoczył poza zakres klikajac strzalki
        if(logIndex >= logs.size()) logIndex = logs.size();
        if(logIndex < 0) logIndex = 0;

        mvwprintw(log_window, i+1, 1, "%s", logs[logIndex].c_str());
    }

    wrefresh(log_window);
}

void Swiat::wykonajTure(){
    sortujWszystkie();
    
    for (size_t i = 0; i < organizmy.size(); ++i) {
        Organizm* organizm = organizmy[i];
        if (organizm->getZyje()) {
            organizm->akcja();
        }
    }
    usunZabite();
    rysujSwiat();
    wyswietlLogi(topLog);
}

void Swiat::rysujSwiat() {
    wclear(win);
    //to zrobie pozniej
    //wclear(log_window) 
    for(Organizm* organizm : organizmy){
       if(organizm == nullptr) continue;
       mvwaddch(win,organizm->getPozycjaY(),organizm->getPozycjaX(),organizm->rysowanie());
    }
    box(win,0,0);
    wrefresh(win);
}

Organizm* Swiat::findOrganismAt(int x, int y){
    for(Organizm* organizm : organizmy){
        if (organizm->getPozycjaX() == x && organizm->getPozycjaY() == y){
            return organizm;
        }   
    }
    return nullptr;
}

void Swiat::sortujWszystkie() {
    std::stable_sort(organizmy.begin(), organizmy.end(), [](Organizm* a, Organizm* b) {
        return a->getInicjatywa() > b->getInicjatywa(); // only initiative matters
    });
}

void Swiat::usunZabite(){
    for (size_t i = 0; i < organizmy.size(); ++i) {
        Organizm* organizm = organizmy[i];
        if (!organizm->getZyje()) {
            organizmy.erase(organizmy.begin()+i); //usun z listy organizmow
            delete organizm;
            i--;
        }
    }
}