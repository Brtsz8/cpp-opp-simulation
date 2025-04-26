#include <iostream>
#include <ncurses.h>
#include <algorithm>
#include <vector>
#include <fstream>
#include "swiat.h"
#include "animals/antylopa.h"
#include "animals/czlowiek.h"
#include "animals/lis.h"
#include "animals/owca.h"
#include "animals/wilk.h"
#include "animals/zolw.h"
#include "plants/barszcz.h"
#include "plants/mlecz.h"
#include "plants/jagody.h"
#include "plants/trawa.h"
#include "plants/guarana.h"


using namespace std;

Swiat::Swiat(WINDOW *new_win, WINDOW *new_log_win) : win(new_win), log_window(new_log_win) {}

Swiat::~Swiat(){
    usunOrganizmy(); //prevents memory leaks, clear-up after simulation
    for(Organizm* organizm : nowe){
        delete organizm;
    }
    nowe.clear();
    logs.clear();
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

int Swiat::getCommand(){
    return command;
}

//setter do okienka z logami
void Swiat::setTopLogIndex(int index){
    if(index>=0 && index<=(int)logs.size()-getmaxy(log_window)+2)
    topLog = index;
}

void Swiat::setCommand(int command)
{
    this->command = command;
}

void Swiat::nowyOrganizm(Organizm* organizm){
    //organizmy.push_back(organizm);
    nowe.push_back(organizm);
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
        if (organizm->getZyje()) organizm->akcja();
    }
    usunZabite();
    for(Organizm* organizm : nowe){
        organizmy.push_back(organizm);
    }
    nowe.clear();
    
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
    for(Organizm* organizm : nowe){
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

void Swiat::save(string filePath){
    ofstream file(filePath);
    if(!file.is_open()) return;
    file<<"Win"<<endl;
    for(Organizm* organizm : organizmy){
        file<<organizm->nazwa()<<" "
            <<organizm->getPozycjaX()<<" "
            <<organizm->getPozycjaY()<<" "
            <<organizm->getSila()<<endl;  //sila musi byc bo ona tez moze byc zmieniana (inicjatywa nie)
    }
    file<<"LogWindow"<<endl;
    for(string log : logs) file<<log<<endl;
    file.close();
}

void Swiat::load(string filePath){
    usunOrganizmy(); //czyscimy swiat
    logs.clear(); //czyscimy logi

    ifstream file(filePath);
    if(!file.is_open()) return;
    string line;
    int pozycja_x,pozycja_y,sila;
    file>>line; //pierwszy buffer
    while(file>>line && line!="LogWindow"){
        file>>pozycja_x>>pozycja_y>>sila;
        Organizm* organizm = nullptr;
        if (line == "Wilk") {
            organizm = new Wilk(pozycja_x, pozycja_y, this);
        }
        else if (line == "Owca") {
            organizm = new Owca(pozycja_x, pozycja_y, this);
        }
        else if (line == "Lis") {
            organizm = new Lis(pozycja_x, pozycja_y, this);
        }
        else if (line == "Zolw") {
            organizm = new Zolw(pozycja_x, pozycja_y, this);
        }
        else if (line == "Antylopa") {
            organizm = new Antylopa(pozycja_x, pozycja_y, this);
        }
        else if (line == "Trawa") {
            organizm = new Trawa(pozycja_x, pozycja_y, this);
        }
        else if (line == "Mlecz") {
            organizm = new Mlecz(pozycja_x, pozycja_y, this);
        }
        else if (line == "Guarana") {
            organizm = new Guarana(pozycja_x, pozycja_y, this);
        }
        else if (line == "Wilcze Jagody") {
            organizm = new Jagody(pozycja_x, pozycja_y, this);
        }
        else if (line == "Barszcz Sosnowskiego") {
            organizm = new Barszcz(pozycja_x, pozycja_y, this);
        }
        else if (line == "Czlowiek") {
            organizm = new Czlowiek(pozycja_x, pozycja_y, this);
        }

        if(organizm){
            organizm->setSila(sila);
            nowyOrganizm(organizm);
        }
    }
    while(getline(file,line))
    {
        if(!line.empty()) logs.push_back(line);
    }
    file.close();
}