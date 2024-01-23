// Marker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//// SUBIECT 
//(2p) Se considera o aplicație pentru gestiunea unei colecţii de markere folosite pentru scrierea pe o
//tablă dintr - o sală.Se vor urmäri aspectele comune privind culoare, dimensiune, producator, etc.Pentru
//datele membre private sunt puse la dispoziție metode de acces.Clasa conține cel puțin patru câmpuri,
//dintre care unul este alocat dinamic, constructori, metodele specifice claselor cu membri alocaţi
//dinamic.Folosiți un membru static sau const.
//(1p) Supraîncărcați operator<< pentru afișarea unui marker.
//(2p) Specializați clasa care descrie un marker electronic având noi câmpuri precum baterie, rază
//acţiune, etc.
//(1p) Oferiți posibilitatea de comparare a două markere prin operator==, compararea realizându - se
//pentru minim două atribute.
//SUBIECT
//(3p) Se consideră o aplicatie pentru gestionarea activităţii unui furnizor de energie electrică alternativă.
//Se vor urmări atribute specifice.precum: nume / denumire client, sursă energie, consum lunar efeleiv,
//consum lunar estimat, numar contract durată contract, pret kWh etc.Datele membre sunt private şi
//sunt puse la dispoziţie metode de acces.Clasa contine cel putin patru cămpuri, dintre care unul este
//alocat dinamic.constructori, metodele specifice claselor cu membri alocați dinamic şi operatorul de
//afișare.Pentru sursele de energie utilizaţi constante enumerative(enum).Folositi un membru static sau
//const.
//(1p) Se va defini operatorul funcție() pentru a modifica valoarea consumului lunar efectiv dintr - o
//anumită lună din contract.
//(1p) Definiti operatorul de conversie la double, care va returna valoarea totala a diferentelor lunare de
//consum.
//(2p) Scrieti două metode : o metodă pentru determinarea lunii cu cea mai mică diferență de consum şi o
//metodă care calculează valoarea totală a consumului efectiv.
//(2p) Exemplificati conceptul de virtualizare prin utilizarea unei clase abstracte.
//(1p) Propuneţi un container STL care permite efectuarea rapidă a operaţiilor de regăsire după numărul
//contractului.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string>
#include<fstream>
using namespace std;

class Contract {
	int nrContract;
	char* client;
	float consumLunarEfectiv;
	float consumLunarEstimat;
	static int pretKw;
public:
	int getNrConstract()
	{
		return this->nrContract;
	}

	char* getClient() {
		return this->client;
	}

	float getConsumLunarEfectiv()
	{
		return this->consumLunarEfectiv;
	}
	float getConsumLunarEstimat()
	{
		return this -> consumLunarEstimat;
	}

	void setNrConstract(int nrContract)
	{
		this->nrContract = nrContract;
	}

	void setClient(char* client)
	{
		this->client = new char[strlen(client) + 1];
		strcpy(this->client, client);
	}

	void setConsumLunarEfectiv(float consumLunarEfectiv)
	{
		this->consumLunarEfectiv = consumLunarEfectiv;
	}

	void setConsumLunarEstimat(float consumLunarEstimat) {
		this->consumLunarEstimat = consumLunarEstimat;
	}

	Contract()
	{
		this->nrContract = 0;
		this->client = new char[strlen("Anonim") + 1];
		strcpy(this->client, "Anonim");
		this->consumLunarEfectiv = 0;
		this->consumLunarEstimat = 0;
	}

	Contract(int nrContract, const char* client, float consumLunarEfectiv, float consumLunarEstimat)
	{
		this->nrContract = nrContract;
		this->client = new char[strlen(client) + 1];
		strcpy_s(this->client, strlen(client) + 1, client);
		this->consumLunarEfectiv = consumLunarEfectiv;
		this->consumLunarEstimat = consumLunarEstimat;
	}

	~Contract()
	{
		if (this->client != nullptr)
		{
			delete[]this->client;
		}
	}

	friend ostream& operator<<(ostream& out, const Contract& c)
	{
		out << "Numar contract: " << c.nrContract << endl;
		out << "Client: " << c.client << endl;
		out << "Consum lunar efectiv: " << c.consumLunarEfectiv << endl;
		out << "Consum lunar estimat: " << c.consumLunarEstimat << endl;
		return out;

	}

	float operator()(float consumNou) {
		this->consumLunarEfectiv = this->consumLunarEfectiv + consumNou;
		return this->consumLunarEfectiv;
	}

	double conversie()
	{
		float diferenta = 0;
		diferenta = this->consumLunarEfectiv - this->consumLunarEstimat;
		return (double)diferenta;
	}

};
 int Contract::pretKw=2;



int main()
{
	Contract c1;
	cout << c1 << endl;

	Contract c2(1, "ION", 20, 30);
	cout << c2 << endl;

	cout << c1(30) << endl;
	cout << c2.conversie();
}

