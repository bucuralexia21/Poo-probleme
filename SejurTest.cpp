// Model test 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;


class Sejur {
private:

    const int id;
	char destinatie[100];
	float pretBaza;
	int nrExcursiiOptionale;
	float* pretExcursie=nullptr;
	string denumireSejur;
	string data;

public:
	Sejur(int  id):id(id)
	{
		//this->id = id;
		//destinatie[0] = '\0';

	}

	Sejur(int id,const char* destinatie,float pretBaza,int nrExcursiiOptionale,float* pretExcursie,string DenumireSejur,string data) :id(id)
	{
		//this->destinatie = destinatie;
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAMETRII";
		
		// Copie destinatia in membrul destinatie
		strcpy(this->destinatie, destinatie);

	
		this->pretBaza = pretBaza;
	
		if (nrExcursiiOptionale > 0 && pretExcursie != nullptr)
		{
			int ctExcursie = 0;
			for (int i = 0; i < nrExcursiiOptionale; i++)
				if (pretExcursie[i] > 0)
					ctExcursie++;

			this->nrExcursiiOptionale = ctExcursie;
			this->pretExcursie = new float[this->nrExcursiiOptionale];

			int k=0;
			for (int i = 0; i < nrExcursiiOptionale; i++)
				if (pretExcursie[i] > 0)
					this->pretExcursie[k++] = pretExcursie[i];
		}

		this->denumireSejur = denumireSejur;
		this->data = data;
		

		
	}

	

	//void setDestinatie(const char* destinatieNoua) {
	//	if (strlen(destinatieNoua) >= 5)
	//		strcpy(destinatie, destinatieNoua);
	//}

	/*char* getDestinatie() {
		return destinatie;
	}*/

	/*Firma(int CUI) :CUI(CUI) {
		//this->CUI = CUI;
	}*/


	void afisare() {
		cout << "\n---------------AFISARE----------------";
		cout <<"\nID "<< this->id;
	 	cout << "\nDestinatie  " << destinatie;
		cout << "\nPret Baza " << pretBaza;
		cout << "\nNr Excursii optionale " << this->nrExcursiiOptionale;
		cout << "\npPret Excursie ";
		if (this->pretExcursie != nullptr) 
		{
			for (int i = 0; i < nrExcursiiOptionale; i++)
			{
				cout << this->pretExcursie[i] << " ";
			}
		                  }
		else {
			cout << "-";
		    }
		}

	~Sejur() {
		cout << "\nApel destructor";
		delete[] this->pretExcursie;
		this->pretExcursie = nullptr;
	}


};



int main()
{
	Sejur s1(123);
	float pretExcursie[] = { 1300,2000,900 };
	
	s1.afisare();
	Sejur s2(2222, "Malta", 100.0f, 2, pretExcursie, "SejurTropical", "2023-12-01");
	s2.afisare();

	return 0;
}

