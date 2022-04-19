#include "source.cpp"
#include <iostream>

int main(){
Gracz g;g.set_id(0);
g.set_left(&g);
g.set_right(&g);
g.give();
g.set_sex(Uczestnik::W);
g.wypisz();
g.get_left()->wypisz();
g.get_right()->wypisz();

Uczestnik p(Uczestnik::K);
Gracz g1(&p);
g1.wypisz();

Koleczko k;
}