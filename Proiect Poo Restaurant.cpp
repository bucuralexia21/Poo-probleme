// Proiect POO Faza 1 Bucur Alexia-Gabriela.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>
//#include <curses.h>
//#include <conio.h>
#include <stdlib.h>
using namespace std;

class FisiereBinare
{
public:
	virtual void writeToFile(fstream& f) = 0;
	virtual void readFromFile(fstream& f) = 0;
};

class Persoana {
public:
	virtual void statut() {
		cout << "\nAceasta persoana este angajata, face parte din clientela lantului de restaurante sau nu a frecventat niciodata restaurantul.";
	}
	virtual void rol() {
		cout << "\nAceasta persoana plaseaza comenzi, indeplineste taskuri sau nu contribuie cu nimic in cadrul lantului de restaurante";
	}
};

class Comanda : public FisiereBinare
{
private:
	const int idComanda;
	int nrPreparate = 0;
	int* preparate = NULL;
	int cantitatiPreparate[100] = {};
	string detaliiComanda = "Neprecizat";


public:
	void writeToFile(fstream& f)
	{
		f.write((char*)&this->idComanda, sizeof(int));

		int lg = this->detaliiComanda.length() + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->detaliiComanda.data(), lg);

		f.write((char*)&this->nrPreparate, sizeof(int));

		for (int i = 0; i < this->nrPreparate; i++)
		{
			f.write((char*)&this->cantitatiPreparate[i], sizeof(int));
			f.write((char*)&this->preparate[i], sizeof(int));
		}
	}
	void readFromFile(fstream& f)
	{
		delete[] this->preparate;

		int lg;
		f.read((char*)&lg, sizeof(int));
		char* buffer2 = new char[lg];
		f.read(buffer2, lg);
		this->detaliiComanda = buffer2;
		delete[] buffer2;

		f.read((char*)&this->idComanda, sizeof(int));
		f.read((char*)&this->nrPreparate, sizeof(int));
		this->preparate = new int[this->nrPreparate];
		for (int i = 0; i < this->nrPreparate; i++)
		{
			f.read((char*)&this->cantitatiPreparate[i], sizeof(int));
			f.read((char*)&this->preparate[i], sizeof(int));
		}
	}


	Comanda(int idComanda) :idComanda(idComanda) {
		//cout << "\nApel constructor cu un parametru";
	}

	Comanda(int idComanda, string detaliiComanda, int nrPreparate, int* preparate, int cantitatiPreparate[]) :idComanda(idComanda) {
		//cout << "\nApel constructor cu toti parametrii";
		this->detaliiComanda = detaliiComanda;
		if (nrPreparate > 0 && preparate != NULL) {
			this->nrPreparate = nrPreparate;
			this->preparate = new int[this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++)
			{
				this->preparate[i] = preparate[i];
			}

			for (int i = 0; i < this->nrPreparate; i++)
			{
				this->cantitatiPreparate[i] = cantitatiPreparate[i];
			}
		}
		else
			throw new exception("preparate null");
	}

	Comanda(const Comanda& c) :idComanda(c.idComanda) {
		//cout << "\nApel constructor copiere";
		this->detaliiComanda = detaliiComanda;
		this->nrPreparate = c.nrPreparate;
		if (nrPreparate > 0 && c.preparate != NULL) {
			this->nrPreparate = c.nrPreparate;
			this->preparate = new int[this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++)

				this->preparate[i] = c.preparate[i];
			for (int i = 0; i < this->nrPreparate; i++)
				this->cantitatiPreparate[i] = c.cantitatiPreparate[i];

		}
	}



	Comanda& operator=(const Comanda& c) {
		if (this != &c) {
			delete[] this->preparate;
			this->detaliiComanda = c.detaliiComanda;
			if (nrPreparate > 0 && c.preparate != NULL)
			{
				this->nrPreparate = c.nrPreparate;
				this->preparate = new int[this->nrPreparate];
				for (int i = 0; i < this->nrPreparate; i++)
					this->preparate[i] = c.preparate[i];
				for (int i = 0; i < this->nrPreparate; i++)
					this->cantitatiPreparate[i] = cantitatiPreparate[i];

			}
		}
		else {
			this->nrPreparate = 0;
			this->preparate = NULL;
		}
		return *this;
	}

	~Comanda() {
		//cout << "\nApel destructor";

		// Verifică dacă pointerul este NULL înainte de a-r șterge

		delete[] this->preparate;

	}

	const int getIdComanda()
	{
		return this->idComanda;
	}

	string getReview()
	{
		return this->detaliiComanda;
	}


	void setReview(string detaliiComanda) {
		if (detaliiComanda.size() > 5)
			this->detaliiComanda = detaliiComanda;
		else
			throw new exception("Review incomplet");

	}
	int getNrPreparate()
	{
		return this->nrPreparate;
	}

	void setNrPreparate(int nrPreparate)
	{
		if (nrPreparate > 0)
		{
			this->nrPreparate = nrPreparate;
		}
		else
			throw new exception("comanda trebuie sa contina minim un preparat");
	}

	void getPreparate()
	{
		for (int i = 0; i < this->nrPreparate; i++)
		{
			cout << this->preparate[i] << "; ";

		}
	}

	void setPreparate(const int* preparate)
	{
		delete[] this->preparate;
		this->preparate = new int[this->nrPreparate];
		for (int i = 0; i < this->nrPreparate; i++) {
			if (preparate[i] >= 0)
				this->preparate[i] = preparate[i];
			else
				throw new exception("codul preparatelor nu poate fi un numar negativ");
		}

	}

	void getCantitatiPreparate()
	{
		for (int i = 0; i < this->nrPreparate; i++)
		{
			cout << this->cantitatiPreparate[i] << "; ";
		}
	}

	void setCantitatiPreparate(int cantitatiPreparate[]) {
		for (int i = 0; i < this->nrPreparate; i++) {
			if (cantitatiPreparate[i] > 0)
				this->cantitatiPreparate[i] = cantitatiPreparate[i];
			else
				throw new exception("cantitatea minima admisa pentru o comanda este de un preparat");
		}
	}

	int getNrTotalPreparateComanda()
	{
		int nrTotalPreparate = 0;
		for (int i = 0; i < this->nrPreparate; i++)
			nrTotalPreparate = nrTotalPreparate + cantitatiPreparate[i];
		return nrTotalPreparate;

	}

	int getCantitateMaximaComanda()
	{
		int max = 0;
		for (int i = 0; i < this->nrPreparate; i++)
			if (this->cantitatiPreparate[i] > max)
				max = this->cantitatiPreparate[i];
		return max;
	}



	friend ostream& operator<<(ostream& out, const Comanda& c) {
		out << "\n-------------------------";
		out << "\nId Comanda: " << c.idComanda;
		out << "\nNr preparate: " << c.nrPreparate;
		//out << "\nPreparate ";
		if (c.preparate != nullptr) {
			out << "\nLista coduri preparate comandate: ";
			for (int i = 0; i < c.nrPreparate; i++)
				out << c.preparate[i] << "; ";
			out << "\nLista cantitati preparate comandate: ";
			for (int i = 0; i < c.nrPreparate; i++)
				out << c.cantitatiPreparate[i] << " ";
		}
		out << "\n-------------------------";
		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Comanda& c)
	{
		out << c.idComanda << endl;
		out << c.detaliiComanda << endl;
		out << c.nrPreparate << endl;
		if (c.preparate != NULL) {
			for (int i = 0; i < c.nrPreparate; i++)
				out << c.preparate[i] << endl;
			for (int i = 0; i < c.nrPreparate; i++)
				out << c.cantitatiPreparate[i] << endl;
		}
		return out;
	}

	friend istream& operator>>(istream& in, Comanda& c)
	{
		delete[] c.preparate;

		cout << "\nIntroduceti detalii pentru comanda";
		in >> c.detaliiComanda;

		cout << "\nIntroduceti numarul de preparate: ";
		in >> c.nrPreparate;
		if (c.nrPreparate < 0)
		{
			c.nrPreparate = 0;
			c.preparate = 0;
		}
		else
		{
			c.preparate = new int[c.nrPreparate];
			cout << "\nIntroduceti codurile preparatelor: ";
			for (int i = 0; i < c.nrPreparate; i++)
			{
				cout << "p[" << i + 1 << "]=";
				in >> c.preparate[i];
			}

			cout << "\nIntroduceti cantitatile preparatelor:";
			for (int i = 0; i < c.nrPreparate; i++)
			{
				cout << "c[" << i + 1 << "]=";
				in >> c.cantitatiPreparate[i];
			}
		}
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Comanda& c)
	{
		delete[] c.preparate;

		in >> c.detaliiComanda;
		in >> c.nrPreparate;
		if (c.nrPreparate < 0)
		{
			c.nrPreparate = 0;
			c.preparate = 0;
		}
		else
		{
			c.preparate = new int[c.nrPreparate];
			for (int i = 0; i < c.nrPreparate; i++)
			{
				in >> c.preparate[i];
			}
			for (int i = 0; i < c.nrPreparate; i++)
			{
				in >> c.cantitatiPreparate[i];
			}
		}
		return in;
	}

	int operator[](int index)
	{
		if (index >= 0 && index < this->nrPreparate)
			return this->cantitatiPreparate[index];
		else
			throw new exception("valoarea indexului nu corespunde");
	}

	Comanda& operator++()
	{
		for (int i = 0; i < this->nrPreparate; i++)
			this->cantitatiPreparate[i]++;
		return *this;
	}


	Comanda operator++(int)
	{
		Comanda rez = *this;
		for (int i = 0; i < this->nrPreparate; i++)
			this->cantitatiPreparate[i]++;
		return rez;
	}

	Comanda& operator--()
	{
		for (int i = 0; i < this->nrPreparate; i++)
			if (cantitatiPreparate[i] > 1)
				this->cantitatiPreparate[i]--;
			else
			{
				for (int j = i; i < this->nrPreparate - 1; i++)
					this->cantitatiPreparate[j] = this->cantitatiPreparate[j + 1];
				this->nrPreparate--;

			}
		return *this;
	}


	Comanda operator--(int)
	{
		Comanda rez = *this;
		for (int i = 0; i < this->nrPreparate; i++) {
			if (cantitatiPreparate[i] > 0)
				this->cantitatiPreparate[i]--;
			else
			{
				for (int j = i; i < this->nrPreparate - 1; i++)
					this->cantitatiPreparate[j] = this->cantitatiPreparate[j + 1];
				this->nrPreparate--;
			}
		}
		return rez;
	}

	bool operator!()
	{
		if (this->nrPreparate >= 10)
			return true;
		return false;

	}

	Comanda operator +=(int datePreparat[2]) //prima pozitite din vector va retine codul produsului,iar a doua va retine cantitatea
	{
		Comanda copie = *this;
		this->nrPreparate++;
		delete[] this->preparate;
		this->preparate = new int[this->nrPreparate];
		for (int i = 0; i < copie.nrPreparate; i++) {
			this->preparate[i] = copie.preparate[i];
			this->cantitatiPreparate[i] = copie.cantitatiPreparate[i];
		}
		this->preparate[this->nrPreparate - 1] = datePreparat[0];
		this->cantitatiPreparate[this->nrPreparate - 1] = datePreparat[1];
		return *this;

	}

	Comanda operator+(int datePreparat[2])
	{
		Comanda rez = *this;
		rez += datePreparat;
		return rez;
	}

	bool operator>=(Comanda c)
	{
		if (this->nrPreparate != c.nrPreparate) return false;
		else if (this->nrPreparate != 0) {
			for (int i = 0; i < this->nrPreparate; i++)
				if (this->preparate[i] != c.preparate[i] || this->cantitatiPreparate[i] != c.cantitatiPreparate[i])
					return false;

		}
		return true;
	}

	bool operator==(Comanda c)
	{
		if (this->detaliiComanda != c.detaliiComanda) return false;
		if (this->nrPreparate != c.nrPreparate) return false;
		else
			if (this->nrPreparate != c.nrPreparate) {
				for (int i = 0; i < this->nrPreparate; i++)
					if (this->preparate[i] != c.preparate[i] || this->cantitatiPreparate[i] != c.cantitatiPreparate[i])
						return false;
			}
		return true;
	}

	explicit operator string()
	{
		return this->detaliiComanda;
	}

};







class Client : public FisiereBinare, public Persoana {
private:
	string nume = "Anonim";
	string prenume = "Anonim";
	char* nrTelefon;
	int nrComenzi = 0;
	Comanda* comenzi[5] = {};

public:
	void rol() {
		cout << "\nAceasta persoana a plasat un numar de " << this->nrComenzi << " comenzi";
	}
	void statut() {
		cout << "\nAceasta persoana face parte din clientela lantului de restaurante";
	}
	void writeToFile(fstream& f)
	{
		int lg = this->nume.length() + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->nume.data(), lg);

		int lg2 = this->prenume.length() + 1;
		f.write((char*)&lg2, sizeof(int));
		f.write(this->prenume.data(), lg2);

		int lg3 = strlen(this->nrTelefon) + 1;
		f.write((char*)&lg3, sizeof(int));
		f.write(this->nrTelefon, lg3);

		f.write((char*)&this->nrComenzi, sizeof(int));

		for (int i = 0; i < this->nrComenzi; i++)
		{
			comenzi[i]->writeToFile(f);
		}
	}
	void readFromFile(fstream& f)
	{
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		f.read(buffer, lg);
		this->nume = buffer;
		delete[] buffer;

		int lg2;
		f.read((char*)&lg2, sizeof(int));
		char* buffer2 = new char[lg2];
		f.read(buffer2, lg2);
		this->prenume = buffer2;
		delete[] buffer2;

		delete[] this->nrTelefon;
		int lg3;
		f.read((char*)&lg3, sizeof(int));
		char* buffer3 = new char[lg];
		f.read(buffer3, lg);
		this->nrTelefon = buffer3;
		delete[] buffer3;

		f.read((char*)&this->nrComenzi, sizeof(int));
		for (int i = 0; i < this->nrComenzi; i++)
		{
			delete[] comenzi[i];
			comenzi[i] = new Comanda(i);
			comenzi[i]->readFromFile(f);
		}
	}
	Client()
	{
		//cout << "\nApel constructor fara parametri";
		this->nrTelefon = new char[strlen("07xxxxxxxx") + 1];
		strcpy(this->nrTelefon, "07xxxxxxxx");

	}

	Client(string nume, string prenume, const char* nrTelefon, int nrComenzi, Comanda* comenzi[5])
	{
		//cout << "\nApel constructor cu toti parametrii";
		this->nume = nume;
		this->prenume = prenume;
		this->nrTelefon = new char[strlen(nrTelefon) + 1];
		strcpy(this->nrTelefon, nrTelefon);
		this->nrComenzi = nrComenzi;
		for (int i = 0; i < this->nrComenzi; i++)
		{
			this->comenzi[i] = new Comanda(*comenzi[i]);
		}
	}

	Client(const Client& cl)
	{
		//cout << "\nApel constructor de copiere";
		this->nume = cl.nume;
		this->prenume = cl.prenume;
		this->nrTelefon = new char[strlen(cl.nrTelefon) + 1];
		strcpy(this->nrTelefon, cl.nrTelefon);
		this->nrComenzi = cl.nrComenzi;
		for (int i = 0; i < this->nrComenzi; i++)
			this->comenzi[i] = new Comanda(*cl.comenzi[i]);
	}

	Client& operator=(const Client& cl) {
		if (this != &cl) {
			for (int i = 0; i < this->nrComenzi; i++) {
				delete this->comenzi[i];
			}
			delete[] this->nrTelefon;
			this->nume = cl.nume;
			this->prenume = cl.prenume;
			this->nrTelefon = new char[strlen(cl.nrTelefon) + 1];
			strcpy(this->nrTelefon, cl.nrTelefon);
			this->nrComenzi = cl.nrComenzi;
			for (int i = 0; i < this->nrComenzi; i++)
				this->comenzi[i] = new Comanda(*cl.comenzi[i]);
		}
		return*this;
	}
	~Client()
	{
		//cout << "\nApel destructor";
		delete[] this->nrTelefon;
		for (int i = 0; i < this->nrComenzi; i++)
			delete this->comenzi[i];
	}

	string getNume() {
		return this->nume;
	}
	void setNume(string nume) {
		if (nume.size() > 3)
			this->nume = nume;
		else
			throw new exception("dimensiune sir gresita - prea mica");
	}
	string getPrenume() {
		return this->prenume;
	}
	void setPrenume(string prenume) {
		if (prenume.size() > 2)
			this->prenume = prenume;
		else
			throw new exception("dimensiune sir gresita - prea mica");
	}
	void getNrTelefon() {
		for (int i = 0; i < strlen(this->nrTelefon) + 1; i++)
			cout << nrTelefon[i];
	}
	void setNrTelefon(const char* nrTelefon) {
		if (strlen(nrTelefon) == 10) {
			delete[] this->nrTelefon;
			this->nrTelefon = new char[strlen(nrTelefon) + 1];
			strcpy(this->nrTelefon, nrTelefon);
		}
		else
			throw new exception("numarul de telefon trebuie sa contina 10 cifre");
	}
	int getNrComenzi() {
		return this->nrComenzi;
	}
	void setNrComenzi(int nrComenzi) {
		if (nrComenzi > 0)
			this->nrComenzi = nrComenzi;
		else
			throw new exception("clientul trebuie sa inregistreze minim o comanda");
	}
	void getComenzi(int target = 0) {
		if (target == 0 || target == 2) {
			for (int i = 0; i < this->nrComenzi; i++)
				cout << *comenzi[i];
		}
		if (target == 1 || target == 2) {
			for (int i = 0; i < this->nrComenzi; i++) {
				ofstream gr3("listaComenzi.txt");
				gr3 << *comenzi[i];
				gr3.close();
			}
		}
	}
	void setComenzi(Comanda* comenzi[]) {
		for (int i = 0; i < this->nrComenzi; i++)
			delete this->comenzi[i];
		for (int i = 0; i < this->nrComenzi; i++) {
			if (comenzi[i]->getNrPreparate() != 0) {
				this->comenzi[i] = new Comanda(*comenzi[i]);
			}
			else
				throw new exception("comanda cu care se face inlocuirea trebuie sa contina minim un produs");
		}
	}
	string getFixSauMobil() {
		string fix = "fix";
		string mobil = "mobil";
		string invalid = "invalid";
		if (nrTelefon[1] == '2') return fix;
		else if (nrTelefon[1] == '7') return mobil;
		else return invalid;
	}

	int getNrTotalPreparateComandate()
	{
		int nr = 0;
		for (int i = 0; i < this->nrComenzi; i++)
			nr = nr + this->comenzi[i]->getNrTotalPreparateComanda();
		return nr;
	}




	friend ostream& operator<<(ostream& out, const Client& cl)
	{
		out << "\n--------------------";
		out << "\nNume:" << cl.nume;
		out << "\nPrenume:" << cl.prenume;
		out << "\nNr telefon:" << cl.nrTelefon;
		out << "\nNr comenzi:" << cl.nrComenzi;
		for (int i = 0; i < cl.nrComenzi; i++)
		{
			if (cl.comenzi[i] != NULL) {
				out << "\nComanda " << i << ": ";
				out << *cl.comenzi[i];
			}
		}
		out << "\n--------------------";
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const Client& cl)
	{
		out << cl.nume << endl;
		out << cl.prenume << endl;
		out << cl.nrTelefon << endl;
		out << cl.nrComenzi << endl;
		for (int i = 0; i < cl.nrComenzi; i++)
		{
			if (cl.comenzi[i] != NULL) {
				out << *cl.comenzi[i];
			}
		}
		return out;
	}
	friend istream& operator>>(istream& in, Client& cl)
	{
		delete[] cl.nrTelefon;
		for (int i = 0; i < cl.nrComenzi; i++)
			delete cl.comenzi[i];

		cout << "\nIntroduceti nume client: ";
		in >> cl.prenume;
		cout << "\nPrenume:";
		in >> cl.prenume;
		char aux[100];
		cout << "\nIntroduceti numarul de telefon (fix sau mobil de Romania): ";
		in >> aux;
		cl.nrTelefon = new char[strlen(aux) + 1];
		strcpy(cl.nrTelefon, aux);
		cout << "\nNr comenzi:";
		in >> cl.nrComenzi;
		if (cl.nrComenzi < 0)
		{
			cl.nrComenzi = 0;
		}
		else
		{
			int id = 200;
			for (int i = 0; i < cl.nrComenzi; i++)
				cl.comenzi[i] = new Comanda(id++);
			cout << "\nIntroduceti fiecare comanda:";
			for (int i = 0; i < cl.nrComenzi; i++) {
				cout << "comanda[" << i + 1 << "]=";
				in >> *(cl.comenzi[i]);
			}
		}
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Client& cl)
	{
		delete[] cl.nrTelefon;
		for (int i = 0; i < cl.nrComenzi; i++)
			delete cl.comenzi[i];

		in >> cl.nume;
		in >> cl.prenume;
		char aux[100];
		in >> aux;
		cl.nrTelefon = new char[strlen(aux) + 1];
		strcpy(cl.nrTelefon, aux);
		in >> cl.nrComenzi;
		if (cl.nrComenzi < 0)
		{
			cl.nrComenzi = 0;
		}
		else
		{
			int id = 200;
			for (int i = 0; i < cl.nrComenzi; i++)
				cl.comenzi[i] = new Comanda(id++);
			for (int i = 0; i < cl.nrComenzi; i++) {
				in >> *(cl.comenzi[i]);
			}
		}
		return in;
	}
	Comanda operator[] (int index)
	{
		if (index >= 0 && index < this->nrComenzi)
			return *this->comenzi[index];
		else
			throw new exception("valoarea index-ului nu corespunde");
	}

	Client& operator++()
	{
		for (int i = 0; i < this->nrComenzi; i++)
			this->comenzi[i]++;
		return *this;
	}

	Client operator++(int)
	{
		Client rez = *this;
		for (int i = 0; i < this->nrComenzi; i++)
			this->comenzi[i]++;
		return rez;
	}

	Client& operator--()
	{
		for (int i = 0; i < this->nrComenzi; i++)
			if (this->comenzi[i]->getNrPreparate() > 0)
				this->comenzi[i]--;
		return *this;
	}


	Client operator--(int)
	{
		Client rez = *this;
		for (int i = 0; i < this->nrComenzi; i++)
			if (this->comenzi[i]->getNrPreparate() > 0)
				this->comenzi[i]--;
		return rez;
	}


	bool operator!()
	{
		if (this->nume.size() == this->prenume.size())
			return true;
		return false;


	}

	Client operator+=(Comanda* comanda)
	{
		Client copie = *this;
		for (int i = 0; i < copie.nrComenzi; i++)
			delete this->comenzi[i];
		this->nrComenzi++;
		for (int i = 0; i < copie.nrComenzi; i++)
			this->comenzi[i] = new Comanda(*copie.comenzi[i]);
		this->comenzi[this->nrComenzi - 1] = new Comanda(*comanda);
		return *this;
	}

	Client operator+ (Comanda* comanda)
	{
		Client rez = *this;
		rez += comanda;
		return rez;
	}

	bool operator>=(Client cl)
	{
		int nrPreparateThis = 0;
		int nrPreparateCl = 0;
		for (int i = 0; i < this->nrComenzi; i++)
			nrPreparateThis = nrPreparateThis + this->comenzi[i]->getNrPreparate();
		for (int i = 00; i < cl.nrComenzi; i++)
			nrPreparateCl = nrPreparateCl + cl.comenzi[i]->getNrPreparate();
		return nrPreparateThis >= nrPreparateCl;
	}

	bool operator==(Client cl)
	{
		if (this->nume != cl.nume) return false;
		if (this->prenume != cl.prenume) return false;
		if (strcmp(this->nrTelefon, cl.nrTelefon) != 0) return false;
		if (this->nrComenzi != cl.nrComenzi) return false;
		else if (this->nrComenzi != 0) {
			for (int i = 0; i < this->nrComenzi; i++)
				if ((this->comenzi[i] == cl.comenzi[i]) == 0) return false;
		}
		return true;
	}

	explicit operator int()
	{
		return this->nrComenzi;
	}


	


};

class ClientVIP :public Client {
private:
	int nrProduse = 0;
	list<string> produse; //list de stringuri cu denumirile produselor de pe wishlist
	int nrReduceri = 0;
	vector<int> reduceri; //vector cu reduceri ptr client
public:
	ClientVIP() :Client() {
		//cout<<"\nApel constructor fara parametri";
	}
	ClientVIP(string nume, string prenume, const char* nrTelefon, int nrComenzi, Comanda* comenzi[5], int nrProduse, string produse[], int nrReduceri, int reduceri[]) :Client(nume, prenume, nrTelefon, nrComenzi, comenzi) {
		//cout<<\nApel constructor cu toti parametrii";
		this->nrProduse = nrProduse;
		for (int i = 0; i < this->nrProduse; i++)
			this->produse.push_back(produse[i]);
		this->nrReduceri = nrReduceri;
		for (int i = 0; i < this->nrReduceri; i++)
			this->reduceri.push_back(reduceri[i]);
	}
	ClientVIP(Client cl, int nrProduse, string produse[], int nrReduceri, int reduceri[]) : Client(cl) {
		//cout<<\nApel constructor cu toti parametrii";
		this->nrProduse = nrProduse;
		for (int i = 0; i < this->nrProduse; i++)
			this->produse.push_back(produse[i]);
		this->nrReduceri = nrReduceri;
		for (int i = 0; i < this->nrReduceri; i++)
			this->reduceri.push_back(reduceri[i]);
	}
	friend ostream& operator<<(ostream& out, const ClientVIP& clv) {
		out << (Client)clv;
		out << "\nNumar produse pe wishlist: " << clv.nrProduse;
		out << "\nProduse: ";
		list<string>::const_iterator it3;
		for (it3 = clv.produse.begin(); it3 != clv.produse.end(); it3++)
			out << *it3 << " ";
		out << "\nNumar reduceri: " << clv.nrReduceri;
		out << "\nReduceri: ";
		vector<int>::const_iterator it4;
		for (it4 = clv.reduceri.begin(); it4 != clv.reduceri.end(); it4++)
			cout << *it4 << " ";
		return out;
	}
	~ClientVIP() {
		//cout<<"\nApel destructor";
	}
};

class Preparat:public FisiereBinare
{
	const int codPreparat;
	string denumire = "Necunoscut";
	int nrIngrediente = 0;
	int stoc[10] = {};
	float* pret = NULL;

public:
	void writeToFile(fstream& f)
	{
		f.write((char*)&this->codPreparat, sizeof(int));

		int lg = this->denumire.length() + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->denumire.data(), lg);

		f.write((char*)&this->nrIngrediente, sizeof(int));

		for (int i = 0; i < this->nrIngrediente; i++)
		{
			f.write((char*)&this->stoc[i], sizeof(int));
		}

		f.write((char*)&this->pret, sizeof(float));
	}
	void readFromFile(fstream& f)
	{
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		f.read(buffer, lg);
		this->denumire = buffer;
		delete[] buffer;

		f.read((char*)&this->codPreparat, sizeof(int));
		f.read((char*)&this->nrIngrediente, sizeof(int));
		for (int i = 0; i < this->nrIngrediente; i++)
		{
			f.read((char*)&this->stoc[i], sizeof(int));
		}

		delete this->pret;
		this->pret = new float;
		f.read((char*)&this->pret, sizeof(float));
	}
	Preparat(int codPreparat) :codPreparat(codPreparat)
	{
		//cout<<"\nApel constructor cu un parametru"; 
		this->pret = new float;
		*this->pret = 0;
	}

	Preparat(int codPreparat, string denumire, int nrIngrediente, int stoc[], const float* pret) :codPreparat(codPreparat)
	{
		//cout << "\nApel constructor cu toti parametrii";
		this->denumire = denumire;
		this->pret = new float;
		*this->pret = *pret;
		this->nrIngrediente = nrIngrediente;
		for (int i = 0; i < this->nrIngrediente; i++)
			this->stoc[i] = stoc[i];
	}

	Preparat(const Preparat& p) :codPreparat(p.codPreparat)
	{
		//cout<<"\nApel constructor prin copiere";

		this->denumire = p.denumire;
		this->pret = new float;
		*this->pret = *p.pret;
		this->nrIngrediente = p.nrIngrediente;
		for (int i = 0; i < this->nrIngrediente; i++)
			this->stoc[i] = p.stoc[i];
	}

	Preparat& operator=(const Preparat& p)
	{
		if (this != &p) {
			delete this->pret;
			this->denumire = p.denumire;
			this->pret = new float;
			*this->pret = *p.pret;
			this->nrIngrediente = p.nrIngrediente;
			for (int i = 0; i < this->nrIngrediente; i++)
				this->stoc[i] = p.stoc[i];
		}
		return *this;
	}

	~Preparat()
	{
		//cout<<"\nApel destructor";
		delete this->pret;
	}

	const int getCodPreparat()
	{
		return this->codPreparat;
	}

	string getDenumire()
	{
		return this->denumire;
	}

	void setDenumire(string denumire)
	{
		if (denumire.size() > 2)
			this->denumire = denumire;
		else
			throw new exception("valoarea adaugata trebuie sa fie mai mare decat 0");

	}

	int getNrIngrediente()
	{
		return this->nrIngrediente;
	}

	void setNrIngrediente(int nrIngrediente)
	{
		if (nrIngrediente > 0)
			this->nrIngrediente = nrIngrediente;
		else
			throw new exception("Preparatul trebuie sa aiba cel putin un ingredient");
	}


	void getStocuri()
	{
		for (int i = 0; i < this->nrIngrediente; i++)
			cout << stoc[i] << "; ";

	}

	void setStocuri(int stoc[])
	{
		for (int i = 0; i < this->nrIngrediente; i++) {
			if (stoc[i] <= 100 && stoc[i] >= 0)
				this->stoc[i] = stoc[i];
			else
				throw new exception("valoarea adaugata pentru stoc nu se incadreaza in intervalul admis");
		}

	}


	int getStocTotal()
	{
		int stocTotal = 0;
		for (int i = 0; i < this->nrIngrediente; i++)
			stocTotal = stocTotal + stoc[i];
		return stocTotal;
	}

	float getPret()
	{
		return*(this->pret);
	}

	void setPret(const float* pret)
	{
		if (*pret > 0.99) {
			delete this->pret;
			this->pret = new float;
			*this->pret = *pret;
		}
		else
			throw new exception("valoarea adaugata pentru pret este prea mica");
	}

	void scumpirePreparat(const float* suma)
	{
		if (*suma > 0)
			*this->pret += *suma;
	}


	void ieftinirePreparat(const float* suma) {
		if (*suma > 0 && *suma <= 0.7 * (*this->pret))
			*this->pret -= *suma;
	}


	friend ostream& operator<<(ostream& out, const Preparat& p)
	{
		out << "\n---------------------------";
		out << "\nCod preparat: " << p.codPreparat;
		out << "\nDenumire: " << p.denumire;
		if (p.pret != NULL)
		{
			out << "\nPret:" << *p.pret;
		}
		else
		{
			out << "\nPret: indisponibil";

		}
		out << "\nNr ingrediente: " << p.nrIngrediente;
		out << "\nLista stocuri pentru fiecare ingredient: ";
		for (int i = 0; i < p.nrIngrediente; i++)
			out << p.stoc[i] << " ";
		out << "\n---------------------------";
		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Preparat& p)
	{
		out << p.codPreparat << endl;
		out << p.denumire << endl;
		if (p.pret != NULL)
		{
			out << *p.pret << endl;
		}
		out << p.nrIngrediente << endl;
		for (int i = 0; i < p.nrIngrediente; i++)
			out << p.stoc[i] << endl;
		return out;
	}

	friend istream& operator>>(istream& in, Preparat& p)
	{
		delete p.pret;
		cout << "\nIntroduceti denumirea preparatului: ";
		in >> p.denumire;
		cout << "\nPret: ";
		p.pret = new float;
		in >> *p.pret;
		cout << "\nNr ingrediente: ";
		in >> p.nrIngrediente;
		if (p.nrIngrediente < 0)
		{
			p.nrIngrediente = 0;
		}
		else
		{
			cout << "\nIntroduceti stocul disponibil pentru fiecare ingredient ";
			for (int i = 0; i < p.nrIngrediente; i++)
			{
				cout << "s[" << i + 1 << "]=";
				in >> p.stoc[i];
			}

		}
		return in;

	}
	friend ifstream& operator>>(ifstream& in, Preparat& p)
	{
		delete p.pret;

		in >> p.denumire;
		p.pret = new float;
		in >> *p.pret;
		in >> p.nrIngrediente;
		if (p.nrIngrediente < 0)
		{
			p.nrIngrediente = 0;
		}
		else
		{
			for (int i = 0; i < p.nrIngrediente; i++)
			{
				in >> p.stoc[i];
			}
		}
		return in;
	}


	int operator[](int index)
	{
		if (index >= 0 && index < this->nrIngrediente)
			return this->stoc[index];
		else
			throw new exception("valoarea indexului nu corespunde");
	}

	Preparat& operator++() //alimenteaza stocurile pentru ingrediente cu 100 de grame
	{
		for (int i = 0; i < nrIngrediente; i++)
			stoc[i] = stoc[i] + 100;
		return *this;
	}

	Preparat operator++(int)
	{
		Preparat rez = *this;
		for (int i = 0; i < nrIngrediente; i++)
			stoc[i] = stoc[i] + 100;
		return rez;
	}

	Preparat& operator--()  //Injumatateste stocurile pentru fiecare ingredient
	{
		for (int i = 0; i < nrIngrediente; i++)
			stoc[i] = stoc[i] / 2;
		return *this;
	}

	Preparat operator--(int)
	{
		Preparat rez = *this;
		for (int i = 0; i < nrIngrediente; i++)
			stoc[i] = stoc[i] / 2;
		return rez;
	}

	bool operator!()
	{
		if (*this->pret > 100)
			return true;
		return false;
	}


	Preparat operator+=(int stoc)
	{
		Preparat copie = *this;
		this->nrIngrediente++;
		for (int i = 0; i < copie.nrIngrediente; i++)
			this->stoc[i] = copie.stoc[i];
		this->stoc[this->nrIngrediente - 1] = stoc;
		return *this;
	}

	Preparat operator+(int stoc)
	{
		Preparat rez = *this;
		rez += stoc;
		return rez;
	}

	bool operator>=(Preparat p)
	{
		return *this->pret >= *p.pret;

	}


	bool operator==(Preparat p)
	{
		if (*this->pret != *p.pret) return false;
		if (this->denumire != p.denumire) return false;
		if (this->nrIngrediente != p.nrIngrediente) return false;
		else if (this->nrIngrediente != 0) {
			for (int i = 0; i < this->nrIngrediente; i++)
				if (this->stoc[i] != p.stoc[i]) return false;
		}
		return true;
	}


	explicit operator float()
	{
		return *this->pret;
	}
};





class Angajat :public FisiereBinare, public Persoana {
private:
	const int cod;
	char* nume;
	string prenume="Anonim";
	int vechime = 0;
	int nrTaskuri = 0;
	int durateTaskuri[5] = { 0,0,0,0,0 };

public:
	void rol() {
		cout << "\nAceasta persoana indeplineste un numar de " << this->nrTaskuri << " taskuri";
	}

	void statut() {
		cout << "\nAceasta persoana este angajata a lantului de restaurante";
	}
	void writeToFile(fstream& f)
	{
		f.write((char*)&this->cod, sizeof(int));
		int lg = strlen(this->nume) + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->nume, lg);

		int lg2 = this->prenume.length() + 1;
		f.write((char*)&lg2, sizeof(int));
		f.write(this->prenume.data(), lg2);

		f.write((char*)&this->vechime, sizeof(int));

		f.write((char*)&this->nrTaskuri, sizeof(int));

		for (int i = 0; i < this->nrTaskuri; i++)
		{
			f.write((char*)&this->durateTaskuri[i], sizeof(int));
		}
	}
	void readFromFile(fstream& f)
	{
		delete[] this->nume;
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		f.read(buffer, lg);
		this->nume = buffer;
		delete[] buffer;

		int lg2;
		f.read((char*)&lg2, sizeof(int));
		char* buffer2 = new char[lg2];
		f.read(buffer2, lg2);
		this->prenume = buffer2;
		delete[] buffer2;

		f.read((char*)&this->cod, sizeof(int));
		f.read((char*)&this->vechime, sizeof(int));
		f.read((char*)&this->nrTaskuri, sizeof(int));
		for (int i = 0; i < this->nrTaskuri; i++)
		{
			f.read((char*)&this->durateTaskuri[i], sizeof(int));
		}
	}
	Angajat(int cod) :cod(cod)
	{
		//cout << "\nApel constructor cu parametri: ";
		this->nume = new char[(strlen("Anonim") + 1)];
		strcpy(this->nume, "Anonim");
	}

	Angajat(int cod, const char* nume, string prenume, int vechime, int nrTaskuri, int durateTaskuri[]) :cod(cod)
	{
		//cout << "\nApel constructor cu toti parametrii";
		this->nume = new char[(strlen(nume) + 1)];
		strcpy(this->nume, nume);
		this->prenume = prenume;
		this->vechime = vechime;
		this->nrTaskuri = nrTaskuri;
		for (int i = 0; i < this->nrTaskuri; i++)
			this->durateTaskuri[i] = durateTaskuri[i];
	}

	Angajat(const Angajat& a) :cod(a.cod)
	{
		//cout << "\nApel constructor de copiere";
		this->nume = new char[(strlen(a.nume) + 1)];
		strcpy(this->nume, a.nume);
		this->prenume = a.prenume;
		this->vechime = a.vechime;
		this->nrTaskuri = a.nrTaskuri;
		for (int i = 0; i < this->nrTaskuri; i++)
			this->durateTaskuri[i] = a.durateTaskuri[i];
	}

	Angajat& operator=(const Angajat& a) {
		//cout << "\nApel Operator = ";
		if (this != &a) {
			delete[] this->nume;
			this->nume = new char[(strlen(a.nume) + 1)];
			strcpy(this->nume, a.nume);
			this->prenume = a.prenume;
			this->vechime = a.vechime;
			this->nrTaskuri = nrTaskuri;
			for (int i = 0; i < nrTaskuri; i++)
				this->durateTaskuri[i] = durateTaskuri[i];
		}
		return *this;
	}

	~Angajat() {
		//cout << "\nApel destructor";
		delete[] this->nume;
	}
	

	void getNume() {
		for (int i = 0; i < strlen(this->nume) + 1; i++)
			cout << nume[i];
	}

	void setNume(const char* nume) {
		if (strlen(nume) > 2) {
			delete[] this->nume;
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
	}
	const int getCod()
	{
		return this->cod;
	}


	string getPrenume()
	{
		return this->prenume;
	}

	void setPrenume(string prenume)
	{
		if (prenume.size() < 30)
			this->prenume = prenume;
		else
			throw new exception("Dimensiunea prenumelui este prea mare");

	}

	int getVechime()
	{
		return this->vechime;
	}

	void setVechime(int vechime)
	{
		if (vechime >= 0) {
			this->vechime = vechime;

		}
		else
			throw new exception("Vcehimea nu poate fi negativa");
	}

	int getNrTaskuri()
	{
		return this->nrTaskuri;
	}

	void setNrTaskuri()
	{
		if (nrTaskuri > 0) {
			this->nrTaskuri = nrTaskuri;
		}
		else
			throw new exception("valoarea adaugata trebuie sa fie mai mare decat 0");
	}

	void getDurateTaskuri() {
		for (int i = 0; i < nrTaskuri; i++)
			cout << durateTaskuri[i] << "; ";
	}

	void setDurateTaskuri() {
		for (int i = 0; i < this->nrTaskuri; i++)
			if (durateTaskuri[i] >= 0 && durateTaskuri[i] <= 9) {
				this->durateTaskuri[i] = durateTaskuri[i];
			}
			else
				throw new exception("Durata task-ului nu este corespunzatoare");
	}

	int getAnAngajare() {
		return (2023 - this->vechime);

	}

	int getOreLucruPeSaptamana() {
		int ore = 0;
		for (int i = 0; i < this->nrTaskuri; i++)
			ore = ore + durateTaskuri[i];
		return ore;
	}


	friend ostream& operator<<(ostream& out, const Angajat& a) {
		out << "\n-------------------------";
		out << "\nCod:" << a.cod;
		out << "\nNume angajat: " << a.nume;
		out << "\nPrenume angajat: " << a.prenume;
		out << "\nVechime angajat: " << a.vechime;
		out << "\nNr taskuri angajat: " << a.nrTaskuri;
		out << "\nDurate taskuri angajat: ";
		for (int i = 0; i < a.nrTaskuri; i++)
			out << a.durateTaskuri[i] << "; ";
		out << "\n-------------------------";
		return out;

	}

	friend ofstream& operator<<(ofstream& out, const Angajat& a)
	{
		out << a.cod << endl;
		out << a.nume << endl;
		out << a.prenume << endl;
		out << a.vechime << endl;
		out << a.nrTaskuri << endl;
		for (int i = 0; i < a.nrTaskuri; i++)
			out << a.durateTaskuri[i] << endl;
		return out;
	}
	int operator[](int index)
	{
		if (index >= 0 && index < this->nrTaskuri)
			return this->durateTaskuri[index];
		else
			throw new exception("Valoare index-ului este necorespunzatoare");

	}

	friend istream& operator>>(istream& in, Angajat& a)
	{
		delete[] a.nume;

		char aux[100];
		cout << "\nIntroduceti nume angajat: ";
		in >> aux;
		a.nume = new char[strlen(aux) + 1];
		strcpy(a.nume, aux);
		cout << "\nPrenume:";
		in >> a.prenume;
		cout << "\nNr taskuri: ";
		in >> a.nrTaskuri;
		if (a.nrTaskuri < 0)
		{
			a.nrTaskuri = 0;
		}
		else
		{
			cout << "\nIntroduceti duratele taskurilor: ";
			for (int i = 0; i < a.nrTaskuri; i++) {
				cout << "[d" << i + 1 << "]=";
				in >> a.durateTaskuri[i];
			}
		}
		cout << "\nIntroduceti vechimea: ";
		in >> a.vechime;
		return in;

	}
	friend ifstream& operator>>(ifstream& in, Angajat& a)
	{
		delete[] a.nume;

		char aux[100];
		in >> aux;
		a.nume = new char[strlen(aux) + 1];
		strcpy(a.nume, aux);
		in >> a.prenume;
		in >> a.nrTaskuri;
		if (a.nrTaskuri < 0)
		{
			a.nrTaskuri = 0;
		}
		else
		{
			for (int i = 0; i < a.nrTaskuri; i++)
			{
				in >> a.durateTaskuri[i];
			}
		}
		in >> a.vechime;
		return in;
	}


	//pre
	Angajat& operator++()
	{
		this->vechime++;
		return *this;
	}

	//post
	Angajat operator++(int)
	{
		Angajat rez = *this;
		this->vechime++;
		return rez;
	}

	//Operator --
	//pre
	Angajat& operator--()
	{
		this->vechime--;
		return *this;
	}

	//post
	Angajat operator--(int) //atentie aici nu trb prin referinta 
	{
		Angajat cop = *this;
		this->vechime--;
		return cop;
	}

	bool operator!()
	{
		if (this->vechime >= 2)
		{
			return true;
		}
		else
			return false;
	}

	Angajat operator+=(int durataTask)
	{
		Angajat copie = *this;
		this->nrTaskuri++;
		for (int i = 0; i < copie.nrTaskuri; i++)
			this->durateTaskuri[i] = copie.durateTaskuri[i];
		this->durateTaskuri[this->nrTaskuri - 1] = durataTask;
		return *this;


	}


	Angajat operator+(int durataTask)
	{
		Angajat rez = *this;
		rez += durataTask;
		return rez;
	}

	bool operator>=(Angajat a)
	{
		return this->vechime >= a.vechime;
	}

	bool operator==(Angajat a)
	{
		if (this->vechime != a.vechime) return false;
		if (strcmp(this->nume, a.nume) != 0) return false;
		if (this->prenume != a.prenume) return false;
		if (this->nrTaskuri != a.nrTaskuri)return false;
		else if (this->nrTaskuri != 0)
		{
			for (int i = 0; i < this->nrTaskuri; i++)
			{
				for (int i = 0; i < this->nrTaskuri; i++)
					if (this->durateTaskuri[i] != a.durateTaskuri[i]) return false;
			}
			return true;
		}

	}

	explicit operator int()
	{
		return this->vechime;
	}


};

class Manager :public Angajat {
private:
	int nrSubordonati = 0;
	set<int> subordonati; //set de int-uri cu codurile angajatilor subordonati
	int nrLocatii = 0;
	map<int, string> locatii; //map de stringuri cu adresele locatiilor pe care la manageriaza
public:
	Manager(int cod) :Angajat(cod) {
		//cout<<"\nApel constructor fara parametri";
	};
	Manager(int cod, const char* nume, string prenume, int vechime, int nrTaskuri, int durateTaskuri[], int nrSubordonati, int subordonati[], int nrLocatii, string adrese[]) :Angajat(cod, nume, prenume, vechime, nrTaskuri, durateTaskuri) {
		//cout<<"\nApel constructor cu toti parametrii";
		this->nrSubordonati = nrSubordonati;
		for (int i = 0; i < this->nrSubordonati; i++)
			this->subordonati.insert(subordonati[i]);
		this->nrLocatii = nrLocatii;
		for (int i = 0; i < this->nrLocatii; i++)
			this->locatii[i++] = adrese[i];
	}
	Manager(Angajat a, int nrSubordonati, int subordonati[], int nrLocatii, string adrese[]) : Angajat(a) {
		//cout<<"\nApel constructor cu toti parametrii";
		this->nrSubordonati = nrSubordonati;
		for (int i = 0; i < this->nrSubordonati; i++)
			this->subordonati.insert(subordonati[i]);
		this->nrLocatii = nrLocatii;
		for (int i = 0; i < this->nrLocatii; i++)
			this->locatii[i++] = adrese[i];
	}
	friend ostream& operator<<(ostream& out, const Manager& m) {
		out << (Angajat)m;
		out << "\nNumar subordonati: " << m.nrSubordonati;
		out << "\nSubordonati: ";
		set<int>::iterator it1;
		for (it1 = m.subordonati.begin(); it1 != m.subordonati.end(); it1++)
			out << *it1 << " ";
		out << "\nNumar locatii: " << m.nrLocatii;
		out << "\nAdrese: ";
		map<int, string>::const_iterator it2;
		for (it2 = m.locatii.begin(); it2 != m.locatii.end(); it2++)
			out << endl << it2->first << " " << it2->second;
		return out;
	}
	~Manager() {
		//cout<<"\nApel destructor";
	}
};

class Restaurant : public FisiereBinare {
private:
	static int taxaParcare;
	char* adresa = NULL;
	int nrPreparateInMeniu = 0;
	Preparat* preparateMeniu[40] = {};
	int nrAngajati = 0;
	Angajat* angajati[5] = {};

public:
	void writeToFile(fstream& f)
	{
		f.write((char*)&this->taxaParcare, sizeof(int));
		int lg = strlen(this->adresa) + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->adresa, lg);

		f.write((char*)&this->nrPreparateInMeniu, sizeof(int));

		for (int i = 0; i < this->nrPreparateInMeniu; i++)
		{
			preparateMeniu[i]->writeToFile(f);
		}

		f.write((char*)&this->nrAngajati, sizeof(int));

		for (int i = 0; i < this->nrAngajati; i++)
		{
			angajati[i]->writeToFile(f);
		}
	}
	void readFromFile(fstream& f)
	{
		delete[] this->adresa;
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		f.read(buffer, lg);
		this->adresa = buffer;
		delete[] buffer;

		f.read((char*)&this->taxaParcare, sizeof(int));
		f.read((char*)&this->nrPreparateInMeniu, sizeof(int));
		for (int i = 0; i < this->nrPreparateInMeniu; i++)
		{
			delete[] preparateMeniu[i];
			preparateMeniu[i] = new Preparat(i);
			preparateMeniu[i]->readFromFile(f);
		}

		f.read((char*)&this->nrAngajati, sizeof(int));
		for (int i = 0; i < this->nrAngajati; i++)
		{
			delete[] angajati[i];
			angajati[i] = new Angajat(i);
			angajati[i]->readFromFile(f);
		}
	}
	Restaurant()
	{
		//cout << "\nApel constructor fara parametri";
		this->adresa = new char[strlen("Necunoscuta") + 1];
		strcpy(this->adresa, "Necunoscuta");

	}

	Restaurant(const char* adresa, int nrPreparateInMeniu, Preparat* preparateMeniu[40], int nrAngajati, Angajat* angajati[5])
	{
		//cout << "\nApel constructor cu toti parametrii";
		this->adresa = new char[strlen(adresa) + 1];
		strcpy(this->adresa, adresa);
		this->nrPreparateInMeniu = nrPreparateInMeniu;
		for (int i = 0; i < this->nrPreparateInMeniu; i++)
			this->preparateMeniu[i] = new Preparat(*preparateMeniu[i]);
		this->nrAngajati = nrAngajati;
		for (int i = 0; i < this->nrAngajati; i++)
			this->angajati[i] = new Angajat(*angajati[i]);
	}

	Restaurant(const Restaurant& r) {
		//cout << "\nApel constructor prin copiere";
		this->adresa = new char[strlen(r.adresa) + 1];
		strcpy(this->adresa, r.adresa);
		this->nrPreparateInMeniu = r.nrPreparateInMeniu;
		for (int i = 0; i < this->nrPreparateInMeniu; i++)
			this->preparateMeniu[i] = new Preparat(*r.preparateMeniu[i]);
		this->nrAngajati = r.nrAngajati;
		for (int i = 0; i < this->nrAngajati; i++)
			this->angajati[i] = new Angajat(*r.angajati[i]);
	}

	Restaurant& operator=(const Restaurant& r)
	{
		if (this != &r) {
			delete[] this->adresa;
			for (int i = 0; i < this->nrPreparateInMeniu; i++) {
				delete this->preparateMeniu[i];
			}
			for (int i = 0; i < this->nrAngajati; i++)
			{
				delete this->angajati[i];
			}
			this->adresa = new char[strlen(r.adresa) + 1];
			strcpy(this->adresa, r.adresa);
			this->nrPreparateInMeniu = r.nrPreparateInMeniu;
			for (int i = 0; i < this->nrPreparateInMeniu; i++)
			{
				this->preparateMeniu[i] = new Preparat(*r.preparateMeniu[i]);
			}
			this->nrAngajati = r.nrAngajati;
			for (int i = 0; i < this->nrAngajati; i++)
				this->angajati[i] = new Angajat(*r.angajati[i]);
		}
		return *this;
	}

	~Restaurant()
	{
		delete[] this->adresa;
		for (int i = 0; i < nrPreparateInMeniu; i++)
			delete this->preparateMeniu[i];
		for (int i = 0; i < this->nrAngajati; i++)
			delete this->angajati[i];
	}

	static void setTaxaParcare(int taxaParcare) {
		if (taxaParcare > 0)
			Restaurant::taxaParcare = taxaParcare;
		else
			throw new exception("taxa de parcare trebuie sa reprezinte o suma nenula si pozitiva");
	}
	static int getTaxaParcare() {
		return Restaurant::taxaParcare;
	}
	void getAdresa() {
		for (int i = 0; i < strlen(this->adresa) + 1; i++)
			cout << this->adresa[i];
	}
	void setAdresa(const char* adresa) {
		if (strlen(adresa) > 3) {
			delete[] this->adresa;
			this->adresa = new char[strlen(adresa) + 1];
			strcpy(this->adresa, adresa);
		}
		else
			throw new exception("dimensiune sir gresita - adresa prea scurta");
	}

	int getNrPreparateInMeniu()
	{
		return this->nrPreparateInMeniu;
	}

	void setNrPreparate(int nrPreparate) {
		if (nrPreparate > 0)
			this->nrPreparateInMeniu = nrPreparate;
		else
			throw new exception("Restaurantul trebuie sa aiba in meniu minim un preparat");
	}

	void getProduse(int target = 0) {
		if (target == 0 || target == 2) {
			for (int i = 0; i < this->nrPreparateInMeniu; i++)
				cout << *preparateMeniu[i];
		}
		if (target == 1 || target == 2) {
			for (int i = 0; i < this->nrPreparateInMeniu; i++) {
				ofstream gr1("listaProd.txt");
				gr1 << *preparateMeniu[i];
				gr1.close();
			}
		}
	}

	void setPreparateMeniu(Preparat* preparateMeniu[]) {
		for (int i = 0; i < this->nrPreparateInMeniu; i++) {
			if (preparateMeniu[i]->getStocTotal() != 0)
				this->preparateMeniu[i] = new Preparat(*preparateMeniu[i]);
			else
				throw new exception("Restaurantul nu poate avea stocul gol");


		}
	}


	int getNrAngajati() {
		return this->nrAngajati;
	}

	void setNrAngajati(int nrAngajati)
	{
		if (nrAngajati > 0 && nrAngajati < 6)
			this->nrAngajati = nrAngajati;
		else
			throw new exception("La restaurant pot lucra minim un angajat si maxim 5 angajati");

	}

	void getAngajati(int target = 0) {
		if (target == 0 || target == 2) {
			for (int i = 0; i < this->nrAngajati; i++)
				cout << *angajati[i];
		}
		if (target == 1 || target == 2) {
			for (int i = 0; i < this->nrAngajati; i++)
			{
				ofstream gr2("listaAng.txt");
				gr2 << *angajati[i];
				gr2.close();
			}
		}
	}
	void setAngajati(Angajat* angajati[]) {
		for (int i = 0; i < this->nrAngajati; i++) {
			if (angajati[i]->getOreLucruPeSaptamana() > 10) {
				delete this->angajati[i];
				this->angajati[i] = new Angajat(*angajati[i]);
			}
			else
				throw new exception("persoana angajata nu atinge numarul minim impus de ore de lucru pe saptamana");
		}
	}

	int getVechimeaCeaMaiMare() {
		int max = 0;
		for (int i = 0; i < this->nrAngajati; i++)
			if (this->angajati[i]->getVechime() > max) max = this->angajati[i]->getVechime();
		return max;
	}
	float getCelMaiMarePret() {
		float max = 0;
		for (int i = 0; i < this->nrPreparateInMeniu; i++)
			if (this->preparateMeniu[i]->getPret() > max) max = this->preparateMeniu[i]->getPret();
		return max;
	}

	friend ostream& operator<<(ostream& out, const Restaurant& r)
	{
		out << "\n--------------------";
		out << "\nAdresa:" << r.adresa;
		out << "\nNr preparate:" << r.nrPreparateInMeniu;
		for (int i = 0; i < r.nrPreparateInMeniu; i++)
		{
			if (r.preparateMeniu[i] != NULL) {
				out << "\nProduse " << i << ": ";
				out << *r.preparateMeniu[i];
			}
		}
		out << "\nNr angajati:" << r.nrAngajati;
		for (int i = 0; i < r.nrAngajati; i++)
		{
			if (r.angajati[i] != NULL) {
				out << "\nAngajatul " << i << ": ";
				out << *r.angajati[i];
			}
		}
		out << "\n--------------------";
		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Restaurant& l)
	{
		out << l.adresa << endl;
		out << l.nrPreparateInMeniu << endl;
		for (int i = 0; i < l.nrPreparateInMeniu; i++)
		{
			if (l.preparateMeniu[i] != NULL) {
				out << *l.preparateMeniu[i];
			}
		}
		out << l.nrAngajati << endl;
		for (int i = 0; i < l.nrAngajati; i++)
		{
			if (l.angajati[i] != NULL) {
				out << *l.angajati[i];
			}
		}
		return out;
	}

	friend istream& operator>>(istream& in, Restaurant& r)
	{
		delete[] r.adresa;
		for (int i = 0; i < r.nrPreparateInMeniu; i++)
			delete r.preparateMeniu[i];
		for (int i = 0; i < r.nrAngajati; i++)
			delete r.angajati[i];

		char aux[100];
		cout << "\nIntroduceti adresa restaurantului (orasul): ";
		in >> aux;
		r.adresa = new char[strlen(aux) + 1];
		strcpy(r.adresa, aux);
		cout << "\nNr produse:";
		in >> r.nrPreparateInMeniu;
		if (r.nrPreparateInMeniu < 0)
		{
			r.nrPreparateInMeniu = 0;
		}
		else
		{
			int cod = 10;
			for (int i = 0; i < r.nrPreparateInMeniu; i++)
				r.preparateMeniu[i] = new Preparat(cod++);
			cout << "\nIntroduceti fiecare preparat:";
			for (int i = 0; i < r.nrPreparateInMeniu; i++) {
				cout << "preparat[" << i + 1 << "]=";
				in >> *(r.preparateMeniu[i]);
			}
		}
		cout << "\nNr angajati:";
		in >> r.nrAngajati;
		if (r.nrAngajati < 0)
		{
			r.nrAngajati = 0;
		}
		else
		{
			int cod = 1000;
			for (int i = 0; i < r.nrAngajati; i++)
				r.angajati[i] = new Angajat(cod++);
			cout << "\nIntroduceti fiecare angajat:";
			for (int i = 0; i < r.nrAngajati; i++) {
				cout << "angajat[" << i + 1 << "]=";
				in >> *(r.angajati[i]);
			}
		}
		return in;
	}

	friend ifstream& operator>>(ifstream& in, Restaurant& l)
	{
		delete[] l.adresa;
		for (int i = 0; i < l.nrPreparateInMeniu; i++)
			delete l.preparateMeniu[i];
		for (int i = 0; i < l.nrAngajati; i++)
			delete l.angajati[i];

		char aux[100];
		in >> aux;
		l.adresa = new char[strlen(aux) + 1];
		strcpy(l.adresa, aux);
		in >> l.nrPreparateInMeniu;
		if (l.nrPreparateInMeniu < 0)
		{
			l.nrPreparateInMeniu = 0;
		}
		else
		{
			int cod = 10;
			for (int i = 0; i < l.nrPreparateInMeniu; i++)
				l.preparateMeniu[i] = new Preparat(cod++);
			for (int i = 0; i < l.nrPreparateInMeniu; i++) {
				in >> *(l.preparateMeniu[i]);
			}
		}
		in >> l.nrAngajati;
		if (l.nrAngajati < 0)
		{
			l.nrAngajati = 0;
		}
		else
		{
			int cod = 1000;
			for (int i = 0; i < l.nrAngajati; i++)
				l.angajati[i] = new Angajat(cod++);
			for (int i = 0; i < l.nrAngajati; i++) {
				in >> *(l.angajati[i]);
			}
		}
		return in;
	}

	int operator[] (int index)
	{
		if (index >= 0 && index < this->nrAngajati)
			return this->angajati[index]->getOreLucruPeSaptamana();
		else
			throw new exception("valoarea indexului nu corespunde");
	}

	Restaurant& operator++()
	{
		for (int i = 0; i < this->nrPreparateInMeniu; i++)
			this->preparateMeniu[i]++;
		return *this;
	}

	Restaurant operator++ (int)
	{
		Restaurant rez = *this;
		for (int i = 0; i < this->nrPreparateInMeniu; i++)
			this->preparateMeniu[i]++;
		return rez;
	}

	Restaurant& operator-- ()
	{
		for (int i = 0; i < this->nrPreparateInMeniu; i++)
			this->preparateMeniu[i]--;
		return *this;
	}
	Restaurant operator-- (int)
	{
		Restaurant rez = *this;
		for (int i = 0; i < this->nrPreparateInMeniu; i++)
			this->preparateMeniu[i]--;
		return rez;
	}
	bool operator!()
	{
		if (this->nrAngajati == 5)
			return true;
		return false;
	}

	Restaurant operator+=(Preparat* preparat)
	{
		Restaurant copie = *this;
		this->nrPreparateInMeniu++;
		for (int i = 0; i < copie.nrPreparateInMeniu; i++)
			this->preparateMeniu[i] = new Preparat(*copie.preparateMeniu[i]);
		this->preparateMeniu[this->nrPreparateInMeniu - 1] = new Preparat(*preparat);
		return *this;
	}
	Restaurant operator+ (Preparat* preparat)
	{
		Restaurant rez = *this;
		rez += preparat;
		return rez;
	}

	bool operator>=(Restaurant r)
	{
		int nrOreMuncaThis = 0;
		int nrOreMuncaL = 0;
		for (int i = 0; i < this->nrAngajati; i++)
			nrOreMuncaThis = nrOreMuncaThis + this->angajati[i]->getOreLucruPeSaptamana();
		for (int i = 0; i < r.nrAngajati; i++)
			nrOreMuncaL = nrOreMuncaL + r.angajati[i]->getOreLucruPeSaptamana();
		return nrOreMuncaThis >= nrOreMuncaL;
	}

	bool operator==(Restaurant r)
	{
		if (strcmp(this->adresa, r.adresa) != 0) return false;
		if (this->nrPreparateInMeniu != r.nrPreparateInMeniu) return false;
		else if (this->nrPreparateInMeniu != 0) {
			for (int i = 0; i < this->nrPreparateInMeniu; i++)
				if ((this->preparateMeniu[i] == r.preparateMeniu[i]) == 0) return false;
		}
		if (this->nrAngajati != r.nrAngajati) return false;
		else if (this->nrAngajati != 0) {
			for (int i = 0; i < this->nrAngajati; i++)
				if ((this->angajati[i] == r.angajati[i]) == 0) return false;
		}
		return true;
	}
	explicit operator int()
	{
		return this->nrPreparateInMeniu;
	}


};
int Restaurant::taxaParcare = 10;

class ComunitateRestaurant {
	int nrPersoane = 0;
	Persoana** p = NULL;
public:
	ComunitateRestaurant(int nrPersoane, Persoana* p[]) {
		this->nrPersoane = nrPersoane;
		if (nrPersoane > 0 && p != NULL) {
			this->p = new Persoana * [this->nrPersoane];
			for (int i = 0; i < this->nrPersoane; i++)
			{
				this->p[i] = p[i];
			}
		}
	}
	void showStatut() {
		for (int i = 0; i < this->nrPersoane; i++) {
			this->p[i]->statut();
		}
	}
	void showRol() {
		for (int i = 0; i < this->nrPersoane; i++) {
			this->p[i]->rol();
		}
	}
	~ComunitateRestaurant() {
		//cout<<"\nApel destructor";
		delete[] p;
	}
};
class Raport
{
public:
	static void listaProduseDinLocatie(Restaurant l, int target)
	{
		if (target == 0)
			cout << "Raportul se afiseaza la consola.\n";
		else if (target == 1)
			cout << "Raportul se afiseaza in fisierul text <<listaProd.txt>>.\n";
		else if (target == 2)
			cout << "Raportul se afiseaza si la consola si in fisierul text <<listaProd.txt>>.\n";
		int nrProd = l.getNrPreparateInMeniu();
		if (nrProd < 1) {
			if (target == 0 || target == 2)
				cout << "Nu exista produse in locatie.\n";
			else if (target == 1 || target == 2)
			{
				ofstream gr1("listaProd.txt");
				gr1 << "Nu exista produse in locatie.\n";
				gr1.close();
			}
		}
		else {
			if (target == 0 || target == 2)
				l.getProduse();
			else if (target == 1 || target == 2)
			{
				ofstream gr1("listaProd.txt");
				l.getProduse();
				gr1.close();
			}
		}
	}
	static void listaAngajatiDinRestaurant(Restaurant l, int target)
	{
		if (target == 0)
			cout << "Raportul se afiseaza la consola.\n";
		else if (target == 1)
			cout << "Raportul se afiseaza in fisierul text <<listaAng.txt>>.\n";
		else if (target == 2)
			cout << "Raportul se afiseaza si la consola si in fisierul text <<listaAng.txt>>.\n";
		int nrAng = l.getNrAngajati();
		if (nrAng < 1) {
			if (target == 0 || target == 2)
				cout << "Nu exista angajati in restaurant.\n";
			else if (target == 1 || target == 2)
			{
				ofstream gr2("listaAng.txt");
				gr2 << "Nu exista angajati in restaurant.\n";
				gr2.close();
			}
		}
		else {
			if (target == 0 || target == 2)
				l.getAngajati();
			else if (target == 1 || target == 2)
			{
				ofstream gr2("listaAng.txt");
				l.getAngajati();
				gr2.close();
			}
		}
	}
	static void listaComenziAleClientului(Client cl, int target)
	{
		if (target == 0)
			cout << "Raportul se afiseaza la consola.\n";
		else if (target == 1)
			cout << "Raportul se afiseaza in fisierul text <<listaComenzi.txt>>.\n";
		else if (target == 2)
			cout << "Raportul se afiseaza si la consola si in fisierul text <<listaComenzi.txt>>.\n";
		int nrComenzi = cl.getNrComenzi();
		if (nrComenzi < 1) {
			if (target == 0 || target == 2)
				cout << "Nu exista angajati in locatie.\n";
			else if (target == 1 || target == 2)
			{
				ofstream gr3("listaComenzi.txt");
				gr3 << "Nu exista angajati in locatie.\n";
				gr3.close();
			}
		}
		else {
			if (target == 0 || target == 2)
				cl.getComenzi();
			else if (target == 1 || target == 2)
			{
				ofstream gr3("listaComenzi.txt");
				cl.getComenzi();
				gr3.close();
			}
		}
	}
};

void displayMenu()
{
	system("cls");
	//system("clear"); //pentru sistem de operare linux
	cout << " Va rugam, alegeti dintre urmatoarele optiuni: \n";
	cout << " 1. Adaugarea unui angajat.\n";
	cout << " 2. Inregistrarea unui nou client.\n";
	cout << " 3. Inregistrarea unei comenzi.\n";
	cout << " 4. Adaugarea unui nou produs.\n";
	cout << " 5. Adaugarea unui  restaurant disponibil.\n";
	cout << " 6. Exit.\n";
	cout << "\t";
}

void actionMenu(int option, string fisAng, string fisProd, string fisComenzi)
{
	if (option == 1)
	{
		Angajat aNou(100);
		cin >> aNou;
		fstream fOut(fisAng, ios::out | ios::binary | ios::app);
		aNou.writeToFile(fOut);
	}
	else if (option == 2)
	{
		Client clNou;
		cin >> clNou;
		fstream fOut("clienti.txt", ios::out | ios::binary);
		clNou.writeToFile(fOut);
	}
	else if (option == 3)
	{
		Comanda cNoua(100);
		cin >> cNoua;
		fstream fOut(fisComenzi, ios::out | ios::binary | ios::app);
		cNoua.writeToFile(fOut);
	}
	else if (option == 4)
	{
		Preparat pNou(100);
		cin >> pNou;
		fstream fOut(fisProd, ios::out | ios::binary | ios::app);
		pNou.writeToFile(fOut);
	}
	else if (option == 5)
	{
		Restaurant lNoua;
		cin >> lNoua;
		fstream fOut("restaurante.txt", ios::out | ios::binary);
		lNoua.writeToFile(fOut);
	}
	else if (option == 6)
	{
		cout << "Multumim, pe curand!\n";
	}
}

void menu(string fisAng, string fisProd, string fisComenzi)
{
	int selection = 0;
	cout << endl;
	bool flag = true;
	while (flag) {
		displayMenu();
		cin >> selection;
		if (selection == 6)
			flag = false;
		actionMenu(selection, fisAng, fisProd, fisComenzi);
	}
}

int main(int argc, const char* argv[])
{
	string fisAng;
	string fisProd;
	string fisComenzi;
	fisAng = "angajati.txt";
	fisProd = "preparate.txt";
	fisComenzi = "comenzi.txt";
	
	
	if (!(argc == 1 || argc == 4))
	{
		cout << "Eroare: programul primeste 0 sau 3 parametri.\n ";
		return 0;
	}
	else if (argc == 4)
	{
		fisAng = argv[1];
		fisProd = argv[2];
		fisComenzi = argv[3];
	}

	// Accesare meniu

	menu(fisAng, fisProd, fisComenzi);



	//Clasa Comanda
	Comanda c1(101);
	cout << c1;


	int preparate[] = { 1000,1001 };
	int cantitatiPreparate[2] = { 2, 1 };
	Comanda c2(101, "ok", 2, preparate, cantitatiPreparate);
	cout << c2;

	Comanda c3 = c2;
	cout << c3;
	cout << endl << "Numarul total de preparate de toate tipurile comandate este: " << c2.getNrTotalPreparateComanda();
	cout << endl << "Cantitatea maxima dintr-un preparat comandata este: " << c2.getCantitateMaximaComanda();

	//Get-uri
	cout << endl << "Id comanda: " << c2.getIdComanda();
	cout << endl << "Review: " << c2.getReview();
	cout << endl << "Nr preparate: " << c2.getNrPreparate() << endl;
	cout << "Preparate: ";
	c2.getPreparate();
	cout << endl << "Cantitati: ";
	c2.getCantitatiPreparate();

	c1 = c2;
	cout << c1;

	//Operatori << si >>
	cin >> c3;
	cout << c3;

	//Citire fisier
	ofstream g2("comanda.txt");
	g2 << c1;
	g2.close();
	Comanda c4(200);
	ifstream cf("comanda.txt");
	cf >> c4;
	cout << c4;
	cf.close();

	//Operator index
	try {
		int cantitate = c3[2];
		cout << endl << "\nCantitatea comandata din produsul al 3-lea este: " << cantitate;

	}
	catch (exception* ex)
	{
		cout << endl << ex->what();
		delete ex;
	}

	Comanda c(102);
	//operator ==
	cout << endl << (c == c3);

	//Operator cast
	cout << endl << (string)c3;
	//operator +
	int dateComanda[2] = { 1005,4 };
	cout << (c + dateComanda);
	//operator >=
	cout << endl << (c >= 2);
	//operator ++ si --
	c = c2++;
	cout << c;
	cout << c2;
	c = ++c3;
	cout << c;
	cout << c3;
	c = --c2;
	cout << c;
	cout << c2;
	c = c3--;
	cout << c;
	cout << c3;

	//operatorul !
	if (!c1)
		cout << endl << "Comanda contine cel putin 10 tipuri diferite de preparate.";
	else
		cout << endl << "Comanda contine mai putin de 10 tipuri de preparate.";

	//Exceptii set-uri
	try
	{
		c.setReview("Excelent");
		cout << c;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}

	try
	{
		c.setNrPreparate(4);
		cout << c;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}

	try //pt schimbarea vectorului de preparate, mai intai se foloseste metoda setNrPreparate
	{
		c.setPreparate(preparate);
		cout << c;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}

	try//pt a schimba vectorul de cantitati, mai intai se folosesc metodele setPrep si setNrPr
	{
		c.setCantitatiPreparate(cantitatiPreparate);
		cout << c;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}


	//Clasa Client
	Comanda* comenzi[5] = { &c1,&c2 };
	Client cl1;
	cout << cl1;
	string nume = "Bucur";
	string prenume = "Alexia-Gabriela";
	char nrTelefon[] = "0762873923";
	Client cl2(nume, prenume, nrTelefon, 2, comenzi);
	cout << cl2;
	Client cl3 = cl2;
	cout << cl3;
	cout << "\nNumarul de telefon al clientului este: " << cl2.getFixSauMobil();
	cout << "\nNumarul total de preparate comandate de client este de: " << cl2.getNrTotalPreparateComandate();


	//Get-uri
	cout << endl << "Nume: " << cl2.getNume();
	cout << endl << "Prenume: " << cl2.getPrenume() << endl;
	cout << "Nr telefon: ";
	cl2.getNrTelefon();
	cout << endl << "Nr comenzi: " << cl2.getNrComenzi() << endl;
	cout << "Comenzi: ";
	cl2.getComenzi();

	//Metode virtuale
	cl2.statut();
	cl2.rol();

	cl1 = cl2;
	cout << cl1;
	//Operatori << si >>
	cin >> cl3;
	cout << cl3;

	//Citire fisier
	ofstream g4("client.txt");
	g4 << cl1;
	g4.close();
	Client cl4;
	ifstream clf("client.txt");
	clf >> cl4;
	cout << cl4;
	clf.close();

	//Operatorul index
	try {
		Comanda comanda = cl3[1];
		cout << endl << "\nCea de-a doua comanda este:" << comanda;
	}
	catch (exception* ex)
	{
		cout << endl << ex->what();
		delete ex;
	}
	Client cl;
	//operator ==
	cout << endl << (cl == cl3);
	//Operator cast
	cout << endl << (int)cl3;
	//operator +
	cout << (cl + &c3);
	//operator >=
	cout << endl << (cl >= cl2);
	//operator ++ si --
	/*cl = cl2++;
	cout << cl;
	cout << cl2;
	cl = ++cl3;
	cout << cl;
	cout << cl3;
	cl = --cl2;
	cout << cl;
	cout << cl2;
	cl = cl3--;
	cout << cl;
	cout << cl3;*/
	//operatorul !
	if (!cl1)
		cout << endl << "Numele clientului are aceeasi lungime ca si prenumele sau.";
	else
		cout << endl << "Numele si prenumele clientului sunt de lungimi diferite.";
	//Exceptii set-uri:
	try
	{
		cl.setNume("Ionescu");
		cout << cl;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}
	try
	{
		cl.setPrenume("Matei");
		cout << cl;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}
	try
	{
		cl.setNrTelefon("072130");
		cout << cl;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}
	try
	{
		cl.setNrComenzi(2);
		cout << cl;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}
	try    //pt a schimba vectorul de comenzi, mai intai se foloseste metoda setNrComenzi
	{
		cl.setComenzi(comenzi);
		cout << cl;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}

	//CLASA CLIENT VIP - extindere client
	string produseWL[3] = { "Sampanie ","CheeseCake","Whiskey" };
	int reduceri[4] = { 20,25,40,50 };
	ClientVIP clv1(cl2, 3, produseWL, 4, reduceri);
	cout << clv1;

	//Clasa Preparat
	Preparat p1(100);
	cout << p1;
	int stoc[5] = { 2,4,5,8,10 };
	float* pr;
	pr = new float;
	*pr = 75.2f;
	Preparat p2(101, "Pizza", 5, stoc, pr);
	cout << p2;
	Preparat p3 = p2;
	cout << p3;
	float* scump;
	scump = new float;
	*scump = 5.3f;
	p2.scumpirePreparat(scump);
	cout << endl << "Pretul dupa scumpire este: " << (float)p2;
	float* ieft;
	ieft = new float;
	*ieft = 0.5f;
	p2.ieftinirePreparat(ieft);
	cout << endl << "Pretul dupa ieftinire este: " << (float)p2;
	//Get-uri
	cout << endl << "Cod preparat: " << p2.getCodPreparat();
	cout << endl << "Denumire: " << p2.getDenumire();
	cout << endl << "Numar ingrediente: " << p2.getNrIngrediente() << endl;
	cout << "Stocuri: ";
	p2.getStocuri();
	cout << endl << "Pret: " << p2.getPret();

	p1 = p2;
	cout << p1;
	//Operatoriu >> si <<
	cin >> p3;
	cout << p3;

	//Citire fisier
	ofstream g3("preparat.txt");
	g3 << p1;
	g3.close();
	Preparat p4(200);
	ifstream pf("preparat.txt");
	pf >> p4;
	cout << p4;
	pf.close();

	//Operatorul index
	try {
		int durata = p3[3];
		cout << endl << "\nStocul pentru ingredientul numarul 4 este: " << durata;
	}
	catch (exception* ex)
	{
		cout << endl << ex->what();
		delete ex;
	}

	Preparat p(102);
	//operator ==
	cout << endl << (p == p3);
	//Operator cast
	cout << endl << (float)p3;
	//operator +
	cout << (p + 4);
	//operator >=
	cout << endl << (p >= p2);
	//operator ++ si --
	p = p2++;
	cout << p;
	cout << p2;
	p = ++p3;
	cout << p;
	cout << p3;
	p = --p2;
	cout << p;
	cout << p2;
	p = p3--;
	cout << p;
	cout << p3;
	//operatorul !
	if (!p1)
		cout << endl << "Preparatul este mai scump de 100 de lei.";
	else
		cout << endl << "Preparatul costa mai putin de 100 de lei.";
	//Exceptii set-uri:
	try
	{
		p.setDenumire("Paste");
		cout << p;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}
	float* pret;
	pret = new float;
	*pret = 80.3f;

	try
	{
		p.setPret(pret);
		cout << p;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}
	try
	{
		p.setNrIngrediente(5);
		cout << p;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}
	try //pt a schimba vectorul de stocuri pentru ingrediente, mai intai se acceseaza metoda setNrIngrediente pentru a-i aloca lungimea vectorului cu care va fi schimbat
	{
		p.setStocuri(stoc);
		cout << p;
	}
	catch (exception* ex)
	{
		cout << endl << ex->what();
		delete ex;
	}

	//Clasa Angajat
	Angajat a1(100);
	cout << a1;
	int durateTaskuri[3] = { 1,2,3 };
	Angajat a2(222, "Bucur", "Alexia-Gabriela", 3, 3, durateTaskuri);
	cout << a2;
	Angajat a3 = a2;
	cout << a3;
	cout << endl << "Numarul de ore lucrate de angajat pe saptamana este: " << a2.getOreLucruPeSaptamana();
	cout << endl << "Anul de angajare al angajatului este: " << a2.getAnAngajare();
	//Getters
	cout << endl << "Codul angajatului: " << a2.getCod() << endl;
	cout << "Numele angajatului este: ";
	a2.getNume();
	cout << "\nPrenumele angajatului este: " << a2.getPrenume();
	cout << endl << "Vechimea: " << a2.getVechime();
	cout << "\nNumarul de taskuri: " << a2.getNrTaskuri();
	cout << "\nLista durate taskuri ";
	a2.getDurateTaskuri();

	//Metode virtuale
	a2.statut();
	a2.rol();


	a1 = a2;
	cout << a1;

	//Operatori << si >>
	//cin >> a1;
	//cout << a1;

	cin >> a3;
	cout << a3;

	//Citire fisier
	ofstream g1("angajat.txt");
	g1 << a1;
	g1.close();
	Angajat a4(200);
	ifstream af("angajat.txt");
	af >> a4;
	cout << "\nAngajat citit din fisier: " << a4;
	af.close();

	//Operatorul index
	int dt[5] = { 2,5,3,4,5 };
	Angajat a9(333, "Bucur", "Crina Any-Maria", 3, 5, dt);

	try {
		int durata = a9[4];
		cout << endl << "\nDurata celui de-al 5-lea task este: " << durata;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}


	try {
		int durata = a9[6];
		cout << endl << "Durata celui de-al 6-lea task este: " << durata;

	}
	catch (exception* ex) {
		cout << "\nExemplu exceptie cast";
		cout << endl << ex->what();
		delete ex;
	}



	Angajat a(102);
	
	//Operator cast
	//operator ==
	cout << endl << (a == a3);
	//Operator cast
	cout << endl << (int)a3;
	//operator +
	cout << (a + 4);
	//operator >=
	cout << endl << (a >= a2);

	//Operator +

	//operator >=

	//operator ++ 
	//operator ++ si --
	a = a2++;
	cout << a;
	cout << a2;
	a = ++a3;
	cout << a;
	cout << a3;
	a = --a2;
	cout << a;
	cout << a2;
	a = a3--;
	cout << a;
	cout << a3;
	//// post-fixat
	//a = a2++;
	//cout << a;
	////pre-fixat
	//a = ++a2;
	//cout << a;


	////Operator --
	////pre
	//a = --a2;

	//cout << a;
	////post
	//a = a2--;
	//cout << a;

	//a = a2;
	//cout << a;
	//operatorul !
	if (!a1)
	{
		cout << endl << "Angajatul lucreaza la magazin de mai mult de 2 ani";
	}
	else
		cout << endl << "Angajatul lucreaza la magazin de mai putin de 2 ani";


	//Operatorul +
	cout << (a + 4);

	//Operator ==
	Angajat a5(221, "Bucur", "Alexia-Gabriela", 4, 3, durateTaskuri);
	Angajat a6(220, "Bucur", "Alexia-Gabriela", 3, 3, durateTaskuri);
	cout << endl << "Sunt obiectele a5 si a6 identice, 1=da,0=nu,op ==";
	cout << endl << (a6 == a5);

	//Operator cast
	cout << endl << "operator cast";
	cout << endl << (int)a3;
	//operator >=
	cout << endl << "Este a5 mai vechi decat a6?";
	cout << endl << (a5 >= a6);


	//Testare fisier binar
	fstream fOut("fisier.txt", ios::out | ios::binary);
	a1.writeToFile(fOut);
	fOut.close();
	//fstream fIn("fisier.txt", ios::in | ios::binary);
	//Angajat aNou(100);
	//aNou.readFromFile(fIn);
	//fIn.close();
	//cout << aNou;


	//CLASA MANAGER - extindere angajat
	int subordonati[3] = { 1000,1001,1002 };
	string adrese[2] = { "Unirii","Rahova" };
	Manager m1(a, 3, subordonati, 2, adrese);
	cout << m1;

	//Clasa Restaurant
	Restaurant r1;
	Preparat* preparateMeniu[5] = { &p1,&p2 };
	Angajat* angajati[5] = { &a1,&a2 };
	char adresa[] = "Bucuresti";
	Restaurant r2(adresa, 2, preparateMeniu, 2, angajati);
	cout << r2;
	Restaurant r3 = r2;
	cout << r3;
	cout << endl << "Cel mai scump produs din restaurant costa " << r2.getCelMaiMarePret() << " lei.";
	cout << endl << "Angajatul cu vechimea cea mai mare lucreaza la restaurant de " << r2.getVechimeaCeaMaiMare() << " ani.";
	//Get-uri
	cout << endl << "Taxa parcare: " << r2.getTaxaParcare() << endl;
	cout << "Adresa: ";
	r2.getAdresa();
	cout << endl << "Nr preparate: " << r2.getNrPreparateInMeniu() << endl;
	cout << "Preparate: ";
	r2.getNrPreparateInMeniu();
	cout << endl << "Nr angajati: " << r2.getNrAngajati() << endl;
	cout << "Angajati: ";
	r2.getAngajati();

	r1 = r2;
	cout << r1;
	//Operatori << si >>
	cin >> r3;
	cout << r3;

	//Citire fisier
	ofstream g5("locatie.txt");
	g5 << r1;
	g5.close();
	Restaurant l4;
	ifstream lf("locatie.txt");
	lf >> l4;
	cout << l4;
	lf.close();


	//Operatorul index
	try {
		int nrOreLucru = r3[1];
		cout << endl << "\nToti angajatii restaurantului lucreaza impreuna, cumulat, " << nrOreLucru << "ore pe saptamana.";
	}
	catch (exception* ex)
	{
		cout << endl << ex->what();
		delete ex;
	}

	Restaurant r;
	//operator ==
	cout << endl << (r == r3);
	//Operator cast
	cout << endl << (int)r3;
	//operator +
	cout << (r + &p3);
	//operator >=
	cout << endl << (r >= r2);
	//operator ++ si --
	/*l = l2++;
	cout << l;
	cout << l2;
	l = ++l3;
	cout << l;
	cout << l3;
	l = --l2;
	cout << l;
	cout << l2;
	l = l3--;
	cout << l;
	cout << l3;*/

	//operatorul !
	if (!r1)
		cout << endl << "La restaurant lucreaza numarul maxim admisibil de angajati.";
	else
		cout << endl << "La restaurant mai pot fi angajate persoane.";

	//Exceptii set-uri:
	try
	{
		r.setTaxaParcare(7);
		cout << r;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}
	try
	{
		r.setAdresa("Brasov");
		cout << r;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}
	try
	{
		r.setNrPreparate(2);
		cout << r;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}
	try   //pt a schimba vectorul de produse, mai intai se foloseste metoda setNrProduse
	{
		r.setPreparateMeniu(preparateMeniu);
		cout << r;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}
	try
	{
		r.setNrAngajati(2);
		cout << r;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}
	try    //pt a schimba vectorul de angajati, mai intai se foloseste metoda setNrAngajati
	{
		r.setAngajati(angajati);
		cout << r;
	}
	catch (exception* ex) {
		cout << endl << ex->what();
		delete ex;
	}
	//Rapoarte

	Raport::listaAngajatiDinRestaurant(r2, 1);
	Raport::listaProduseDinLocatie(r2, 0);
	Raport::listaComenziAleClientului(cl2, 2);


	//CLASA COMUNITATE RESTAURANT - ierarhie
	Persoana* pers[4] = { &a2,&m1,&cl2,&clv1 };
	ComunitateRestaurant cm(4, pers);
	cm.showStatut();
	cm.showRol();	

	return 0;
}

