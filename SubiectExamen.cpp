
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string>
#include<fstream>
using namespace std;

class SubiectExamen {
    const int id;
    static int punctajMinim;
    string titlu;
    string barem;
    int nrCerinte;
    string* cerinte;

public:

    string getTitlu()
    {
        return this->titlu;
    }

    string getBarem()
    {
        return this->barem;
    }

    void setTitlu(string titlu)
    {
        this->titlu = titlu;
    }

    void setCerinte(int nrCerinte, string* cerinte)
    {
        if (this->cerinte != nullptr)
        {
            delete[]this->cerinte;
        }
        this->nrCerinte = nrCerinte;
        this->cerinte = new string[this->nrCerinte];
        for (int i = 0; i < nrCerinte; i++)
        {
            this->cerinte[i] = cerinte[i];
        }
    }

    SubiectExamen():id(0) {
        this->titlu = "Subiect necunoscut";
        this->barem = "barem necunoscut";
        this->nrCerinte = 0;
        this->cerinte =nullptr;
    }

    //constructor cu toti parameetrii
    SubiectExamen(string titlu,string barem,int nrCerinte,string* cerinte) :id(id) {
        this->titlu = titlu;
        this->barem = barem;
        this->nrCerinte = nrCerinte;
        this->cerinte = new string[this->nrCerinte];
        for (int i = 0; i < this->nrCerinte; i++)
        {
            this->cerinte[i] = cerinte[i];
        }
    }


    //constructor de copiere
    SubiectExamen(const SubiectExamen& s):id(s.id)
    {
        this->titlu = s.titlu;
        this->barem = s.barem;
        this->nrCerinte = s.nrCerinte;
        this->cerinte = new string[this->nrCerinte];
        for (int i = 0; i < this->nrCerinte; i++)
        {
            this->cerinte[i] = s.cerinte[i];
        }
    }

    //op=
    SubiectExamen& operator=(const SubiectExamen& s)
    {
        if (this != &s)
        {
            if (this->cerinte != nullptr)
            {
                delete[]this->cerinte;
            }
            this->titlu = s.titlu;
            this->barem = s.barem;
            this->nrCerinte = s.nrCerinte;
            this->cerinte = new string[this->nrCerinte];
            for (int i = 0; i < this->nrCerinte; i++)
            {
                this->cerinte[i] = s.cerinte[i];
            }
        }
        return *this;
    }

    ~SubiectExamen()
    {
        if (this->cerinte != nullptr)
        {
            delete[]this->cerinte;
        }
    }

    friend ostream& operator<<(ostream& out, const SubiectExamen& s)
    {
        out << s.id << endl;
        out << s.titlu << endl;
        out << s.barem << endl;
        out << s.nrCerinte << endl;
        for (int i = 0; i < s.nrCerinte; i++)
        {
            out << s.cerinte[i] << ", " ;
        }
        out << endl;

        return out;
    }

    friend ofstream& operator<<(ofstream& out, const SubiectExamen& s)
    {
        out << s.id << endl;
        out << s.titlu << endl;
        out << s.barem << endl;
        out << s.nrCerinte << endl;
        for (int i = 0; i < s.nrCerinte; i++)
        {
            out << s.cerinte[i] << ", ";
        }
        out << endl;

        return out;
    }
};
int SubiectExamen::punctajMinim = 1;


class Evaluator {
    string prenume;
    string nume;
    int nrSubiecteExamene;
    SubiectExamen* subiecteExamene[5] = {};

public:

    string getPrenume()
    {
        return this->prenume;
    }
    Evaluator()
    {
        this->nume = "nume Anonim";
        this->prenume = "prenume Anonim";
    }

    Evaluator(string prenume, string nume, int nrSubiecteExamene, SubiectExamen* subiecteExamene[5])
    {
        this->prenume= prenume;
        this->nume = nume;
        this->nrSubiecteExamene = nrSubiecteExamene;
        for (int i = 0; i < this->nrSubiecteExamene; i++)
        {
            this->subiecteExamene[i] = new SubiectExamen(*subiecteExamene[i]);
        }
    }

    Evaluator(const Evaluator& e)
    {
        this->prenume = e.prenume;
        this->nume = e.nume;
        this->nrSubiecteExamene = e.nrSubiecteExamene;
        for (int i = 0; i < this->nrSubiecteExamene; i++)
        {
            this->subiecteExamene[i] = new SubiectExamen(*e.subiecteExamene[i]);
        }
    }
};


int main()
{
    SubiectExamen s1;

    cout << s1 << endl;

    string cerinte[] = { "cerinta1","cerinta2" };
    SubiectExamen s2("Subiect 2","barem2",2,cerinte);

    cout << s2 << endl;

    SubiectExamen s3(s2);
    cout << s3<<endl;

    SubiectExamen s4;
    s4 = s1;

    cout << s4 << endl;

    SubiectExamen s5("Subiect 5", "barem 5", 2, cerinte);
    cout<<s5.getTitlu()<<endl<<endl;
    string cerinte1[] = { "cerinta 3","cerinta 4" };
    s5.setCerinte(2, cerinte1);


    cout << s5<<endl;

    ofstream fSubiectExamen("subiecteExamen.txt", ios::out);
    if (fSubiectExamen.is_open()) {
        fSubiectExamen << s1;
        fSubiectExamen << s2;
        // ... scrie alte obiecte SubiectExamen, dacã este necesar ...
    }
    else {
        cout << "Nu s-a putut deschide fisierul pentru scriere." << endl;
    }
    fSubiectExamen.close();


    SubiectExamen* subiecteExamene[2] = { &s1,&s2 };
    Evaluator ev1("Ion", "Popescu", 2, subiecteExamene);
    cout << ev1.getPrenume() << endl;


}

