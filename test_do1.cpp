#include "source.cpp"
#include <iostream>

using namespace std;

typedef Uczestnik u;

int main(){
    Wodzirej w;
    u a(u::M);
    u b(u::K); 
    u c(u::W);
    u d(u::M);
    u e(u::K);
    u f(u::M);

    w.dolacz(&a);
    w.dolacz(&b);
    w.dolacz(&c);
    w.dolacz(&d);
    w.dolacz(&e);
    w.dolacz(&f);
    w.dolacz(&c);
    w.uczestnicy();
}    