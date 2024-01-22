//SUBIECT
//(3p) Se considerã o aplica?ie pentru gestionarea activitãþii unei firme distribu?ie.Definiþi o clasã care
//modeleazã un aspect specific acestei activitãþi.Se vor urmãri atribute precum : numele / denumirea
//clientului, produse ºi cantitã?i comandate, pre?uri asociate etc.Datele membre sunt private ?i sunt puse
//la dispoziþie metode de acces.Clasa conþine cel pu?in patru câmpuri, dintre care unul este alocat
//dinamic, constructori, metodele specifice claselor cu membri aloca?i dinamic ºi operatorul de afiºare.
//Folosiþi un membru static sau const.
//(1p) Se va defini operatorul[] pentru a accesa un produs dupã poziþia datã.
//(1 p) Definiþi operatorul += pentru adãugarea unui produs la o comandã.Dacã produsul existã deja in
//comanda, se va incrementa doar cantitatea.
//(2p) Scrie?i într - un fiºier text comenzile care îndeplinesc un criteriu dat, primit ca parametru.
//(2p) Exemplifica?i conceptul de virtualizare prin utilizarea unei clase abstracte.
//(1p) Propune?i un container STL care permite efectuarea rapidã a opera?iilor de inserare / stergere de
//produse intr - o / dintr - o comandã.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string>
#include<fstream>
using namespace std;

class Comanda {
    const int idComanda;
    string numeClient;
    int nrProduse;
    string* denumireProduse;
    float* cantitatiProduse;



public:
    //constructorul fara parametrii/default/implicit
    Comanda() :idComanda(0)
    {
        this->numeClient = "Anonim";
        this->nrProduse = 0;
        this->denumireProduse = NULL;
        this->cantitatiProduse = NULL;

    }





    //Sablon pt Getter
    /*
       tipDeDataVariabila getNumeVariabila(){
       return this->numeVariabila;
       }
    */
    string getNumeClient() {
        return this->numeClient;
    }

    int getNrComenzi() {
        return this->nrProduse;
    }


    //Sablon pt setter
    //IN SETTERI NU MODIFICAM CONST, OP=, OP>>
    /*
      void setNumeVariabila(tipDeDataVariabila numeVariabila){
          this->variabila=variabila;
      }
    */
    void setNumeClient(string numeClient) {
        this->numeClient = numeClient;
    }

    //Constructorul cu toti parametrii
    Comanda(int idComanda, string numeClient, int nrProduse, string* denumireProduse, float* cantitatiProduse) :idComanda(idComanda)
    {
        this->numeClient = numeClient;
        this->nrProduse = nrProduse;
        this->denumireProduse = new string[this->nrProduse]; //scadem o steluta la alocare memorie
        for (int i = 0; i < this->nrProduse; i++) {
            this->denumireProduse[i] = denumireProduse[i];
        }
        this->cantitatiProduse = new float[this->nrProduse]; //scadem o steluta la alocare memorie
        for (int i = 0; i < this->nrProduse; i++) {
            this->cantitatiProduse[i] = cantitatiProduse[i];
        }

    }

    //constructorul de copiere ~contine toti parametrii, toate atributele unei clase

    Comanda(const Comanda& c) :idComanda(c.idComanda) {
        this->numeClient = c.numeClient;
        this->nrProduse = c.nrProduse;
        this->denumireProduse = new string[this->nrProduse]; //scadem o steluta la alocare memorie
        for (int i = 0; i < this->nrProduse; i++) {
            this->denumireProduse[i] = c.denumireProduse[i];
        }
        this->cantitatiProduse = new float[this->nrProduse]; //scadem o steluta la alocare memorie
        for (int i = 0; i < this->nrProduse; i++) {
            this->cantitatiProduse[i] = c.cantitatiProduse[i];
        }
    }

    //de cate ori se apeleaza destructoriul intr-un program?

    ~Comanda() {

        if (this->denumireProduse != NULL) {
            delete[] this->denumireProduse;
        }
        if (this->cantitatiProduse != NULL) {
            delete[] this->cantitatiProduse;
        }
        //cout << "S-a apelat destructorul" << endl;
    }

    //operator=
    //operator = se compune din: evitarea auto-asignarii, destructor(ce e scris in el)+constructor de copiere+return *this;

    Comanda& operator=(const Comanda& c)
    {
        if (this != &c) {
            if (this->denumireProduse != NULL) {
                delete[] this->denumireProduse;
            }
            if (this->cantitatiProduse != NULL) {
                delete[] this->cantitatiProduse;
            }
            this->numeClient = c.numeClient;
            this->nrProduse = c.nrProduse;
            this->denumireProduse = new string[this->nrProduse]; //scadem o steluta la alocare memorie
            for (int i = 0; i < this->nrProduse; i++) {
                this->denumireProduse[i] = c.denumireProduse[i];
            }
            this->cantitatiProduse = new float[this->nrProduse]; //scadem o steluta la alocare memorie
            for (int i = 0; i < this->nrProduse; i++) {
                this->cantitatiProduse[i] = c.cantitatiProduse[i];
            }
            return *this;
        }

    }


    friend ostream& operator<<(ostream& out, const Comanda& c) {
        out << c.idComanda << endl;
        out << c.numeClient << endl;
        out << c.nrProduse << endl;
        for (int i = 0; i < c.nrProduse; i++) {
            out << c.denumireProduse[i] << ",";
        }
        out << endl;

        for (int i = 0; i < c.nrProduse; i++) {
            out << c.cantitatiProduse[i] << ",";
        }
        out << endl;

        return out;
    }

    //ofstream si ifstream sunt de fapt ostream si istream fara text si fara atribute const si static!!

    friend ofstream& operator<<(ofstream& out, const Comanda& c) {
        out << "Id Comanda: " << c.idComanda << endl;
        out << "Client: " << c.numeClient << endl;
        out << "Nr produse:" << c.nrProduse << endl;
        out << "Produse:";
        for (int i = 0; i < c.nrProduse; i++) {
            out << c.denumireProduse[i] << ",";
        }
        out << endl;
        out << "Cantitati produse:";
        for (int i = 0; i < c.nrProduse; i++) {
            out << c.cantitatiProduse[i] << ",";
        }
        out << endl;

        return out;
    }



    string& operator[](int poz) {
        if (poz >= 0 && poz < this->nrProduse) {
            //return this->denumireProduse[poz];
            string denumireSiCantitate = this->denumireProduse[poz];
            denumireSiCantitate += "----";
            denumireSiCantitate += to_string(this->cantitatiProduse[poz]);
            return denumireSiCantitate;

        }
        else {
            string mesaj = " pozitia introdusa este gresita";
            return mesaj;
        }


    }

    //obj+="Tiramisu

    Comanda& operator+=(string denumireProdus)
    {
        bool gasit = 0; //plecam de la remisa ca obiectul pe care vreau sa l adaug nu s eafla in vector
        int pozEl = 0;
        for (int i = 0; i < this->nrProduse; i++) {
            if (this->denumireProduse[i] == denumireProdus) {
                gasit = 1;
                pozEl = i;
            }
        }
        if (gasit == 1) {
            this->cantitatiProduse[pozEl]++;
        }
        else {
            Comanda aux = *this; //apelam constructorul de copiere
            this->nrProduse++;
            if (this->denumireProduse != NULL) {
                delete[]this->denumireProduse;
            }
            this->denumireProduse = new string[this->nrProduse];
            for (int i = 0; i < aux.nrProduse; i++) {
                this->denumireProduse[i] = denumireProduse[i];
            }
            this->cantitatiProduse = new float[this->nrProduse];
            for (int i = 0; i < aux.nrProduse; i++) {
                this->cantitatiProduse[i] = cantitatiProduse[i];
            }
            this->denumireProduse[this->nrProduse - 1] = denumireProdus;
            this->cantitatiProduse[this->nrProduse - 1] = 2;
            return *this;
        }

    }
};

int main()
{
    //obj creat pe baza constructorului fara param implicit sau default
    Comanda c; //Comanda este clasaa, iar c este un obiect de tipul clasei Comanda

    cout << "-------------------------------" << endl << endl;
    cout << c.getNumeClient() << endl;
    c.setNumeClient("Dorel");

    cout << "-------------------------------" << endl << endl;
    cout << c.getNumeClient() << endl;

    //constructor cu toti parametrii
    string denumireProd[] = { "Cafea","Zahar","lapte","Chipsuri","Cola" };
    float cantProd[] = { 6,12.5,8,12,15 };
    Comanda c1(15, "Ion Ion", 5, denumireProd, cantProd);
    Comanda com1(22, "John Ion", 2, denumireProd, cantProd);
    Comanda com2(33, "Tom Ion", 3, denumireProd, cantProd);
    Comanda com3(2, "Home Ion", 5, denumireProd, cantProd);

    cout << "-------------------------------" << endl << endl;
    cout << c1.getNumeClient() << endl;

    cout << "-------------------------------" << endl << endl;

    //constructorul de copiere
    Comanda c2 = c;
    cout << c2.getNumeClient() << endl;

    cout << "-------------------------------" << endl << endl;
    //op=
    c2 = c1;
    cout << c2.getNumeClient();

    cout << "-------------------------------" << endl << endl;
    //op<<
    cout << c2 << endl;


    cout << "-------------------------------" << endl << endl;

    cout << c2[1] << endl;
    c2[1] = "Lapte praf";
    cout << c2 << endl;
    cout << "-------------------------------" << endl << endl;
    //op +=
    c2 += "Sarmale";
    c2 += "Sarmale";
    c2 += "Sarmale";
    c2 += "Sarmale";
    c2 += "Sarmale";
    c2 += "Sarmale";

    cout << c2 << endl;
    cout << "-------------------------------" << endl << endl;
    //scriere in fisier text

    Comanda vectComenzi[] = { c1,com1,com2,com3 };
    ofstream f("comenzi.txt", ios::out);
    for (int i = 0; i < 4; i++) {
        if (vectComenzi[i].getNrComenzi() >= 4) {
            f << vectComenzi[i];
        }
    }
    f.close();

    return 0;
}