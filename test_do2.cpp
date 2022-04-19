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

    w.dolacz(&a,0);
    w.dolacz(&b,1);
    w.dolacz(&c);
    w.dolacz(&d,1);
    w.dolacz(&e,1);
    w.dolacz(&f);
    w.uczestnicy();
    cout << endl;
    w.zrezygnuj(2);
    w.rozpocznij();
    cout << w.zrezygnuj(1) << endl;
    cout << w.zrezygnuj(5) << endl;
    cout << w.zrezygnuj(20) << endl;
    w.uczestnicy();

}