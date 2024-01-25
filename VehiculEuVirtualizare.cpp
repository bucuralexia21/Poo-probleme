// Vehicul.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include <iostream>
using namespace std;


class Vehicul {
protected:
	const int id;
	static int nextId;
	string tipVehicul;
	string firma;
	int numarLocuri;


public:
	Vehicul() :id(0) {
		this->tipVehicul = "Mare";
		this->firma = "Mercedes";
		this->numarLocuri = 5;
	}

	Vehicul(string tipVehicul,string firma,int numarLocuri):id(nextId++) {
		this->tipVehicul = tipVehicul;
		this->firma = firma;
		this->numarLocuri = numarLocuri;
	}

	Vehicul(const Vehicul& v) :id(v.nextId++) {
		this->tipVehicul = v.tipVehicul;
		this->firma = v.firma;
		this->numarLocuri = v.numarLocuri;
	}

	//op=
	Vehicul& operator=(const Vehicul& v)
	{
		if (this != &v)
		{
			this->tipVehicul = v.tipVehicul;
			this->firma = v.firma;
			this->numarLocuri = v.numarLocuri;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Vehicul& v)
	{
		out << "Tip vehicul: " << v.tipVehicul << endl;
		out << "Firma vehicul: " << v.firma << endl;
		out << "Numar locuri: " << v.numarLocuri << endl;

		return out;
	}

	virtual void getAmortizare()
	{
		cout << "Amortizare pentru vehicul: "<<endl;
	}

};
int Vehicul::nextId = 0;

class Autobuz : public Vehicul
{
	float capacitate;

public:
	Autobuz() :Vehicul()
	{
		this->capacitate = 0;
	}

	Autobuz(string tipVehicul, string firma, int numarLocuri,float capacitate) :Vehicul(tipVehicul,firma,numarLocuri)
	{
		this->capacitate = capacitate;
	}

	friend ostream& operator<<(ostream& out, const Autobuz& a) {
		out << (Vehicul&)a;
		out << "Capacitate autobuz: " << a.capacitate << endl;
		return out;
	}


	void getAmortizare()
	{
		cout << "Pentru autobuz amortizarea este 10%"<<endl;
	}
};


class Tramvai :public Vehicul {

	int numarVagoane;

public:
	Tramvai() :Vehicul() {
		this->numarVagoane = 0;
	}

	Tramvai(string tipVehicul, string firma, int numarLocuri,int numarVagoane) :Vehicul(tipVehicul,firma,numarLocuri) {
		this->numarVagoane = numarVagoane;
	}

	friend ostream& operator<<(ostream& out, const Tramvai& t)
	{
		out << (Vehicul&)t;
		out << "Numar vagoane: " << t.numarVagoane;
		return out;
	}


	void getAmortizare()
	{
		cout << "Pentru tramvai amortizarea este 12%"<<endl;
	}

};

class Troleibuz :public Vehicul {
	string putere;
public:
	Troleibuz() :Vehicul()
	{
		this->putere = "500 Kw";
	}

	Troleibuz(string tipVehicul, string firma, int numarLocuri,string putere) :Vehicul(tipVehicul, firma, numarLocuri)
	{
		this->putere = putere;
	}

	friend ostream& operator<<(ostream& out, const Troleibuz& tro) {
		out << (Vehicul&)tro;
		out << "Putere troleibuz: " << tro.putere<<endl;
		return out;
	}


	void getAmortizare()
	{
		cout << "Pentru troleibuz amortizarea este 8%"<<endl;
	}

};

int main()
{
	Vehicul v1("Mic", "BMW", 5);
	cout << v1 << endl;

	Vehicul v2(v1);
	cout << v2 << endl;

	Vehicul v3("Mare", "BMW", 8);
	cout << v3 << endl;
	v3 = v2;
	cout << v3 << endl;

	Autobuz a1;
	Autobuz a2("Mare", "Mercedes", 50, 80);

	cout << a1 << endl;
	cout << a2<<endl;


	cout << "Tramvai 1: " << endl << endl;
	Tramvai t1;
	cout << t1 << endl << endl;

	cout << "Tramvai 2: " << endl << endl;
	Tramvai t2("Mare", "BMW", 100, 4);
	cout << t2 << endl<<endl;


	cout << "Troleibuz 1: " << endl;
	Troleibuz tro1;

	Troleibuz tro2("Mare","Merca",90,"900Kw");

	cout << tro1 << endl;
	cout << "Troleibuz 2: " << endl;
	cout << tro2 << endl;


	v1.getAmortizare();

	a1.getAmortizare();
	t1.getAmortizare();
	tro1.getAmortizare();

	cout << "Virtualizare cu pointeri: " << endl;
	Vehicul* vehicul1 = &a1;
	Vehicul* vehicul2 = &t1;

	vehicul1->getAmortizare();
	vehicul2->getAmortizare();

}

