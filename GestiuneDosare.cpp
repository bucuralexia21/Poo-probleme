#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include< string>
#include<fstream>
using namespace std;

class Dosar {
	int nrDosar;
	char* CV;
	string CI;
	bool modulPeda;
	bool esteDepus;
	static int nrDosare;
	static int aniVechime;

public:
	int getNrDosar()
	{
		return this->nrDosar;

	}

	char* getCV() {
		return this->CV;

	}
	string getCi()
	{
		return this->CI;

	}

	bool getModulPeda()
	{
		return this->modulPeda;
	}

	void setNrDosar(int nrNouDosar)
	{
		if (nrNouDosar < 0) {
			throw new exception("e negativ");
		}
		this->nrDosar = nrNouDosar;
	}

	void setCV(char* CVnou)
	{
		this->CV = new char[strlen(CVnou) + 1];
		strcpy(this->CV, CVnou);
	}

	void setCI(string CI)
	{
		this->CI = CI;
	}

	void setModulPeda(bool modulPedaNou) {
		this->modulPeda = modulPedaNou;
	}
	void setEsteDepus(bool esteDepus) {
		this->esteDepus = esteDepus;
	}

	Dosar() {
		this->nrDosar =0 ;
		this->CV = new char[strlen("anonim") + 1];
		strcpy(this->CV, "anonim");
		this->CI = "anonim";
		this->modulPeda = 0;
	}


	Dosar(int nrDosar,const char* CV,string CI,bool modulPeda) {
		this->nrDosar = nrDosar;
		this->CV = new char[strlen(CV) + 1];
		strcpy(this->CV, CV);
		this->CI = CI;
		this->modulPeda = modulPeda;
		if (this->esteDepus == 1) {
			nrDosare++;
		}
	}

	~Dosar()
	{
		if (this->CV != nullptr)
		{
			delete[]this->CV;
		}
	}

	friend ostream& operator<<(ostream& out, const Dosar& d)
	{
		out << "Numar dosar: " << d.nrDosar << endl;
		out << "CV: " << d.CV << endl;
		out << "CI: " << d.CI << endl;
		out << "modulPeda: " << d.modulPeda << endl;
		out << "ani Vechime: " << d.aniVechime << endl;
		return out;
	}

	void scriereFisierText(const char* numeFisier)
	{
		ofstream fout(numeFisier);
		fout << nrDosar << "\n";
		fout << CV << "\n";
		fout << CI << "\n";
		fout << modulPeda << "\n";
		fout << aniVechime << "\n";
		fout.close();
	}

	void citireFisier(const char* numeFisier)
	{
		ifstream fin(numeFisier);
		fin >> nrDosar;
		fin >> CV;
		fin >> CI;
		fin >> modulPeda;
		fin >> aniVechime;
		fin.close();
	}

	static int getNrDosare()
	{
		return nrDosare;
	}
};
int Dosar::aniVechime = 2;
int Dosar::nrDosare = 0;

int main()
{
	try {
		Dosar d1(2, "CVAlexia", "6020", 1);
		cout << "Dosar 1: " << endl << d1 << endl;

		d1.scriereFisierText("dosare.txt");

		Dosar d2(3, "CVALEXIA2", "6020", 0);
		cout << d2 << endl;

		d2.citireFisier("dosare.txt");
		cout << "Dosar 2: " << endl << d2 << endl;

		d2.setEsteDepus(1);
		d1.setEsteDepus(1);

		cout << Dosar::getNrDosare() << endl;
	}
	catch (exception* e) {
		cout << e->what();
		delete e;
	}
}