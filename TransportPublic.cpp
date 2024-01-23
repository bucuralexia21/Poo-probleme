#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include< string>
#include<fstream>
using namespace std;

class Vehicul {
	const int id;
	static int numarator;
	int nrLocuri;
	char* motorizare;
	float valoare;

public:
	const int getId()
	{
		return this->id;

	}
	int getNrLocuri()
	{
		return this->nrLocuri;

	}
	char* getMotorizare()
	{
		return this->motorizare;
	}
	float getValoare()
	{
		return this->valoare;
	}
	void setNrLocuri(int nrLocuri)
	{
		this->nrLocuri = nrLocuri;
	}
	void setMotorizare(char* motorizare)
	{
		this->motorizare = new char[strlen(motorizare) + 1];
		strcpy(this->motorizare, motorizare);
	}
	void setValoare(float valoare)
	{
		this->valoare = valoare;
	}


	Vehicul() :id(numarator++)
	{
		this->nrLocuri = 0;
		this->motorizare = new char[strlen("necunoscuta") + 1];
		strcpy(this->motorizare, "necunoscuta");
		this->valoare = 0;
	}


	Vehicul(int nrLocuri, const char* motorizare, float valoare) :id(numarator++)
	{
		this->nrLocuri = nrLocuri;
		this->motorizare = new char[strlen(motorizare) + 1];
		strcpy(this->motorizare, motorizare);
		this->valoare = valoare;
	}

	~Vehicul()
	{
		if (this->motorizare != nullptr)
		{
			delete[]this->motorizare;
		}
	}

	//constructor copiere
	Vehicul(const Vehicul& v) :id(v.numarator++)
	{
		this->nrLocuri = v.nrLocuri;
		this->motorizare = new char[strlen(v.motorizare) + 1];
		strcpy(this->motorizare, v.motorizare);
		this->valoare = v.valoare;
	}


	//op=
	Vehicul& operator=(const Vehicul& v) {
		if (this != &v) {
			if (this->motorizare != nullptr)
			{
				delete[]this->motorizare;
			}
			this->nrLocuri = v.nrLocuri;
			this->motorizare = new char[strlen(v.motorizare) + 1];
			strcpy(this->motorizare, v.motorizare);
			this->valoare = v.valoare;

		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Vehicul& v)
	{
		out << "ID: " << v.id << endl;
		out << "Numar locuri: " << v.nrLocuri << endl;
		out << "Motorizare: " << v.motorizare << endl;
		out << "Valoare: " << v.valoare << endl;
		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Vehicul& v)
	{
		out << v.id << endl;
		out << v.nrLocuri << endl;
		out << v.motorizare << endl;
		out << v.valoare << endl;
		return out;
	}


	bool operator==(const Vehicul& a) {
		if (strcmp(this->motorizare, a.motorizare) == 0 && this->nrLocuri == a.nrLocuri && this->valoare == a.valoare)
			return true;
		else
			return false;
	}

};

class Autobuz :public Vehicul {
	float capacitate;

public:
	Autobuz() :Vehicul() {
		this->capacitate = 0;
	}

	Autobuz(int nrLocuri, const char* motorizare, float valoare, float capacitate) :Vehicul(nrLocuri, motorizare, valoare)
	{
		this->capacitate = capacitate;
	}

	friend ostream& operator<<(ostream& out, const Autobuz& a)
	{
		out << (Vehicul&)a;
		out << "Capacitate autobuz: " << a.capacitate << endl;
		return out;
	}

};


class Tramvai :public Vehicul {
	int nrVagoane;

};

class Troleibuz :public Vehicul {
	int putere;
};
int Vehicul::numarator = 0;



int main()
{
	Vehicul v1;
	cout << v1 << endl;

	Vehicul v2(8, "gas", 200);
	cout << v2 << endl;

	Vehicul v3(v2);
	cout << v3 << endl;

	if (v1 == v2)
	{
		cout << "Vehiculele sunt identice"<<endl;
	}
	else
	{
		cout << "Vehiculele nu sunt identice"<<endl;
	}

	v3 = v1;
	

	if (v1 == v3)
	{
		cout << "Vehiculele sunt identice"<<endl;
	}
	else
	{
		cout << "Vehiculele nu sunt identice"<<endl;
	}


	cout << "---------------------------------------------"<<endl;
	cout << v3<<endl;


	fstream fout("Vehciul.txt", ios::out);
	fout <<  v3<<endl;
	fout.close();

	Autobuz a1;
	cout << a1;

	

}