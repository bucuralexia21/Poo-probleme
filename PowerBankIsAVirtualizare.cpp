// PowerBankExamen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//SUBIECT
//(3p) Se consideră o aplicate pentru gestionarea activității unei magazin care vinde baterii externe de
//tipul powerBank.Se vor urmări atribute specifice, precum: capacitate greutate număr intrări / ieșiri,
//culoare etc.Datele membre sunt private si sunt puse la dispoziție metode de acces.Clasa conține cel
//puțin patru câmpuri dintre care unul este alocat dinamic, constructori, metodele specifice claselor cu
//membri alocați dinamic și operatorul de afișare.Folosiți un membru static sau const
//(1p) Se vor defini operator+= si operator-= care permit incarcarea powerbank - ului respectiv descarcarea
//acestuia
//(1p) Definiti operator== care compară doua obiecte de tip PowerBlank si returneaza true dacă toate
//valorile atributelor corespunzatoare sunt egale intre ele.
//(2p) Exemplificati conceptul de relatie de tip „is a” prin specializarea clasei PowerBank.Testați soluția
//prin instanțierea noii clase.
//(2p) Explicati conceptele de early binding si late binding.
//(1p) Exemplificați conceptul de functie template in C++

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string>
#include<fstream>
using namespace std;


class PowerBank {
	int capacitate;
	float greutate;
	char* culoare;
	static int nrIntrari;

public:
	int getCapacitate() {
		return this->capacitate;
	}

	float getGreutate() {
		return this->greutate;

	}

	char* getCuloare()
	{
		return this->culoare;
	}


	void setCapacitate(int capacitate) {
		this->capacitate = capacitate;
	}

	void setGreutate(float greutate) {
		this->greutate = greutate;
	}

	void setCuloare(char* culoare) {
		this->culoare = new char[strlen(culoare) + 1];
		strcpy(this->culoare, culoare);
	}

	//constructor implicit
	PowerBank()
	{
		this->capacitate = 0;
		this->greutate = 0;
		this->culoare = new char[strlen("necunoscuta") + 1];
		strcpy(this->culoare, "necunoscuta");


	}

	//constructor cu toti parametrii
	PowerBank(int capacitate, float greutate, const char* culoare)
	{
		this->capacitate = capacitate;
		this->greutate = greutate;
		this->culoare = new char[strlen(culoare) + 1];
		strcpy(this->culoare, culoare);

	}

	//constructor de copiere
	PowerBank(const PowerBank& p) {
		this->capacitate = p.capacitate;
		this->greutate = p.greutate;
		this->culoare = new char[strlen(p.culoare) + 1];
		strcpy(this->culoare, p.culoare);
	}

	~PowerBank()
	{
		if (this->culoare != nullptr)
		{
			delete[]this->culoare;
		}
	}

	//afisare
	friend ostream& operator<<(ostream& out, const PowerBank& p) {
		out << "Capacitate: " << p.capacitate << endl;
		out << "Greutate: " << p.greutate << endl;
		out << "Culoare: " << p.culoare << endl;
		return out;
	}

	friend ofstream& operator<<(ofstream& out, const PowerBank& p) {
		out << p.capacitate << endl;
		out << p.greutate << endl;
		out << p.culoare << endl;
		return out;
	}

	friend istream& operator>>(istream& in, PowerBank& p) {
		cout << "Introduceti capacitate: ";
		in >> p.capacitate;
		cout << "Introduceti Greutate: ";
		in >> p.greutate;
		cout << "Culoare: ";
		in >> p.culoare;
		return in;
	}

	PowerBank& operator+=(int valoare) {
		this->capacitate += valoare;
		return *this;
	}


	PowerBank& operator-=(int valoare) {
		this->capacitate -= valoare;
		return *this;
	}


	bool operator==(const PowerBank& p) {
		if (this->capacitate == p.capacitate && this->greutate == p.greutate
			&& strcmp(this->culoare, p.culoare) == 0)
			return true;
		else return false;

	}

	PowerBank& operator*=(int valoare) {
		this->capacitate *= valoare;
		return*this;
	}

	bool operator<(const PowerBank& other) const {
		return this->capacitate < other.capacitate;
	}




	virtual void Descriere()
	{
		cout << "PoerBankDescriere" << endl;
	}
};
int PowerBank::nrIntrari = 3;


class SunPoweredPowerBank : public PowerBank {
	int KwSoare;

public:
	SunPoweredPowerBank() :PowerBank()
	{
		this->KwSoare = 0;
	}

	SunPoweredPowerBank(int capacitate, float greutate, const char* culoare, int KwSoare)
		:PowerBank(capacitate, greutate, culoare)
	{
		this->KwSoare = KwSoare;
	}

	SunPoweredPowerBank(const SunPoweredPowerBank& p) :PowerBank(p)
	{
		this->KwSoare = p.KwSoare;
	}

	friend ostream& operator<<(ostream& out, const SunPoweredPowerBank& p) {
		out << (PowerBank&)p;
		out << "kWSoare: " << p.KwSoare;
		return out;
	}


	friend istream& operator>>(istream& in, SunPoweredPowerBank& p) {
		in >> (PowerBank&)p;
		cout << "Introduceti kWSoare: ";
		in >> p.KwSoare;
		return in;
	}

	void Descriere()
	{
		cout << "SunPowerBankDescriere" << endl;
	}

};
int main()
{
	PowerBank p1;
	cout << p1 << endl;

	PowerBank p2(80, 20.5, "rosu");

	PowerBank p3(160, 21.5, "galben");

	PowerBank p4(60, 21.5, "verde");

	cout << p2 << endl;

	p2 += 20;
	cout << p2.getCapacitate() << endl;

	p2 -= 10;
	cout << p2.getCapacitate() << endl;


	cout << "-------*=------------------" << endl;
	cout << "P2 are capacitatea " << p2.getCapacitate() << endl;
	p2 *= 10;
	cout << p2.getCapacitate() << endl;

	if (p2 == p3) {
		cout << "Sunt egale" << endl;
	}
	else
	{
		cout << "Nu sunt egale" << endl;
	}


	//copie
	PowerBank pc = p2;
	if (pc == p2) {
		cout << "Sunt egale" << endl;
	}
	else
	{
		cout << "Nu sunt egale" << endl;
	}

	cout << "--------Op<---------------" << endl;

	PowerBank p5(5000, 250, "Red");
	PowerBank p6(10000, 300, "Blue");



	if (p5 < p6) {
		cout << "p5<p6";

	}
	else
	{
		cout<<"p5>p6";
	}

	//ofstream
	ofstream fout("PowerBank.txt", ios::out);
	fout << p2;
	fout.close();



	SunPoweredPowerBank sp;
	cout << sp;
	cin >> sp;


	//late binding
	PowerBank* powerBank = &sp;

	powerBank->Descriere();



}


