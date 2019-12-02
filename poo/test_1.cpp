// Problema 1 POO INFO AN II 02/12/2019
// Fructe autohtone (denumire, preț) și import (denumire, importator)
// 1. Adăugare fruct
// 2. Afișare stoc sortat după denumire cu posibilitatea de a alege categoria
// 3 Afișare fructe autohtone mai scumpe decât un preț citit de la tastieră
// Pentru nota zece se vor folosi surpraîncărări de operatori/tratare de excepții


#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <string>
using namespace std;

class Exception
{
public:
    string message;
    int data;
    Exception()
    {
        this->message = "";
        this->data = 0;
    }
    Exception(string mesage, int data)
    {
        this->message = mesage;
        this->data = data;
    }
};

class Market
{
private:
    string name;
    Market *next;
    unsigned short int type : 1;

public:
    Market(
        string name,
        unsigned short int type)
    {
        this->name = name;
        this->type = type;
    }
    virtual void display()
    {
        cout << "\nDenumire: " << name;
    }
    int getType()
    {
        return this->type;
    }
    virtual int getPrice()
    {
        return 0;
    }
    friend class List;
};
class Local : Market
{
private:
    int price;

public:
    Local(int price, string name, unsigned short int type) : Market(name, type)
    {
        this->price = price;
    }
    void display()
    {
        Market::display();
        cout << "\nPret: " << price;
    }
    int getPrice()
    {
        return this->price;
    }
    friend class List;
};

class Imported : Market
{
private:
    string importer;

public:
    Imported(string importer, string name, unsigned short int type) : Market(name, type)
    {
        this->importer = importer;
    }
    void display()
    {
        Market::display();
        cout << "\nImportator: " << importer;
    }
    friend class List;
};

class Overload
{
private:
    string name;
    int type;

public:
    string getName()
    {
        return this->name;
    }
    int getType()
    {
        return this->type;
    }
    friend ostream &operator<<(ostream &out, Overload &stream);
    friend istream &operator>>(istream &in, Overload &stream);
};

ostream &operator<<(ostream &out, Overload &stream)
{
    cout << "\nUrmeaza citire:\n";
    return out;
}
istream &operator>>(istream &in, Overload &stream)
{
    cout << "Denumire:";
    cin >> stream.name;
    cout << "Tip (0-autohtone/!0-import): ";
    cin >> stream.type;
    return in;
}

class List
{
public:
    Market *head;
    void displayCategory();
    void displayExpensier();
    void addNode(Market *node);
    void insert();
};

void List::addNode(Market *node)
{
    Market *mptr;
    mptr = head;
    if (mptr)
    {
        if (node->name < mptr->name)
        {
            node->next = head;
            head = node;
        }
        else
        {
            while (mptr->next && (mptr->next)->name < node->name)
                mptr = mptr->next;
            node->next = mptr->next;
            mptr->next = node;
        }
    }
    else
        head = node;
}

void List::displayCategory()
{
    Market *mptr;
    int type;
    if (!head)
        cout << "\nLista este vida";
    else
    {
        cout << "\nTip (0-autohtone/!0-import): ";
        cin >> type;
        for (mptr = head; mptr; mptr = mptr->next)
            if (type == mptr->getType())
                mptr->display();
    }
}

void List::displayExpensier()
{
    Market *mptr;
    int price;
    if (!head)
        cout << "\nLista este vida";
    else
    {
        cout << "\nIntroduceti pretul: ";
        cin >> price;
        for (mptr = head; mptr; mptr = mptr->next)
            if (mptr->getType() == 0 && mptr->getPrice() > price)
                mptr->display();
    }
}

void List::insert()
{
    Market *mptr;
    int price;
    string importer;
    Overload stream;
    cout << stream;
    cin >> stream;
    if (stream.getType())
    {
        cout << "Importator: ";
        cin >> importer;
        Imported *iptr;
        iptr = new Imported(importer, stream.getName(), stream.getType());
        mptr = iptr;
    }
    else
    {
        try
        {
            cout << "Pret: ";
            cin >> price;
            if (price <= 0)
                throw Exception("\nPretul trebuie sa fie pozitiv", price);
        }
        catch (Exception e)
        {
            do
            {
                cout << "\nIntroduceti o valoare pozitiva: ";
                cin >> price;
            } while (price <= 0);
        }
        Local *lptr;
        lptr = new Local(price, stream.getName(), stream.getType());
        mptr = lptr;
    }
    this->addNode(mptr);
}

int main()
{
    int option;
    List list;
    list.head = NULL;
    while (1)
    {
        cout << "\n0.Iesire";
        cout << "\n1.Adaugare fruct in stoc";
        cout << "\n2.Afisarea intregului stoc dupa categorie";
        cout << "\n3.Afisarea fructelor autohtone mai scumpe decat o valoare";
        cout << "\nOptiunea: ";
        cin >> option;
        switch (option)
        {
        case 0:
            return 0;
            break;
        case 1:
            list.insert();
            break;
        case 2:
            list.displayCategory();
            break;
        case 3:
            list.displayExpensier();
            break;
        default:
            break;
        }
    }
    return 0;
}