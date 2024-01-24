//SUBIECT
//carti de vizita
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string>
#include<fstream>
using namespace std;


class CarteDeVizita {
private:
    static int idUrmator;
    const int id;
    char* numePersoana;
    string numarTelefon;
    string adresaEmail;
    string numeCompanie;

public:

    CarteDeVizita() : id(idUrmator++)
    {
        this->numePersoana = new char[strlen("necunoscut")+1];
        strcpy(this->numePersoana, "necunoscut");
        this->numarTelefon = "0798654321";
        this->adresaEmail = "anonima@gmail.com";
        this->numeCompanie = "Companie anonima";
       
    }

    CarteDeVizita(const char* numePersoana, string numarTelefon, string adresaEmail, string numeCompanie)
        : id(idUrmator++){
        this->numePersoana = new char[strlen(numePersoana) + 1];
        strcpy(this->numePersoana, numePersoana);
        this->numarTelefon = numarTelefon;
        this->adresaEmail = adresaEmail;
        this->numeCompanie = numeCompanie;
    }

    CarteDeVizita(const CarteDeVizita& cdv)
        : id(idUrmator++), numePersoana(new char[strlen(cdv.numePersoana) + 1]),
        numarTelefon(cdv.numarTelefon), adresaEmail(cdv.adresaEmail), numeCompanie(cdv.numeCompanie) {
        strcpy(numePersoana, cdv.numePersoana);
    }

    CarteDeVizita& operator=(const CarteDeVizita& cdv) {
        if (this != &cdv) {
            delete[] numePersoana;
            numePersoana = new char[strlen(cdv.numePersoana) + 1];
            strcpy(numePersoana, cdv.numePersoana);

            numarTelefon = cdv.numarTelefon;
            adresaEmail = cdv.adresaEmail;
            numeCompanie = cdv.numeCompanie;
        }
        return *this;
    }

    ~CarteDeVizita() {
        delete[] numePersoana;
    }

    friend ostream& operator<<(ostream& os, const CarteDeVizita& cdv) {
        os << "ID: " << cdv.id << endl;
        os << "Nume: " << cdv.numePersoana <<endl;
        os << "Telefon: " << cdv.numarTelefon << endl;
        os << "Email: " << cdv.adresaEmail << endl;
        os << "Companie: "<< cdv.numeCompanie<<endl;
        return os;
    }

    friend istream& operator>>(istream& in, CarteDeVizita& cdv) {
        string nume;
        cout << "Nume persoana: ";
        /*in >> nume;*/
        if (cdv.numePersoana != nullptr) {
            delete[] cdv.numePersoana;

        }
       // cdv.numePersoana = new char[nume.length() + 1];
        char aux[100];
        in >> ws;
        in.getline(aux, 99);
        cdv.numePersoana = new char[strlen(aux)+1];
        strcpy(cdv.numePersoana, aux);
        cout << "Numar telefon: ";
        in >> cdv.numarTelefon;
        cout << "Adresa email: ";
        in >> cdv.adresaEmail;
        cout << "Nume companie: ";
        in >> cdv.numeCompanie;

        return in;
    }

    bool operator==(const CarteDeVizita& cdv) const {
        return strcmp(numePersoana, cdv.numePersoana) == 0;
    }
};

int CarteDeVizita::idUrmator = 0;

class CarteDeVizitaElectronica : public CarteDeVizita {
private:
    string urlProfil;

public:
    CarteDeVizitaElectronica(const char* nume, string telefon, string email, string companie, string url)
        : CarteDeVizita(nume, telefon, email, companie)
    {
        this->urlProfil = url;
    }

    virtual void DeschideProfil() {
        cout << "Deschidere profil pentru " << urlProfil << endl;
    }
};

int main() {
    // Create an instance of CarteDeVizita using the parameterized constructor
    CarteDeVizita cdv1("Ionut", "0722123456", "ion.popescu@example.com", "Exemplu SRL");
    cout << "Carte de vizita 1:" << endl;
    cout << cdv1 << endl << endl;


    // Create an instance of CarteDeVizitaElectronica
    CarteDeVizitaElectronica cdve1("Ionuta", "0722999888", "maria.ionescu@example.com", "Exemplu SRL", "http://mariaionescu.com");
    cout << "Carte de vizita electronica:" << endl;
    cout << cdve1 << endl;
    cdve1.DeschideProfil(); // Demonstrate the virtual function
    cout << endl;

    // Read information for a new CarteDeVizita from the console
    CarteDeVizita cdv2;
    cout << "Introduceti informatiile pentru a doua carte de vizita:" << endl;
    cin >> cdv2;

    // Display the entered information
    cout << "Carte de vizita 2:" << endl;
    cout << cdv2 << endl;

    // Compare two CarteDeVizita instances
    if (cdv1 == cdv2) {
        cout << "Cartile de vizita sunt identice." << endl;
    }
    else {
        cout << "Cartile de vizita sunt diferite." << endl;
    }

    return 0;
}
