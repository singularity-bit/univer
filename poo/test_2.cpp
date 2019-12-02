#include<iostream>
#include<string.h>
#include<conio.h>
#include<string>

using namespace std;
class lista;//prototipul clasei lista
class produse_magazin{
    int tip_derivat;//1-scanere,2-imprimante
    string producator;
    produse_magazin*urm;
    public:
    produse_magazin(int t,string prod)//constructor
    {
        tip_derivat=t;
        producator=prod;
        urm=NULL;
    }
    virtual void afisare()//fuctie de afisarea elementelor din clasa de baza
    {
        cout<<"-----------------------\n";
        cout<<"Producator: "<<producator<<endl;
    }
    friend class lista;//pentru a avea acces la campurile clasei
};

class scanere:public produse_magazin{
    int viteza_scanare;
    public:scanere(int t,string prod,int viteza):produse_magazin(t,prod){
        viteza_scanare=viteza;
    }
    void afisare(){
        produse_magazin::afisare();
        cout<<"viteza de scanare: "<<viteza_scanare<<endl;
    }
    friend class lista;
};
class imprimante:public produse_magazin{
    string format;
    public:
        imprimante(int t,string prod,string form):produse_magazin(t,prod){
            format=form;
        }
        void afisare(){
            produse_magazin::afisare();
            cout<<"format: "<<format<<endl;
        }
        friend class lista;
};
class lista{
    public:
        produse_magazin*head;
        void adaugare(produse_magazin*prod);
        void afisare_lista();
        void stergere(string);
        void cautare(string);
};
void lista::adaugare(produse_magazin*a){
    produse_magazin*p;
    p=head;//se initializeaza capul listei
    if(p){
        if(a->producator<p->producator){
            a->urm=head;
            head=a;
        }else{
            while(p->urm&&(p->urm)->producator<a->producator)
                p=p->urm;
            a->urm=p->urm;
            p->urm=a;
        }
    }
    else
    {
        head=a;
    }
}
void lista::afisare_lista(){
    produse_magazin*a;
    a=head;
    if(!a)
        cout<<"\nlista este vida!\n";
    else
        {
            while(a){
                a->afisare();
                a=a->urm;
                _getch();
            }
        } 
}
void lista::cautare(string prod){
    produse_magazin*a;
    a=head;
    if(!a)
        cout<<"\nlista este vida!\n";
    else{
        while(a&&a->producator!=prod){
            
            a=a->urm;
            a->afisare();
            _getch();
           
        }
    }
}
class supraincarcare{
    string producator;
    public:
        friend ostream & operator << (ostream &out,supraincarcare &a);
        friend istream & operator >>(istream &in,supraincarcare &a);
        string return_producator(){
            return producator;
        }
};
ostream & operator <<(ostream &out,supraincarcare &a){
    cout<<"vom citi datele pentru scanere si imprimante: "<<endl;
    cout<<endl;
    return out;
}
istream & operator >> (istream &in,supraincarcare &a){
    cout<<"\nproducatorul: ";
    cin>>a.producator;
    return in;
}
class MyException{
    public:
        string str_what;
        int what;
        MyException(){
            str_what=" ";
            what=0;
        }
        MyException(string s,int e){
            str_what=s;
            what=e;
        }
};
void introducere(lista &list,int x){
    int tip_derivat;
    int viteza_scanare;
    string format;
    produse_magazin*prod_mag;
    supraincarcare supr;
    cout << supr;
    cin >> supr;
    if(x==1)//optiunea 1
    {
        int ok=1;
        scanere*sc;
        try{
            cout<<"\n introduceti viteza de scanare: ";
            cin>>viteza_scanare;
            if(viteza_scanare<0)
                throw MyException("\nviteza de scanare nu are o valoare pozitiva\n",viteza_scanare);

        }
        catch(MyException e){
            do{
                cout<<"\nintroduceti valoare pozitiva: ";
                cin>>viteza_scanare;
            }while(viteza_scanare<0);
        }
        sc=new scanere(1,supr.return_producator(),viteza_scanare);
        prod_mag=sc;
        list.adaugare(prod_mag);
    }
    else if(x==2){
        imprimante*impr;
        cout<<"\nintroduceti formatul imprimantei: ";
        cin>>format;
        impr=new imprimante(2,supr.return_producator(),format);
        prod_mag=impr;
        list.adaugare(prod_mag);
    }
}
void lista::stergere(string prod){
    produse_magazin*p,*q;
    p=q=head;
    if(p){
        while(p&&p->producator!=prod){
            q=p;
            p=p->urm;
        }
        if(p){
            if(p!=q){
                q->urm=p->urm;
                delete p;
            }
            else{
                head=p->urm;
                delete p;
            }
        }
        else
        {
            cout<<"\nprodusul nu exista!\n";
        }
        
    }
    else{
        cout<<"\nlista este vida!";
    }
}
int main(){
    int opt;
    lista list;
    string producator;
    list.head=NULL;
    do{
        system("CLS");
        cout << "1.Adaugare scanere in lista, ordonat dupa producator.\n";
		cout << "2.Adaugare imprimante in lista, ordonat dupa producator.\n";
		cout << "3.Afisare articole din magazin.\n";
		cout << "4.Stergerea unui articol dupa producator \n";
		cout << "5.Cautarea unui articol dupa producator \n";
		cout << "0.Iesire.\n";
        cout<<"\n alegeti o varianta: ";
        cin>>opt;
       switch(opt){
           case 1:  introducere(list,1);
                    break;
            case 2: introducere(list,2);
                    break;
            case 3: list.afisare_lista();
                    break;
            case 4: cout<<"\nintroduceti articolul dorit sa fie sters: ";
                    cin>>producator;
                    list.stergere(producator);
                    break;
            case 5: cout<<"\nintroduceti articolul pe care doriti sa-l cautati: ";
                    cin>>producator;
                    list.cautare(producator);
                    break;
            case 0: break;
            default:cout<<"\ncomanda gresita!";
       }
    }while(opt!=0);
    return 0;
}
