#include <iostream>
#include<string>
#include<fstream>
using namespace std;

enum tipMarker
{
	gros = 1, subtire = 2, mediu = 3, necunoscut = 4

};

class Marker{
	char* culoare;
	int gramaj;
	string producator;
	float dimensiune;
	static int grosimeMarker;
	const int id;
	static int numarator;
	tipMarker TipMarker;

public:
	tipMarker getTipMarker() {
		return this->TipMarker;
	}
	const int getId() {
		return this->id;
	}
	char* getCuloare() {
		return this->culoare;
	}
	int getGramaj() {
		return this->gramaj;
	}
	string getProducator() {
		return this->producator;
	}
	float getDimensiune() {
		return this->dimensiune;
	}
	void setCuloare(char* culoare) {
		this->culoare = new char[strlen(culoare) + 1];
		strcpy_s(this->culoare, strlen(culoare) + 1, culoare);
	}
	void setGramaj(int gramaj) {
		this->gramaj = gramaj;
	}
	void setProducator(string producator) {
		this->producator = producator;
	}
	void setDimensiune(float dimensiune) {
		this->dimensiune = dimensiune;
	}
	void setTipMarker(tipMarker TipMarker) {
		this->TipMarker = TipMarker;
	}
	Marker():id(numarator++) {
		this->culoare = new char[strlen("NECUNOSCUTA") + 1];
		strcpy_s(this->culoare, strlen("NECUNOSCUTA") + 1, "NECUNOSCUTA");
		this->gramaj = 0;
		this->producator = "ANONIM";
		this->dimensiune = 0;
		this->TipMarker = necunoscut;
	}

	Marker(const char* culoare, int gramaj, string producator, float dimensiune,tipMarker TipMarker ):id(numarator++)
	{
		this->culoare = new char[strlen(culoare) + 1];
		strcpy_s(this->culoare, strlen(culoare) + 1, culoare);
		this->gramaj = gramaj;
		this->producator = producator;
		this->dimensiune = dimensiune;
		this->TipMarker = TipMarker;
	}
	
	~Marker() {
		if (this->culoare != nullptr)
		{
			delete[]this->culoare;
		}
	}

	friend ostream& operator<<(ostream& out, const Marker& m) {
		out << "ID: " << m.id << endl;
		out << "Culoare: " << m.culoare << endl;
		out << "Gramaj: " << m.gramaj << endl;
		out << "Producator: " << m.producator << endl;
		out << "Dimensiune: " << m.dimensiune << endl;
		out << "Tip: " << m.TipMarker << endl;
		return out;
	}

	//operatorul de copiere

	Marker(const Marker& m):id(m.numarator++) {
		this->culoare = new char[strlen(m.culoare) + 1];
		strcpy_s(this->culoare, strlen(m.culoare) + 1, m.culoare);
		this->gramaj = m.gramaj;
		this->producator = m.producator;
		this->dimensiune = m.dimensiune;
		this->TipMarker = m.TipMarker;
	}

	//operatorul =

	Marker& operator=(const Marker& m) {
		if (this != &m) {
			if (this->culoare != nullptr)
			{
				delete[]this->culoare;
			}
			this->culoare = new char[strlen(m.culoare) + 1];
			strcpy_s(this->culoare, strlen(m.culoare) + 1, m.culoare);
			this->gramaj = m.gramaj;
			this->producator = m.producator;
			this->dimensiune = m.dimensiune;
			this->TipMarker = m.TipMarker;
		}
		return *this;
	}
	//operator==

	bool operator==(const Marker& m) {
		if (strcmp(this->culoare, m.culoare)==0 && this->gramaj == m.gramaj && this->producator == m.producator && this->dimensiune == m.dimensiune&&this->TipMarker==m.TipMarker)
			return true;
		else return false;
	}

	friend istream& operator>>(istream& in, Marker& m) {
		
		cout << "Introduceti culoare: ";
		in >> m.culoare;
		cout << "Introduceti gramaj: ";
		in >> m.gramaj;
		cout << "Introduceti producator: ";
		in >> m.producator;
		cout << "Introduceti dimensiune: ";
		in >> m.dimensiune;
		cout << "Introduceti tip: ";
		int val;
		in >> val;
		switch (val) {
		case 1: m.TipMarker = gros; break;
		case 2: m.TipMarker = subtire; break;
		case 3: m.TipMarker = mediu; break;
		case 4: m.TipMarker = necunoscut; break;
		}
		return in;
	}

	friend ofstream& operator<<(ofstream& out, const Marker& m) {
		out << m.culoare << endl;
		out << m.gramaj << endl;
		out << m.producator << endl;
		out << m.dimensiune << endl;
		out << m.TipMarker << endl;
		return out;
	}

	friend ifstream& operator>>(ifstream& in, Marker& m) {
		in >> m.culoare;
		in >> m.gramaj;
		in >> m.producator;
		in >> m.dimensiune;
		int val;
		in >> val;
		switch (val)
		{
		case 1:m.TipMarker = gros; break;
		case 2:m.TipMarker = subtire; break;
		case 3:m.TipMarker = mediu; break;
		case 4:m.TipMarker = necunoscut; break;
	
		}

		return in;
	}


	Marker& operator+=(float nr) {
		this->dimensiune += nr;
		return *this;
	}

	//operator cast la int

	operator int() {
		return this->dimensiune;
	}


};

int Marker::grosimeMarker = 2;
int Marker::numarator = 1;

class MarkerElectronic : public Marker {
	int baterie;

public:
	MarkerElectronic() :Marker() {
		this->baterie = 0;
	}

	MarkerElectronic(const char* culoare, int gramaj, string producator, float dimensiune, int baterie,tipMarker TipMarker) :Marker(culoare, gramaj,producator, dimensiune, TipMarker) {
		this->baterie = baterie;
	}
	
	MarkerElectronic(const MarkerElectronic& me):Marker(me) {
		this->baterie = me.baterie;
	}

	MarkerElectronic& operator=(const MarkerElectronic& me) {
		if (this != &me) {
			Marker::operator=(me);
			this->baterie = me.baterie;

		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const MarkerElectronic& me) {
		out << (Marker&)me;
		out <<"Baterie: "<< me.baterie << endl;
		return out;
	}

	friend istream& operator>>(istream& in, MarkerElectronic& me) {
		in >> (Marker&)me;
		cout << "Introduceti baterie: ";
		in >> me.baterie;
		return in;
	}

	MarkerElectronic& operator-=(int val) {
		this->baterie -= val;
		return *this;
	}
};


class Clasa {
	int nrMarkere;
	Marker* marker;

public:
	Clasa() {
		this->nrMarkere = 0;
		this->marker = nullptr;
	}

	Clasa(int nrMarkere, Marker* marker) {
		this->nrMarkere = nrMarkere;
		this->marker = new Marker[this->nrMarkere];
		for (int i = 0; i < this->nrMarkere; i++) {
			this->marker[i] = marker[i];
		}
	}

	friend ostream& operator<<(ostream& out, const Clasa& c) {
		out << "Numar markere: " << c.nrMarkere << endl;
		for (int i = 0; i < c.nrMarkere; i++) {
			out << "Markerul " << i+1 << ": " << c.marker[i] << endl;
		}
		out << endl;
		return out;
	}
	

	//friend istream& operator>>(istream& in, Clasa& c) {
	//	cout << "Introduceti nr markere: ";
	//	in >> c.nrMarkere;
	//	cout << "Introduceti markerele dorite: ";
	//	for (int i = 0; i < c.nrMarkere; i++)
	//	{
	//		in >> c.marker[i];
	//	}
	//	return in;
	//}

	Clasa& operator+=(const Marker& m) {
		Marker* copie = this->marker;
		this->marker = new Marker[this->nrMarkere + 1];
		for (int i = 0; i < this->nrMarkere; i++) {
			this->marker[i] = copie[i];
		}
		this->marker[this->nrMarkere] = m;
		this->nrMarkere++;
		delete[]copie;
		return *this;
	}

	//gramaj total cu functie()

	int operator()() {
		int suma = 0;
		for (int i = 0; i < this->nrMarkere; i++) {
			suma = suma + this->marker[i].getGramaj();
		}
		return suma;
	}

	Marker& operator[](int poz) {
		for (int i = 0; i < this->nrMarkere; i++) {
			if (i == poz) {
				return this->marker[i];
			}
		}
	}

};

int main()
{

	Marker m1;
	cout << m1<<endl;
	cout << endl;

	Marker m2("Rosu", 15, "FaberCastel", 10.23,gros);
	cout << m2 << endl;
	cout << endl;

	Marker m3(m2);
	cout << m3 << endl;
	cout << endl;

	if (m3 == m2) {
		cout << "SUNT EGALE" << endl;
	}
	else cout << "NU SUNT EGALE" << endl;
	cout << endl;

	m3 = m1;
	cout << m3 << endl;
	cout << endl;

	MarkerElectronic me1;
	cout << me1 << endl;
	cout << endl;

	MarkerElectronic me2("Rosu", 15, "FaberCastel", 10, 40, gros);
	cout << me2 << endl;
	cout << endl;

	me2 -= 5;
	cout << me2;
	cout << endl;

	MarkerElectronic me3(me1);
	cout << me3 << endl;
	cout << endl;

	me2 = me1;
	cout << me2;
	cout << endl;

	/*Marker m4;
	cin >> m4;
	cout << m4;
	cout << endl;*/

	ofstream fout("Marker.txt", ios::out);
	fout << m2;
	fout.close();


	/*ifstream fin("Marker.txt", ios::in);
	fin >> m4;
	fin.close();
	cout << m4;
	cout << endl;*/

	/*MarkerElectronic me4;
	cin >> me4;
	cout << me4;
	cout << endl;*/


	Marker vectClasa[] = { m1,m2 };
	Clasa c1(2, vectClasa);
	cout << c1 << endl;

	/*Clasa c2;
	cin >> c2;
	cout << c2;*/

	c1 += m3;
	cout << c1;
	cout << endl;

	cout << c1();
	cout << endl;
	
	cout << c1[2];
	cout << endl;

	m2 += 20;
	cout << m2;

	cout << (float)m2;
	cout << endl;

	return 0;
}
