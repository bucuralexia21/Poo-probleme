// RestantaRazvan.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Enunt examen POO 30 iunie 2020 ora 8.00
Să se scrie o aplicație orientată obiect pentru evidenta activitatilor zilnice ale unei persoane; este necesară cunoașterea activitatii, a orei de desfasurare și a duratei estimate.
Pentru domeniul dat, să se definească o clasă cu membri de tip public, private,  protected, const, static, care să conțină:
(1p) definirea corectă a clasei;
(2p) constructor cu parametri, default constructor, constructor de copiere, destructor și operator<< pentru afișare (0.5 puncte/funcție/operator) ;
(2p) operator=, un operator pentru compararea între obiecte și încă doi operatori adecvați domeniului (aritmetici sau cast sau indexare sau de alt tip) (0.5 puncte/funcție/operator) ;
(1p) două funcții de tip accesor și două metode proprii clasei (0.25 puncte/funcție/operator);
 (1p) funcții sau operatori pentru salvarea și restaurarea obiectelor în/din fișiere binare, permanente.
 (2p) Definiți încă o clasă, capabilă să gestioneze o colecție de obiecte din prima clasă; operatorii += și -= vor asigura adăugarea / scoaterea obiectelor din colecție.
(1p) Transformați una din clase într-o clasă template sau instanțiați o clasă template STL, pentru domeniul dat.
Elementele definite vor fi punctate doar dacă sunt complete și au fost testate în main().

*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string>
using namespace std;

enum grad {
    Usoara,Medie,Grea,FoarteGrea
};

class Activitate {

    const int idActivitate;
    static int numarator;


protected:
    char* denumire;
    string locatie;
    int durata; //in minute
    int nrObiecte;
    string* denumireObiecte;
    float* greutateObiecte;
    grad gradDificultate;


public:

    //ce sunt constructorii?
    //pt ce ii folosim?

    Activitate() :idActivitate(numarator) {
        this->denumire = nullptr;
        this->locatie = "Necunoscuta";
        this->durata = 0;
        this->nrObiecte = 0;
        this->denumireObiecte = nullptr;
        this->greutateObiecte = nullptr;
        this->gradDificultate = Usoara;
    }

    //constructorul cu toti parametrii
    Activitate(const char* denumire, string locatie, int durata, int nrObiecte, string* denumireObiecte,float* greutateObiecte,grad gradDificultate):idActivitate(numarator)
    {
        //validare pt char*
        if (strlen(denumire) >= 3) {
            this->denumire = new char[strlen(denumire) + 1];
            strcpy(this->denumire, denumire);
        }
        else
        {
            this->denumire = new char[strlen("Necunoscut") + 1];
            strcpy(this->denumire, "Necunoscut");
        }
        //validare pt string
        if (locatie.size()>=3 ) //locatie.length()>=3
        {
            this->locatie = locatie;
        }
        else
        {
            this->locatie = "Necunoscuta";
        }

        if (durata > 0)
        {
            this->durata = durata;
        }
        else
        {
            this->durata = 0;
        }

        if (nrObiecte > 0 && denumireObiecte != nullptr && greutateObiecte != nullptr)
        {
            this->nrObiecte = nrObiecte;
            this->denumireObiecte = new string[this->nrObiecte];
            for (int i = 0; i < this->nrObiecte; i++)
            {
                this->denumireObiecte[i] = denumireObiecte[i];
            }


            this->greutateObiecte = new float[this->nrObiecte];
            for (int i = 0; i < this->nrObiecte; i++)
            {
                this->greutateObiecte[i] = greutateObiecte[i];
            }
        }
        else
        {
            this->nrObiecte = 0;
            this->denumireObiecte = nullptr;
            this->greutateObiecte = nullptr;
        }

        this->gradDificultate = gradDificultate;


    }

    //constrcutor de copiere
    //se apeleaza cand cream un obiect nou pe baza altuia care exista
    Activitate(const Activitate& a):idActivitate(a.idActivitate)
    {
        //validare pt char*
        if (strlen(a.denumire) >= 3) {
            this->denumire = new char[strlen(a.denumire) + 1];
            strcpy(this->denumire, a.denumire);
        }
        else
        {
            this->denumire = new char[strlen("Necunoscut") + 1];
            strcpy(this->denumire, "Necunoscut");
        }
        //validare pt string
        if (a.locatie.size() >= 3) //locatie.length()>=3
        {
            this->locatie = a.locatie;
        }
        else
        {
            this->locatie = "Necunoscuta";
        }

        if (a.durata > 0)
        {
            this->durata = a.durata;
        }
        else
        {
            this->durata = 0;
        }

        if (a.nrObiecte > 0 && a.denumireObiecte != nullptr && a.greutateObiecte != nullptr)
        {
            this->nrObiecte = a.nrObiecte;
            this->denumireObiecte = new string[this->nrObiecte];
            for (int i = 0; i < this->nrObiecte; i++)
            {
                this->denumireObiecte[i] = a.denumireObiecte[i];
            }


            this->greutateObiecte = new float[this->nrObiecte];
            for (int i = 0; i < this->nrObiecte; i++)
            {
                this->greutateObiecte[i] = greutateObiecte[i];
            }
        }
        else
        {
            this->nrObiecte = 0;
            this->denumireObiecte = nullptr;
            this->greutateObiecte = nullptr;
        }

        this->gradDificultate = a.gradDificultate;

    }



    const int getIdActivitate(){
        return this->idActivitate;
    }

    char* getDenumire()
    {
        return this->denumire;
    }

    //getteri 

    string getLocatie()
    {
        return this->locatie;
    }

    float* getGreutateObiecte()
    {
        return this->greutateObiecte;
    }
    int getNrObiecte()
    {
        return this->nrObiecte;
    }
    string* getDenumireObiecte()
    {
        return this->denumireObiecte;
    }

    Activitate& operator=(const Activitate& a)
    {
        if (this != &a)
        {
            if (this->denumire != nullptr)
            {
                delete[]this->denumire;
            }
            if (this->denumireObiecte != nullptr)
            {
                delete[]this->denumireObiecte;
            }
            if (this->greutateObiecte != nullptr)
            {
                delete[]this->greutateObiecte;
            }
            //validare pt char*
            if (strlen(a.denumire) >= 3) {
                this->denumire = new char[strlen(a.denumire) + 1];
                strcpy(this->denumire, a.denumire);
            }
            else
            {
                this->denumire = new char[strlen("Necunoscut") + 1];
                strcpy(this->denumire, "Necunoscut");
            }
            //validare pt string
            if (a.locatie.size() >= 3) //locatie.length()>=3
            {
                this->locatie = a.locatie;
            }
            else
            {
                this->locatie = "Necunoscuta";
            }

            if (a.durata > 0)
            {
                this->durata = a.durata;
            }
            else
            {
                this->durata = 0;
            }

            if (a.nrObiecte > 0 && a.denumireObiecte != nullptr && a.greutateObiecte != nullptr)
            {
                this->nrObiecte = a.nrObiecte;
                this->denumireObiecte = new string[this->nrObiecte];
                for (int i = 0; i < this->nrObiecte; i++)
                {
                    this->denumireObiecte[i] = a.denumireObiecte[i];
                }


                this->greutateObiecte = new float[this->nrObiecte];
                for (int i = 0; i < this->nrObiecte; i++)
                {
                    this->greutateObiecte[i] = greutateObiecte[i];
                }
            }
            else
            {
                this->nrObiecte = 0;
                this->denumireObiecte = nullptr;
                this->greutateObiecte = nullptr;
            }

            this->gradDificultate = a.gradDificultate;
        }
        return *this;
    }

    //destructor
    ~Activitate()
    {
        if (this->denumire != nullptr)
        {
            delete[]this->denumire;
        }
        if (this->denumireObiecte != nullptr)
        {
            delete[]this->denumireObiecte;
        }
        if (this->greutateObiecte != nullptr)
        {
            delete[]this->greutateObiecte;
        }
    }


};
//cum initializam un static
int Activitate:: numarator = 1;

int main()
{

    Activitate a;
    cout << a.getIdActivitate() << endl;

    string denumiri[] = { "bara","gantere" };
    float greutate[] = { 20,17.5 };
    Activitate a1("Sala", "Acasa", 30, 2, denumiri, greutate, Usoara);

    cout <<  "-----------------Getteri---------------------------------"<<endl<<endl;

    cout << "Denumire: " << a1.getDenumire() << endl;
    cout <<"Nr obiecte: " << a1.getNrObiecte() << endl;
    for (int i = 0; i < a1.getNrObiecte(); i++)
    {
        cout << a1.getDenumireObiecte()[i] << ", ";
    }
    cout << endl;
    cout << "Greutate Obiecte: ";// << *a1.getGreutateObiecte() << endl;
    for (int i = 0; i < a1.getNrObiecte(); i++)
    {
        cout << a1.getGreutateObiecte()[i] << ", ";
    }
    cout << "Id Activitate: " << a1.getIdActivitate() << endl;
    cout << "Locatie: " << a1.getLocatie() << endl;

}

