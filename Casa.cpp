#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Casa {
protected: //!cand avem mostenire pt vila, punem aici protected
	char* adresa;
	int nrCamere;
	float suprafata;
	int anConstructie;
	static bool auElectricitate;


public:
	Casa()
	{
		this->adresa = new char[strlen("?") + 1];
		strcpy(this->adresa, "?");
		this->nrCamere = 0;
		this->suprafata = 0;
		this->anConstructie = 2000;
	}

	int getNrCamere() {
		return this->nrCamere;
	}

	void setNrCamere(int nrCamere) {
		this->nrCamere = nrCamere;
	}

	Casa(const char* adresa, int nrCamere,float suprafata,int anConstructie)
	{
		this->adresa = new char[strlen(adresa) + 1];
		strcpy(this->adresa, adresa);
		this->nrCamere = nrCamere;
		this->suprafata = suprafata;
		this->anConstructie = anConstructie;
	}

	//constructor de copiere
	Casa(const Casa& c) {
		this->adresa = new char[strlen(c.adresa) + 1];
		strcpy(this->adresa, c.adresa);
		this->nrCamere = c.nrCamere;
		this->suprafata = c.suprafata;
		this->anConstructie = c.anConstructie;
	}


	~Casa(){
		if (this->adresa != nullptr)
		{
			delete[]this->adresa;
		}
	}

	//op =
	Casa&operator=(const Casa& c) {
		if (this != &c)
		{
			if (this->adresa != nullptr)
			{
				delete[]this->adresa;
			}
			this->adresa = new char[strlen(c.adresa) + 1];
			strcpy(this->adresa, c.adresa);
			this->nrCamere = c.nrCamere;
			this->suprafata = c.suprafata;
			this->anConstructie = c.anConstructie;

		}
		return *this;
	}


	friend  ostream& operator<<(ostream& out, const Casa& c) {

		out << "Adresa: "<< c.adresa << endl;
		
		out << "Numar Camere: " << c.nrCamere << endl;
		
		out << "Suprafata: " << c.suprafata << endl;
		
		out << "An constructie: " << c.anConstructie << endl;
		
		out << "Au electricitate(1-Da sau 0-Nu): " << c.auElectricitate << endl;
		return out;
	}

	//ofstream si istream sunt osytream si istream fara texte ajutatoare 
	friend  ofstream& operator<<(ofstream& out, const Casa& c) {

		out << c.adresa << endl;

		out << c.nrCamere << endl;

		out <<c.suprafata << endl;

		out <<  c.anConstructie << endl;

		out <<  c.auElectricitate << endl;
		return out;
	}
	friend istream& operator >>(istream& in, Casa& c) {
		cout << "Adresa: ";
		if (c.adresa != NULL) {
			delete[]c.adresa;

		}
		char aux[100]; //ca un caracter este pentru terminator(\0)
		in >> ws;
		in.getline(aux, 99);
		//in >> c.adresa;
		c.adresa = new char[strlen(aux) + 1];
		strcpy(c.adresa, aux);
		//pt string folosim urmatoarea functie:string exSir->getLine(in,exSir);
		in >> c.nrCamere;
		in >> c.suprafata;
		in >> c.anConstructie;
		return in;
	}

	friend ifstream& operator >>(ifstream& in, Casa& c) {
		cout << "Adresa: ";
		if (c.adresa != NULL) {
			delete[]c.adresa;

		}
		char aux[100]; //ca un caracter este pentru terminator(\0)
		in >> ws;
		in.getline(aux, 99);
		//in >> c.adresa;
		c.adresa = new char[strlen(aux) + 1];
		strcpy(c.adresa, aux);
		//pt string folosim urmatoarea functie:string exSir->getLine(in,exSir);
		in >> c.nrCamere;
		in >> c.suprafata;
		in >> c.anConstructie;
		return in;
	}

	bool operator()(int nrPersoane) {
		return this->nrCamere >= nrPersoane;
	}

	bool operator==(Casa c) {
		return (strcmp(this->adresa, c.adresa) == 0 && this->nrCamere == nrCamere && this->suprafata == c.suprafata && this->anConstructie == c.anConstructie);

	}

	bool operator!=(Casa c) {
		return!(*this == c);
	}

	void ScriereInBinar(string numeFisier) {
		ofstream f(numeFisier, ios::out | ios::binary);
		//pt char*
		int dimAdresa = strlen(adresa);
		f.write((char*) &dimAdresa, sizeof(dimAdresa));
		f.write(adresa, dimAdresa + 1);

		//pt string --ex string nume
		/*
		int dimNume=strlen(nume);
		f.write((char*)&dimNume,sizeof(dimNume));
		f.write(nume.c_str(),dimNume+1);
		*/
		f.write((char*)&dimAdresa, sizeof(dimAdresa));
		f.write((char*)&suprafata, sizeof(suprafata));
		f.write((char*)&anConstructie, sizeof(anConstructie));
		f.close();
	}
	void CitireDinBinar(string numeFisier) {
		ifstream f(numeFisier, ios::in | ios::binary);
		//pt char*
		int dimAdresa = 0;
		if (this->adresa != NULL) {
			delete[]this->adresa;
		}
		f.read((char*)&dimAdresa, sizeof(dimAdresa));
		adresa = new char[dimAdresa + 1];
		f.read(adresa, dimAdresa + 1);

		//pt string --ex string nume
		/*
		int dimNume=strlen(nume);
		f.write((char*)&dimNume,sizeof(dimNume));
		char* aux=new char[dimNume+1];
		this->nume=aux;
		delete[]aux;
		
		*/
		f.read((char*)&dimAdresa, sizeof(dimAdresa));
		f.read((char*)&suprafata, sizeof(suprafata));
		f.read((char*)&anConstructie, sizeof(anConstructie));
		f.close();
	}

	virtual string tipImobil() {
		return "Casa normala";

	}

	string tipClasa() {
		return "Acest obiect este de tip casa";
	}
};
bool Casa::auElectricitate = true;

class Vila :public Casa {
	int nrEtaje;
	bool areMansarda;
public:
	Vila() :Casa() {
		this->nrEtaje = 0;
		this->areMansarda = 0;
	}
	Vila(const char* adresa, int nrCamere, float suprafata, int anConstructie,int nrEtaje, bool areMansarda) :Casa(adresa,nrCamere,suprafata,anConstructie) {
		this->nrEtaje = nrEtaje;
		this->areMansarda = areMansarda;
	}


	Vila(const Vila &v) :Casa(v) {
		this->nrEtaje = v.nrEtaje;
		this->areMansarda = v.areMansarda;
	}

	~Vila()
	{

	}

	Vila& operator=(const Vila& v) {
		Casa::operator=(v);
			this->nrEtaje = v.nrEtaje;
			this->areMansarda = v.areMansarda;
		
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Vila& v) {
		out << (Casa&)v;
		out << "Numar etaje:" << v.nrEtaje << endl;
		out << "Are mansarda(1-Da,0-Nu)" << v.areMansarda << endl;
		return out;

	}
	friend ofstream& operator<<(ofstream& out, const Vila& v) {
		out << (Casa&)v;
		out <<  v.nrEtaje << endl;
		out <<  v.areMansarda << endl;
		return out;

	}

	friend istream& operator>>(istream& in, Vila& v) {
		in >> (Casa&)v;
		cout << "Numara etaje: ";
		in >> v.nrEtaje;
		cout << "Are mansarda(1-Da,0-Nu)";
		in >> v.areMansarda;
		return in;

	}

	friend ifstream& operator>>(ifstream& in, Vila& v) {
		in >> (Casa&)v;
		in >> v.nrEtaje;
		in >> v.areMansarda;
		return in;

	}
	void ScriereInBinar(string numeFisier) {
		ofstream f(numeFisier, ios::out | ios::binary);
		//pt char*
		int dimAdresa = strlen(adresa);
		f.write((char*)&dimAdresa, sizeof(dimAdresa));
		f.write(adresa, dimAdresa + 1);

		//pt string --ex string nume
		/*
		int dimNume=strlen(nume);
		f.write((char*)&dimNume,sizeof(dimNume));
		f.write(nume.c_str(),dimNume+1);
		*/
		f.write((char*)&nrCamere, sizeof(nrCamere));
		f.write((char*)&suprafata, sizeof(suprafata));
		f.write((char*)&anConstructie, sizeof(anConstructie));
		f.write((char*)&nrEtaje, sizeof(nrEtaje));
		f.write((char*)&areMansarda, sizeof(areMansarda));
		f.close();
	}
	void CitireDinBinar(string numeFisier) {
		ifstream f(numeFisier, ios::in | ios::binary);
		//pt char*
		int dimAdresa = 0;
		if (this->adresa != NULL) {
			delete[]this->adresa;
		}
		f.read((char*)&dimAdresa, sizeof(dimAdresa));
		adresa = new char[dimAdresa + 1];
		f.read(adresa, dimAdresa + 1);

		//pt string --ex string nume
		/*
		int dimNume=strlen(nume);
		f.write((char*)&dimNume,sizeof(dimNume));
		char* aux=new char[dimNume+1];
		this->nume=aux;
		delete[]aux;

		*/
		f.read((char*)&dimAdresa, sizeof(dimAdresa));
		f.read((char*)&suprafata, sizeof(suprafata));
		f.read((char*)&anConstructie, sizeof(anConstructie));
		f.read((char*)&nrEtaje, sizeof(nrEtaje));
		f.read((char*)&areMansarda, sizeof(areMansarda));
		f.close();
	}

	virtual string tipImobil() {
		return "Vila cu etaj";

	}

	string tipClasa() {
		return "Acest obiect este de tip vila";
	}
};

template<typename cls> 
void afisareObiectSauValoare(cls parametru) {
	cout << parametru << endl;

}
int main()
{
	Casa c;
	cout << c.getNrCamere()<<endl;
	c.setNrCamere(4);
	cout << c.getNrCamere() << endl << endl;
	Casa c1("Str teiul Doameni", 4, 500, 2012);
	cout << endl << c1 << endl;
	Casa c2 = c;
	cout << endl << c2 << endl;
	c2 = c1;
	cout << endl << c2 << endl;
	cout << c2(3) << endl;

	if (c2(3)) {
		cout << "Fiecare persoana are camera ei" << endl;

	}
	else
	{
		cout << "Fiecare persoana nu are camera ei" << endl;

	}
	if (c2(13)) {
		cout << "Fiecare persoana are camera ei" << endl;

	}
	else
	{
		cout << "Fiecare persoana nu are camera ei" << endl;

	}

	if (c1 == c)
	{
		cout << "Casele sunt identice!" << endl;

	}
	else {
		cout << "Casele nu sunt identice!" << endl;
	}

	if (c1 == c2)
	{
		cout << "Casele sunt identice!" << endl;

	}
	else {
		cout << "Casele nu sunt identice!" << endl;
	}

	Casa cEx;
	cout << endl << cEx << endl;
	//cin >> cEx;
	//cout << endl << cEx << endl;

	//citirea si scrierea din fisiere
	ofstream f("aplicatie.txt", ios::out);
	f << c2 << endl;
	f.close();

	ifstream g("aplicatie.txt", ios::in);
	g >> cEx;
	g.close();
	cout << endl << cEx << endl;

	cout << "---------------------------------------" << endl;

	Casa cBinar;
	cout << endl << cBinar << endl;
	c2.ScriereInBinar("casa.bin");
	cBinar.CitireDinBinar("casa.bin");
	cout << endl << cBinar << endl;

	cout << "---------------------------------------" << endl;
	cout << "---------------------------------------" << endl;
	cout << "---------------------------------------" << endl;

	Vila v;
	Vila v1("Str Ispirescu", 4, 1600, 1999, 8, 0);
	cout << v1 << endl;
	Vila v2 = v;
	cout << v2 << endl;
	v2 = v1;
	cout << v2 << endl;

	Vila vEx;
	cout << endl << vEx << endl;
	//cin >> vEx;
	//cout << endl << vEx << endl;


	//citirea si scrierea din fisiere
	cout << "---------------------------------------" << endl;

	ofstream fv("vila.txt", ios::out);
	fv << v1 << endl;
	fv.close();

	ifstream gv("vila.txt", ios::in);
	gv >> vEx;
	gv.close();
	cout << endl << vEx << endl;

	cout << "---------------------------------------" << endl;
	cout << "---------------------------------------" << endl;
	cout << "---------------------------------------" << endl;
	cout << "---------------------------------------" << endl;

	Vila vBinar;
	cout << endl << vBinar << endl;
	v2.ScriereInBinar("vila.bin");
	vBinar.CitireDinBinar("vila.bin");
	cout << endl << vBinar << endl;

	//early binding--legatura anticipata/timpurie-- apare de la momentul  compilarii programului
	//cel mai bun ex este legat de ce constructor apelam
	//early binding-ul este vizibil prin polimorfism parametric
	Casa cExEarly;//constructor fara parametrii/implicit/default

	Casa cExEarly1("Strada Luminii", 2, 200, 2011);
	cout << cExEarly << endl;
	cout << cExEarly1 << endl;


	//late binding--legatura intarziata--apare la mom executarii codului
	//late bonding se demonstreaza cu fctii virtuale si pointeri

	Casa* pc = new Casa(c2);
	Casa* pc1 = new Vila(v2);

	cout << pc->tipImobil() << endl;
	cout << pc->tipClasa() << endl;
	cout << endl << endl;

	cout << pc1->tipImobil() << endl;
	cout << pc1->tipClasa() << endl;

	//functie template
	afisareObiectSauValoare(22);
	afisareObiectSauValoare(22.5);
	afisareObiectSauValoare("Maria");
	string text = "Ce vreti voi";
	afisareObiectSauValoare(text);
	afisareObiectSauValoare(c1);
	afisareObiectSauValoare(v1);
}