//Tomasz Koczar

#include "Uczestnik.h"
#include <iostream>

class Gracz{
    Uczestnik* osoba;
    unsigned int indentyfikator;
    Gracz* lewy;
    Gracz* prawy;

    bool posiadacz=false;

    public:
    Gracz(){};
    Gracz(Uczestnik &osoba): osoba(&osoba){};
    Gracz(Uczestnik *osoba): osoba(osoba){};

    void set_id(unsigned int i){indentyfikator=i;}
    unsigned int get_id()const{return indentyfikator;}

    void set_left(Gracz* gracz){lewy=gracz;}
    void set_right(Gracz* gracz){prawy=gracz;}

    Gracz* get_left()const{return lewy;};
    Gracz* get_right()const{return prawy;};

    bool posses()const{return posiadacz;}
    void take(){posiadacz=false;}
    void give(){posiadacz=true;}

    Uczestnik::Plec get_sex() const{return osoba->plec;}
    void set_sex(Uczestnik::Plec p) {osoba->plec=p;}

    Uczestnik* get_player()const{return osoba;}
    void set_player(Uczestnik *o){osoba=o;}
    int convert_sex_to_int()const{
        if(get_sex()==Uczestnik::K) return 0;
        if(get_sex()==Uczestnik::M) return 1;
        return 2;
    }
    void wypisz()const{
        std::cout << "plec: " << convert_sex_to_int()<< ", nr: " << get_id() << std::endl; 
    }
    void wypiszs()const{
        std::cout<<"nr: " << get_id() << std::endl;
    }

    void make_wodzirej(){
        set_right(this);
        set_left(this);
        set_id(0);
        give();
        Uczestnik* w=new Uczestnik(Uczestnik::W);
        set_player(w);
    }
};

    

class Koleczko{
    Gracz wodzirej;
    unsigned int id=1;
    bool going=false;
    public:
    Koleczko(){wodzirej.make_wodzirej();}
    unsigned int insert(Gracz& obecny,Uczestnik* uczestnik){ 
        
        Gracz* gracz=new Gracz(uczestnik);
        gracz->set_id(id);
        id++;
        gracz->set_left(&obecny);
        gracz->set_right(obecny.get_right());
        obecny.get_right()->set_left(gracz);
        obecny.set_right(gracz);
        return gracz->get_id();
    }

    unsigned int insert_left(Gracz* obecny,Uczestnik* uczestnik){ 
        Gracz* gracz=new Gracz(uczestnik);
        gracz->set_id(id);
        id++;
        gracz->set_right(obecny);
        gracz->set_left(obecny->get_left());
        obecny->get_left()->set_right(gracz);
        obecny->set_left(gracz);
        return gracz->get_id();
    }

    unsigned int push_front(Uczestnik* uczestnik){
        return insert(wodzirej,uczestnik);
    }

    void remove(Gracz* gracz){
        gracz->get_left()->set_right(gracz->get_right());
        gracz->get_right()->set_left(gracz->get_left());
        delete gracz;

    }

    unsigned int size()const {
        Gracz*ptr=wodzirej.get_right();
        int i=1;
        while(ptr!=&wodzirej){
            i++;
            ptr=ptr->get_right();
        }
        return i;
    }

    bool isgoing()const{return going;}
    void start(){going=true;}
    void stop(){going=false;}

    bool present(Uczestnik* osoba){
        Gracz* ptr=get_wodzirej();
        do{
            if(ptr->get_player()==osoba) return true;
            ptr=ptr->get_right();
        }while(ptr!=&wodzirej);
        return false;
    }

    Gracz* get_gamer_left(unsigned int pozycja){
        Gracz* ptr=&wodzirej;
        for(unsigned int i=0;i<pozycja;++i){
            ptr=ptr->get_left();
        }
        return ptr;
    }

    Gracz* get_wodzirej(){
        return &wodzirej;
    }

    Uczestnik* get_wodzirej_player()const{
        return wodzirej.get_player();
    }
    
    Gracz* get_owner(){
        Gracz* ptr=&wodzirej;
        if(ptr->posses()) return ptr;
        ptr=ptr->get_right();
        while (ptr!=&wodzirej){
            if(ptr->posses()) return ptr;
            ptr=ptr->get_right();
        }
        return 0;
    }

    bool change_owner(Gracz* g1,Gracz* g2){
        if(g1->get_sex()==g2->get_sex()) return false;
        g1->take();
        g2->give();
        return true;
    }

    int get_female(){
        int i=0;
        Gracz* ptr=wodzirej.get_right();
        while (ptr!=&wodzirej){
            if(ptr->convert_sex_to_int()==0) i++;
            ptr=ptr->get_right();
        }
        return i;
    }
    int get_male(){
        int i=0;
        Gracz* ptr=wodzirej.get_right();
        while (ptr!=&wodzirej){
            if(ptr->convert_sex_to_int()==1) i++;
            ptr=ptr->get_right();
        }
        return i;
    }

    Gracz* get_gamer(Uczestnik* osoba){
        if(osoba==wodzirej.get_player()) return &wodzirej;
        Gracz*ptr=wodzirej.get_right();
        while (ptr!=&wodzirej){
            if(ptr->get_player()==osoba) return ptr;
            ptr=ptr->get_right();
        }
        return 0;
    }    
    Gracz* get_gamer(unsigned int id){
        if(id==0) return &wodzirej;
        Gracz *ptr=wodzirej.get_right();
        while (ptr!=&wodzirej){
            if(ptr->get_id()==id) return ptr;
            ptr=ptr->get_right();
        }
        return 0;
    }

    void wypisz()const{
        const Gracz* ptr=&wodzirej;
        for(unsigned int i=0;i<size();i++){
            ptr->wypisz();
            ptr=ptr->get_left();
        }


    }

    void wypisz(Uczestnik::Plec p)const{
        const Gracz* ptr=&wodzirej;
        if(p==Uczestnik::W){
            ptr->wypiszs();
            
        }else{
        
            for(unsigned int i=0;i<size();i++){
                if(ptr->get_sex()==p) ptr->wypiszs();
                ptr=ptr->get_right();
            }
        }
    }

    unsigned int get_id()const{return id;}

    ~Koleczko(){
        delete wodzirej.get_player();
        Gracz * ptr= wodzirej.get_left();
        while (ptr!=&wodzirej)
        {
            Gracz* ptr2=ptr->get_left();
            delete ptr;
            ptr=ptr2;
        }
        
    }
};

class Wodzirej{
    Koleczko k;
    public:
    Wodzirej(){};
    unsigned int dolacz(Uczestnik* osoba){
        if(osoba==0) return 0;
        if(osoba->plec==Uczestnik::W)return 0;
        if(k.present(osoba))return 0;
        return (k.push_front(osoba));
    }
    unsigned int dolacz(Uczestnik* osoba, unsigned int pozycja){
        if(osoba==0) return 0;
        if(osoba->plec==Uczestnik::W)return 0;
        if(k.present(osoba))return 0;
        if(pozycja>=k.size()) return 0;
        Gracz* obecny=k.get_gamer_left(pozycja);
        return k.insert_left(obecny,osoba);
    }

    bool rozpocznij(){
        if(k.isgoing())return false;
        if(k.size()==1) return false;
        if(k.get_female()==0||k.get_male()==0) return false;
        k.start();
        k.change_owner(k.get_wodzirej(),k.get_wodzirej()->get_right());
        return true;
    }

    bool zakoncz(){
        if(k.isgoing()){
            k.change_owner(k.get_owner(),k.get_wodzirej());
            return true;
        }
        return false;
    }

    bool zrezygnuj(Uczestnik* osoba){
        if(osoba==0) return false;
        if(!k.get_gamer(osoba)) return false;
        Gracz* gracz=k.get_gamer(osoba);
        if(gracz==k.get_wodzirej()) return false;
        if(gracz->posses()) return false;
        k.remove(k.get_gamer(osoba));
        return true;
    }

    bool zrezygnuj(unsigned int id){
        if(id==0) return false;
        if(id>=k.get_id()) return false;
        Gracz *gracz=k.get_gamer(id);
        if(gracz==0) return false;
        if(gracz->posses()) return false;
        k.remove(gracz);
        return true;
    }

    bool przekaz(Uczestnik* osoba){
        if(!k.isgoing()) return false;
        Gracz* gracz=k.get_gamer(osoba);
        if(gracz==0 || gracz==k.get_wodzirej()) return false;
        return k.change_owner(k.get_owner(),gracz);
    }

    bool przekaz(unsigned int id){
        if(!k.isgoing()) return false;
        if(id==0) return false;
        if(id>=k.get_id()) return false;
        Gracz* gracz=k.get_gamer(id);
        if(gracz==0) return false;
        return k.change_owner(k.get_owner(),gracz);
    }

    void uczestnicy()const{
        k.wypisz();
    }  

    void uczestnicy(Uczestnik::Plec p)const{
        k.wypisz(p);
    }

    unsigned int liczba()const{
        return k.size();
    } 

    int size(){
        return k.size();
    }

    Uczestnik* wodzirej()const{
        return(k.get_wodzirej_player());
    }

};
