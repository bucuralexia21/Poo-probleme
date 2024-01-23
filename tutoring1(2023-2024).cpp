//PRINCIPIILE P.O.O

//1)Abstractizare -> reprezinta procesul de transpunere(tranzitie) a unui obiect din realitate in linii de cod

//2)Incapsulare -> Ofera protectie datelor din zona privata a clasei
// (practic limiteaza accesul din exterior asupra atributelor din clasa)

//3)Polimorfism

//4)Mostenire

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

//clasa se formeaza de la cuvantul cheie "class" si se defineste ca fiind o structura mai avansata (deoarece va contine si metode)

//atributul constant--> este un atribut a carui valoare nu se schimba niciodata in timpul executiei programului
// atributul constant este initializat la momentul crearii obiectului
//static --> reprezinta un atribut a caruit valoare va fi la fel pentru toate obiectele create


//TIPURI DE DATA:
//int --> 4bytes/ 4 octeti
//bool --> 1 byte/ 1 octet
//char --> 1 byte/1 octet
//string -->stocam o colectie de caractere --> 40 bytes/ 40 octeti
//float -->4 bytes/ 4 octeti
//double --> 8 bytes/ 8 octeti

//POINTERI --> stocheaza o adresa
//putem crea pointer pentru orice tip de data 
//cat ocupa un pointer? --> orice pointer ocupa 4 bytes/ 4 octeti -> adresa este numar intreg

//enum -> enumeratie

enum Categorie{ Lactate, Carne, ProdusePanificatie, Dulciuri, Bauturi, LegumeSiFructe };

class conditiePastrare {
public:
	virtual string afiseazaUnMesaj() = 0;
};

//modificatori de acces din clasa sunt : private,public si protected
class Produs:public conditiePastrare {
protected:
	//denumire,cantitate,pret, codDeBare, id, producator , reteta(ingrediente si cantitatea aferenta),categorie, nrKcal, daca este bio
	const int idProdus;
	static int nrProduse;
	const string codDeBare;//"9831234134";
	static int procentTVA;
	char* numeProdus;
	string producator;
	char taraProducatoare[50];
	Categorie catAliment;
	float pret;
	int dataExpirare[3];
	int nrKcal;
	int nrIngrediente;
	string* denumireIngrediente;
	float* cantitateIngrediente;
	bool esteBio;
public:
	//constructorii sunt functii/metode care nu au tip returnat, 
	//au acelasi nume ca si clasa si se ocupa de crearea si initializarea atribuelor dintr-o clasa


	//exista 3 tipuri de constructori:
	//1) constructor fara parametri(implicit, default, se mai numeste si null(?))
	Produs() :idProdus(nrProduse++), codDeBare("000000") {
		//in constructorul fara parametri, dam valori nule la pointeri(in afara de char*)
		//la atributele numerice(int,float,double, bool) dam 0;
		// iar la string si char* punem si noi o denumire
		this->numeProdus = new char[strlen("NuStim") + 1];//aici alocam spatiu, iar +1 este pentru terminatorul de sir
		strcpy(this->numeProdus, "NuStim");
		this->producator = "Anonim";
		strcpy(this->taraProducatoare, "Necunoscuta");
		this->catAliment = Lactate;
		this->pret = 0;
		this->dataExpirare[0] = 1;
		this->dataExpirare[1] = 1;
		this->dataExpirare[2] = 2024;
		this->nrKcal = 0;
		this->nrIngrediente = 0;
		this->denumireIngrediente = NULL;
		this->cantitateIngrediente = NULL;
		this->esteBio = false;
	}


	//2) constructor cu parametri(de la 1 la N, unde N reprezinta numarul de atribute din clasa)
	
	Produs(string codDeBare, const char* numeProdus, string producator, const char* taraProducatoare, Categorie catAliment,
		float pret, int* dataExpirare, int nrKcal, int nrIngrediente, string* denumireIngrediente, float* cantitateIngrediente,
		bool esteBio) :idProdus(nrProduse++), codDeBare(codDeBare) {
		this->numeProdus = new char[strlen(numeProdus) + 1];//aici alocam spatiu, iar +1 este pentru terminatorul de sir
		strcpy(this->numeProdus, numeProdus);
		this->producator = producator;
		strcpy(this->taraProducatoare, taraProducatoare);
		this->catAliment = catAliment;
		this->pret = pret;
		for (int i = 0; i < 3; i++)
		{
			this->dataExpirare[i] = dataExpirare[i];
		}
		this->nrKcal = nrKcal;
		this->nrIngrediente = nrIngrediente;
		this->denumireIngrediente = new string[this->nrIngrediente];
		this->cantitateIngrediente = new float[this->nrIngrediente];

		for (int i = 0; i < this->nrIngrediente; i++) {
			this->denumireIngrediente[i] = denumireIngrediente[i];
		}

		for (int i = 0; i < this->nrIngrediente; i++) {
			this->cantitateIngrediente[i] = cantitateIngrediente[i];
		}
		this->esteBio = esteBio;
	}


	//3) constructorul de copiere --> se apleaza atunci cand vrem sa cream un obiect nou pe baza altuia deja existent
	Produs(const Produs& p):idProdus(p.idProdus),codDeBare(p.codDeBare) {
		this->numeProdus = new char[strlen(p.numeProdus) + 1];//aici alocam spatiu, iar +1 este pentru terminatorul de sir
		strcpy(this->numeProdus, p.numeProdus);
		this->producator = p.producator;
		strcpy(this->taraProducatoare, p.taraProducatoare);
		this->catAliment = p.catAliment;
		this->pret = p.pret;
		for (int i = 0; i < 3; i++)
		{
			this->dataExpirare[i] = p.dataExpirare[i];
		}
		this->nrKcal = p.nrKcal;
		this->nrIngrediente = p.nrIngrediente;
		this->denumireIngrediente = new string[this->nrIngrediente];
		this->cantitateIngrediente = new float[this->nrIngrediente];

		for (int i = 0; i < this->nrIngrediente; i++) {
			this->denumireIngrediente[i] = p.denumireIngrediente[i];
		}

		for (int i = 0; i < this->nrIngrediente; i++) {
			this->cantitateIngrediente[i] = p.cantitateIngrediente[i];
		}
		this->esteBio = p.esteBio;
	}

	//destrucotrul
	~Produs() {
		if (this->numeProdus != NULL) {
			delete[]this->numeProdus;
		}

		if (this->denumireIngrediente != NULL) {
			delete[]this->denumireIngrediente;
		}
		if (this->cantitateIngrediente != NULL) {
			delete[]this->cantitateIngrediente;
		}
	}


	//operator = ->> se apeleaza intre doua obiecte deja existente
	//operator = se compune din ceea ce am scris in destructor + ceea ce am scris in constructorul de copiere + return *this;
	Produs& operator=(const Produs& p) {
		if (this != &p) {
			if (this->numeProdus != NULL) {
				delete[]this->numeProdus;
			}

			if (this->denumireIngrediente != NULL) {
				delete[]this->denumireIngrediente;
			}
			if (this->cantitateIngrediente != NULL) {
				delete[]this->cantitateIngrediente;
			}

			this->numeProdus = new char[strlen(p.numeProdus) + 1];//aici alocam spatiu, iar +1 este pentru terminatorul de sir
			strcpy(this->numeProdus, p.numeProdus);
			this->producator = p.producator;
			strcpy(this->taraProducatoare, p.taraProducatoare);
			this->catAliment = p.catAliment;
			this->pret = p.pret;
			for (int i = 0; i < 3; i++)
			{
				this->dataExpirare[i] = p.dataExpirare[i];
			}
			this->nrKcal = p.nrKcal;
			this->nrIngrediente = p.nrIngrediente;
			this->denumireIngrediente = new string[this->nrIngrediente];
			this->cantitateIngrediente = new float[this->nrIngrediente];

			for (int i = 0; i < this->nrIngrediente; i++) {
				this->denumireIngrediente[i] = p.denumireIngrediente[i];
			}

			for (int i = 0; i < this->nrIngrediente; i++) {
				this->cantitateIngrediente[i] = p.cantitateIngrediente[i];
			}
			this->esteBio = p.esteBio;
		}
		return *this;
	}





	//getteri -> functii/metode de acces(functii/metode accesor) cu ajutorul carora putem obtine/extrage valoarea unui atribut din clasa

	/* sablon pt getteri

		tipDeDataAtribut getNumeAtribut(){
			return this->numeAtribut;
		}
	*/

	const int getIdProdus() {
		return this->idProdus;
	}

	const string getCodDeBare() {
		return this->codDeBare;
	}

	//functiile statice si friend nu primesc pointerul this
	static int getNrProduse() {
		return Produs::nrProduse;
	}

	static int getProcentTVA() {
		return Produs::procentTVA;
	}

	const char* getNumeProdus() {
		return this->numeProdus;
	}

	string getProducator() {
		return this->producator;
	}

	char* getTaraProducatoare() {
		return this->taraProducatoare;
	}

	string getDenumireCatAliment() {
		if (this->catAliment == Lactate) {
			return "Lactate";
		}
		else if (this->catAliment == Carne) {
			return "Carne";
		}
		else if (this->catAliment == ProdusePanificatie) {
			return "ProdusePanificatie";
		}
		else if (this->catAliment == Dulciuri) {
			return "Dulciuri";
		}
		else if (this->catAliment == Bauturi) {
			return "Bauturi";
		}
		else if (this->catAliment == LegumeSiFructe) {
			return "LegumeSiFructe";
		}

	}

	Categorie getCatAliment() {
		return this->catAliment;
	}

	float getPret() {
		return this->pret;
	}

	int* getDataExpirare() {
		return this->dataExpirare;
	}

	int getNrKcal()
	{
		return this->nrKcal;
	}

	int getNrIngrediente() {
		return this->nrIngrediente;
	}

	string* getDenumireIngrediente() {
		return this->denumireIngrediente;
	}

	float* getCantitateIngrediente() {
		return this->cantitateIngrediente;
	}

	bool getEsteBio() {
		return this->esteBio;
	}



	//setteri -> functii/metode de acces(functii/metode accesor) cu ajutorul carora putem modifica valoarea unui atribut din clasa
	//tipul de data la setteri este intotdeauna VOID deoarece doar modifica valoarea, nu returneaza nimic
	//nu putem face setter pentru atributele constate si/sau statice
	//la pointeri intai dezalocam in setteri si apoi alocam iar memorie
		/* sablon pt setteri

			void setNumeAtribut(tipAtribut numeAtribut){
				this->numeAtribut = numeAtribut;
			}
		*/
	void setNumeProdus(const char* numeProdus) {
		if (numeProdus != NULL) {
			if (strlen(numeProdus) >= 3) {
				if (this->numeProdus != NULL) {
					delete[]this->numeProdus;
				}
				this->numeProdus = new char[strlen(numeProdus) + 1];
				strcpy(this->numeProdus, numeProdus);
			}
		}
	}


	void setProducator(string producator) {
		if (producator.size() >= 3) {
			this->producator = producator;
		}
	}

	void setCatAliment(Categorie catAliment) {
		this->catAliment = catAliment;
	}

	void setPret(float pret) {
		if (pret > 0 && pret <= 9999) {
			this->pret = pret;
		}
	}

	void setDataExpirare(int* dataExpirare) {
		if (dataExpirare != NULL) {
			for (int i = 0; i < 3; i++) {
				this->dataExpirare[i] = dataExpirare[i];
			}
		}
	}

	void setNrKcal(int nrKcal) {
		if (nrKcal > 0) {
			this->nrKcal = nrKcal;
		}
	}

	void setIngrediente(int nrIngrediente, string* denumireIngrediente, float* cantitateIngrediente) {
		if (nrIngrediente > 0 && denumireIngrediente != NULL && cantitateIngrediente != NULL) {
			this->nrIngrediente = nrIngrediente;
			if (this->denumireIngrediente != NULL) {
				delete[]this->denumireIngrediente;
			}
			if (this->cantitateIngrediente != NULL) {
				delete[]this->cantitateIngrediente;
			}
			this->denumireIngrediente = new string[this->nrIngrediente];
			this->cantitateIngrediente = new float[this->nrIngrediente];

			for (int i = 0; i < this->nrIngrediente; i++) {
				this->denumireIngrediente[i] = denumireIngrediente[i];
			}

			for (int i = 0; i < this->nrIngrediente; i++) {
				this->cantitateIngrediente[i] = cantitateIngrediente[i];
			}
		}
	}

	void setEsteBio(bool esteBio) {
		this->esteBio = esteBio;
	}


	//METODE


	//1)SUMA CANTITATILOR DE  INGREDIENTE
	float sumaCantitatiIngrediente(/* *this */) {
		float suma = 0;
		if (this->nrIngrediente > 0 && this->cantitateIngrediente != NULL) {
			for (int i = 0; i < this->nrIngrediente; i++) {
				suma += this->cantitateIngrediente[i];
			}
		}

		return suma;
	}
	

	//2)Medie cantitati ingrediente
	float medieCantitati() {
		//return this->sumaCantitatiIngrediente() / this->nrIngrediente;
		float suma = 0;
		if (this->nrIngrediente > 0 && this->cantitateIngrediente != NULL) {
			for (int i = 0; i < this->nrIngrediente; i++) {
				suma += this->cantitateIngrediente[i];
			}
		}
		return suma / this->nrIngrediente;

		
	}

	//3)Minim cantitati ingrediente
	float minimCantitate() {
		if (this->nrIngrediente > 0 && this->cantitateIngrediente != NULL) {
			float minim = this->cantitateIngrediente[0];
			for (int i = 1; i < this->nrIngrediente; i++) {
				if (minim > this->cantitateIngrediente[i]) {
					minim = this->cantitateIngrediente[i];
				}
			}
			return minim;
		}
		else {
			return 0;
		}
	}

	//4)Maxim cantitati ingrediente
	float maximCantitate() {
		if (this->nrIngrediente > 0 && this->cantitateIngrediente != NULL) {
			float maxim = this->cantitateIngrediente[0];
			for (int i = 1; i < this->nrIngrediente; i++) {
				if (this->cantitateIngrediente[i] >= maxim) {
					maxim = this->cantitateIngrediente[i];
				}
			}
			return maxim;
		}
		else {
			return 0;
		}
	}

	//5) CREATI O FUNCTIE CARE SA ADAUGE UN NOU INGREDIENT IN PRODUS, DACA INGREDIENTUL EXISTA, ADAUGATI CANTITATEA LA CEA EXISTENTA
	void adaugaIngredient(string denumire, float cantitate) {
		if (cantitate > 0) {
			bool gasit = 0;//cautam sa vedem daca exista ingredientul cautat in Produs
			int pozGasit = 0;
			for (int i = 0; i < this->nrIngrediente; i++) {
				if (this->denumireIngrediente[i] == denumire) {
					gasit = 1;
					pozGasit = i;
				}
			}
			if (gasit == 1) {
				this->cantitateIngrediente[pozGasit] += cantitate;
			}
			else {
				Produs copie = *this;
				this->nrIngrediente++;
				if (this->denumireIngrediente != NULL) {
					delete[]this->denumireIngrediente;
				}
				if (this->cantitateIngrediente != NULL) {
					delete[]this->cantitateIngrediente;
				}
				this->denumireIngrediente = new string[this->nrIngrediente];
				this->cantitateIngrediente = new float[this->nrIngrediente];

				for (int i = 0; i < copie.nrIngrediente; i++) {
					this->denumireIngrediente[i] = copie.denumireIngrediente[i];
				}

				for (int i = 0; i < copie.nrIngrediente; i++) {
					this->cantitateIngrediente[i] = copie.cantitateIngrediente[i];
				}

				this->denumireIngrediente[this->nrIngrediente - 1] = denumire;
				this->cantitateIngrediente[this->nrIngrediente - 1] = cantitate;
			}
		}
		
	}

	//6)CREATI O FUNCTIE CARE SA ELIMINE INGREDIENTUL CAUTAT
	void eliminaIngredient(string denumire) {
		bool gasit = 0;//cautam sa vedem daca exista ingredientul cautat in Produs
		//int pozGasit = 0;
		for (int i = 0; i < this->nrIngrediente; i++) {
			if (this->denumireIngrediente[i] == denumire) {
				gasit = 1;
				//pozGasit = i;
			}
		}
		if (gasit == 1) {
			Produs copie = *this;
			this->nrIngrediente--;
			if (this->denumireIngrediente != NULL) {
				delete[]this->denumireIngrediente;
			}
			if (this->cantitateIngrediente != NULL) {
				delete[]this->cantitateIngrediente;
			}
			this->denumireIngrediente = new string[this->nrIngrediente];
			this->cantitateIngrediente = new float[this->nrIngrediente];

			int pozitie = 0;
			for (int i = 0; i < copie.nrIngrediente; i++) {
				if (copie.denumireIngrediente[i] != denumire) {
					this->denumireIngrediente[pozitie] = copie.denumireIngrediente[i];
					this->cantitateIngrediente[pozitie] = copie.cantitateIngrediente[i];
					pozitie++;
				}
			}
		}
	}


	//7)Creati o functie care sa scada cantitatea dintr-un anumit Ingredient
	void scadereCantitateIngredient(string denumire, float cantitate) {
		bool gasit = 0;//cautam sa vedem daca exista ingredientul cautat in Produs
		//int pozGasit = 0;
		for (int i = 0; i < this->nrIngrediente; i++) {
			if (this->denumireIngrediente[i] == denumire) {
				gasit = 1;
				if (this->cantitateIngrediente[i] <= cantitate) {
					this->eliminaIngredient(denumire);
				}
				else {
					this->cantitateIngrediente[i] -= cantitate;
				}
			}
		}
	}
	//operatorii care au nevoie de friend sunt operatorii care au nevoie de doi operanzi pentru a fi implementati, 
	// iar cel din stanga operatului este de al tip decat cel al clasei in care implementam operatorul
	friend ostream& operator<<(ostream& out, const Produs& p) {
		out << p.idProdus << endl;
		out << p.codDeBare << endl;
		out << p.numeProdus << endl;
		out << p.producator << endl;
		out << p.taraProducatoare << endl;
		//out << p.catAliment << endl;
		if (p.catAliment == Lactate) {
			out << "Lactate" << endl;
		}
		else if (p.catAliment == Carne) {
			out << "Carne" << endl;
		}
		else if (p.catAliment == ProdusePanificatie) {
			out << "ProdusePanificatie" << endl;
		}
		else if (p.catAliment == Dulciuri) {
			out << "Dulciuri" << endl;
		}
		else if (p.catAliment == Bauturi) {
			out << "Bauturi" << endl;
		}
		else if (p.catAliment == LegumeSiFructe) {
			out << "LegumeSiFructe" << endl;
		}

		out << p.pret << endl;
		out << p.dataExpirare[0]<<"/"<< p.dataExpirare[1]<<"/"<<p.dataExpirare[2] << endl;
		out << p.nrKcal << endl;
		out << p.nrIngrediente << endl;
		for (int i = 0; i < p.nrIngrediente; i++) {
			out << p.denumireIngrediente[i] << " ,";
		}
		cout << endl;
		for (int i = 0; i < p.nrIngrediente; i++) {
			out << p.cantitateIngrediente[i] << " grame,";
		}
		out << endl;
		out << p.esteBio << endl;
		return out;
	}

	//operator >>
	// in operatorul >>, ca si in setteri, nu citim atributele const si/sau static
	//in operatorul >>, ca si in setteri, trebuie sa dezalocam intai atributele alocate dinamic si apoi trebuie sa alocam iar
	friend istream& operator>>(istream& in, Produs& p) {
		//asa citim un char* 
		cout << "Introduceti numele produsului: ";
		char aux[100];
		//in >> aux; asa citim pana la primul spatiu
		//asa citim pana la enter
		//in >> ws;
		in.getline(aux, 99);
		if (p.numeProdus != NULL) {
			delete[]p.numeProdus;
		}
		p.numeProdus = new char[strlen(aux) + 1];
		strcpy(p.numeProdus, aux);


		//asa citim un string;
		cout << "Introduceti producatorul produsului: ";
		//in >> ws;
		getline(in, p.producator);
	

		//asa citim un char static
		cout << "Introduceti tara produsului: ";
		//in >> ws;
		in.getline(p.taraProducatoare, 49);


		//asa citim un enum
		cout << "Introduceti categoria dorita: (Introduceti numarul dorit -> 0. Lactate, 1.Carne, 2.ProdusePanificatie, 3.Dulciuri, 4.Bauturi, 5.LegumeSiFructe ): ";
		int optEnum = 0;
		in >> optEnum;
		if (optEnum == 0) {
			p.catAliment = Lactate;
		}
		else if (optEnum == 1 ) {
			p.catAliment = Carne;
		}
		else if (optEnum == 2) {
			p.catAliment = ProdusePanificatie;
		}
		else if (optEnum ==3) {
			p.catAliment = Dulciuri;
		}
		else if (optEnum ==4) {
			p.catAliment = Bauturi;
		}
		else if (optEnum ==5) {
			p.catAliment = LegumeSiFructe;
		}
		//asa citim un numeric
		cout << "Introduceti pret: ";
		in >> p.pret;

		cout << "Introduceti ziua de expirare: ";
		in >> p.dataExpirare[0];
		cout << "Introduceti luna de expirare: ";
		in >> p.dataExpirare[1];
		cout << "Introduceti anul de expirare: ";
		in >> p.dataExpirare[2];

		cout << "Introduceti numarul de calorii: ";
		in >> p.nrKcal;

		cout << "Introduceti numarul de ingrediente: ";
		in >> p.nrIngrediente;
		if (p.cantitateIngrediente != NULL) {
			delete[]p.cantitateIngrediente;
		}
		if (p.denumireIngrediente != NULL) {
			delete[]p.denumireIngrediente;
		}

		p.denumireIngrediente = new string[p.nrIngrediente];
		p.cantitateIngrediente = new float[p.nrIngrediente];

		cout << "Introduceti denumirea ingredientelor: ";
		for (int i = 0; i < p.nrIngrediente; i++) {
			//in >> p.denumireIngrediente[i];
			in >> ws;
			getline(in, p.denumireIngrediente[i]);
		}

		cout << "Introduceti cantitatea ingredientelor: ";
		for (int i = 0; i < p.nrIngrediente; i++) {
			in >> p.cantitateIngrediente[i];
		}

		cout << "Este bio?(1-Da sau 0-Nu): ";
		in >> p.esteBio;
		return in;
	}

	//PT citirea din/in fisiere avem nevoie de ofstream is ifstream, care sunt de fapt ostream si istream fara texte aditionale si fara atribute const/static

	friend ofstream& operator<<(ofstream& out, const Produs& p) {
		out << p.numeProdus << endl;
		out << p.producator << endl;
		out << p.taraProducatoare << endl;
		out << p.catAliment << endl;
		out << p.pret << endl;
		out << p.dataExpirare[0] << endl << p.dataExpirare[1] << endl << p.dataExpirare[2] << endl;
		out << p.nrKcal << endl;
		out << p.nrIngrediente << endl;
		for (int i = 0; i < p.nrIngrediente; i++) {
			out << p.denumireIngrediente[i] << endl;
		}
		for (int i = 0; i < p.nrIngrediente; i++) {
			out << p.cantitateIngrediente[i] << endl;
		}
		out << p.esteBio << endl;
		return out;
	}

	//operator >>
	// in operatorul >>, ca si in setteri, nu citim atributele const si/sau static
	//in operatorul >>, ca si in setteri, trebuie sa dezalocam intai atributele alocate dinamic si apoi trebuie sa alocam iar
	friend ifstream& operator>>(ifstream& in, Produs& p) {
		char aux[100];
		in.getline(aux, 99);
		if (p.numeProdus != NULL) {
			delete[]p.numeProdus;
		}
		p.numeProdus = new char[strlen(aux) + 1];
		strcpy(p.numeProdus, aux);
		getline(in, p.producator);
		in.getline(p.taraProducatoare, 49);
		int optEnum = 0;
		in >> optEnum;
		if (optEnum == 0) {
			p.catAliment = Lactate;
		}
		else if (optEnum == 1) {
			p.catAliment = Carne;
		}
		else if (optEnum == 2) {
			p.catAliment = ProdusePanificatie;
		}
		else if (optEnum == 3) {
			p.catAliment = Dulciuri;
		}
		else if (optEnum == 4) {
			p.catAliment = Bauturi;
		}
		else if (optEnum == 5) {
			p.catAliment = LegumeSiFructe;
		}
		in >> p.pret;
		in >> p.dataExpirare[0];
		in >> p.dataExpirare[1];
		in >> p.dataExpirare[2];
		in >> p.nrKcal;
		in >> p.nrIngrediente;
		if (p.cantitateIngrediente != NULL) {
			delete[]p.cantitateIngrediente;
		}
		if (p.denumireIngrediente != NULL) {
			delete[]p.denumireIngrediente;
		}
		p.denumireIngrediente = new string[p.nrIngrediente];
		p.cantitateIngrediente = new float[p.nrIngrediente];
		for (int i = 0; i < p.nrIngrediente; i++) {
			in >> ws;
			getline(in, p.denumireIngrediente[i]);
		}
		for (int i = 0; i < p.nrIngrediente; i++) {
			in >> p.cantitateIngrediente[i];
		}
		in >> p.esteBio;
		return in;
	}


	//serializare ---> transformarea unui obiect intr-o secventa de biti
	void serializare(string numeFisier) {
		ofstream f(numeFisier, ios::out | ios::binary);
		//asa scriem un char* 
		int dimNume = strlen(this->numeProdus);
		f.write((char*)&dimNume, sizeof(dimNume));
		f.write(this->numeProdus, dimNume + 1);

		//asa scriem un string
		int dimProducator = this->producator.size();
		f.write((char*)&dimProducator, sizeof(dimProducator));
		f.write(this->producator.c_str(), dimProducator + 1);
		
		//asa scriem un char static
		int dimTara = strlen(this->taraProducatoare);
		f.write((char*)&dimTara, sizeof(dimTara));
		f.write(this->taraProducatoare, dimTara + 1);


		//asa scriem un enum 
		f.write((char*)&this->catAliment, sizeof(catAliment));

		//asa scriem numerice
		f.write((char*)&this->pret, sizeof(pret));
		for (int i = 0; i < 3; i++) {
			f.write((char*)&this->dataExpirare[i], sizeof(dataExpirare[i]));
		}
		f.write((char*)&this->nrKcal, sizeof(nrKcal));
		f.write((char*)&this->nrIngrediente, sizeof(nrIngrediente));
		//asa scriem un string *
		for (int i = 0; i < this->nrIngrediente; i++) {
			int dimDenumIngredient = this->denumireIngrediente[i].size();
			f.write((char*)&dimDenumIngredient, sizeof(dimDenumIngredient));
			f.write(this->denumireIngrediente[i].c_str(), dimDenumIngredient + 1);
		}
		//asa scriem un numeric*
		for (int i = 0; i < this->nrIngrediente; i++) {
			f.write((char*)&this->cantitateIngrediente[i], sizeof(cantitateIngrediente[i]));

		}
		f.write((char*)&this->esteBio, sizeof(esteBio));
		cout << "Fisierul a fost scris in Binar!" << endl;
		f.close();
	
	}


	//deserializare ---> restaurarea unui obiect dintr-o secventa de biti
	void deserializare(string numeFisier) {
		ifstream f(numeFisier, ios::out | ios::binary);
		if(f.is_open())
		{
			//asa citim un char* 
			if (this->numeProdus != NULL) {
				delete[]this->numeProdus;
			}
			int dimNume = 0;
			f.read((char*)&dimNume, sizeof(dimNume));
			this->numeProdus = new char[dimNume + 1];
			f.read(this->numeProdus, dimNume + 1);

			//asa citim un string
			int dimProducator = 0;
			f.read((char*)&dimProducator, sizeof(dimProducator));
			char* aux = new char[dimProducator + 1];
			f.read(aux, dimProducator + 1);
			this->producator = aux;
			delete[]aux;

			//asa citim un char static
			int dimTara = 0;
			f.read((char*)&dimTara, sizeof(dimTara));
			f.read(this->taraProducatoare, dimTara + 1);


			//asa citim un enum 
			f.read((char*)&this->catAliment, sizeof(catAliment));

			//asa citim numerice
			f.read((char*)&this->pret, sizeof(pret));
			for (int i = 0; i < 3; i++) {
				f.read((char*)&this->dataExpirare[i], sizeof(dataExpirare[i]));
			}
			f.read((char*)&this->nrKcal, sizeof(nrKcal));
			f.read((char*)&this->nrIngrediente, sizeof(nrIngrediente));
			//asa citim un string *
			if (this->denumireIngrediente != NULL) {
				delete[]this->denumireIngrediente;
			}
			this->denumireIngrediente = new string[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++) {
				int dimDenumIngredient = 0;
				f.read((char*)&dimDenumIngredient, sizeof(dimDenumIngredient));
				char* aux1 = new char[dimDenumIngredient + 1];
				f.read(aux1, dimDenumIngredient + 1);
				this->denumireIngrediente[i] = aux1;
				delete[]aux1;
			}
			//asa citim un numeric*
			if (this->cantitateIngrediente != NULL) {
				delete[]this->cantitateIngrediente;
			}
			this->cantitateIngrediente = new float[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++) {
				f.read((char*)&this->cantitateIngrediente[i], sizeof(cantitateIngrediente[i]));

			}
			f.read((char*)&this->esteBio, sizeof(esteBio));
			cout << "Fisierul a fost citit din Binar!" << endl;
			f.close();
		}
		else {
			cout << "Fisierul binar cautat nu exista!" << endl;
		}

	}


	
	float zileRamasePanaLaExpirare(){
		int zi = 19;
		int luna = 1;
		int an = 2024;
	
		int zileRamasePanaLaExpirare = 0;
		zileRamasePanaLaExpirare =  dataExpirare[0] + dataExpirare[1]*12 + dataExpirare[2] * 365 - (2024 * 365 + 1 * 30 + 19);
		if (zileRamasePanaLaExpirare < 0) {
			return 0;
		}
		else {
			return zileRamasePanaLaExpirare;
		}
	}

	 virtual string returneazaTipClasa() {
		return "Este un simplu Produs!";
	 }

	 int intoareceValoare() {
		 return 1;
	 }

	 string afiseazaUnMesaj() {
		 return "Acest produs se pastreaza in conditii normale!";
	 }
};
//char* numeProdus;
//string producator;
//char taraProducatoare[50];
//Categorie catAliment;
//float pret;
//int dataExpirare[3];
//int nrKcal;
//int nrIngrediente;
//string* denumireIngrediente;
//float* cantitateIngrediente;
//bool esteBio;



//atributele statice se initializeaza in afara clasei
int Produs::nrProduse = 1;
int Produs::procentTVA = 17;

void utilizareGetteri(Produs p) {
	cout << endl << endl << endl << endl;
	cout << "Getteri" << endl << endl;
	cout << p.getIdProdus() << endl;
	cout << p.getCodDeBare() << endl;
	cout << p.getNumeProdus() << endl;
	cout << p.getProducator() << endl;
	cout << p.getTaraProducatoare() << endl;
	cout << p.getCatAliment() << endl;
	//cout << p.getDenumireCatAliment() << endl;
	cout << p.getPret() << endl;
	//cout << p.getDataExpirare() << endl;//aici este vector si afiseaza adresa
	for (int i = 0; i < 3; i++) {
		cout << p.getDataExpirare()[i] << "/";
	}
	cout << endl;
	cout << p.getNrKcal() << endl;
	cout << p.getNrIngrediente() << endl;
	for (int i = 0; i < p.getNrIngrediente(); i++) {
		cout << p.getDenumireIngrediente()[i] << " ,";
	}
	cout << endl;
	for (int i = 0; i < p.getNrIngrediente(); i++) {
		cout << p.getCantitateIngrediente()[i] << " grame,";
	}
	cout << endl;
	//cout << p.getDenumireIngrediente() << endl;//aici este vector si afiseaza adresa
	//cout << p.getCantitateIngrediente() << endl;//aici este vector si afiseaza adresa
	cout << p.getEsteBio() << endl;

	cout << endl << endl << endl << endl;
}



//MOSTENIRE ESTE IS A ->> DERIVATI CLASA / SPECIALIZATI CLASA


class ProdusCongelat: public Produs{
	int nrPortii;
	float temperaturaCongelare;
public:
	
	ProdusCongelat() :Produs() {
		this->nrPortii = 0;
		this->temperaturaCongelare = 0.0;
	}


	ProdusCongelat(string codDeBare, const char* numeProdus, string producator, const char* taraProducatoare, Categorie catAliment,
		float pret, int* dataExpirare, int nrKcal, int nrIngrediente, string* denumireIngrediente, float* cantitateIngrediente,
		bool esteBio,int nrPortii, float temperaturaCongelare)
		:Produs(codDeBare, numeProdus,producator,taraProducatoare,catAliment,pret,dataExpirare, nrKcal,nrIngrediente,denumireIngrediente,cantitateIngrediente,esteBio) {
		this->nrPortii = nrPortii;
		this->temperaturaCongelare = temperaturaCongelare;
	}

	ProdusCongelat(const ProdusCongelat& pc) :Produs(pc) {
		this->nrPortii = pc.nrPortii;
		this->temperaturaCongelare = pc.temperaturaCongelare;
	}
	~ProdusCongelat() {

	}

	ProdusCongelat& operator=(const ProdusCongelat& pc) {
		if (this != &pc) {
			Produs::operator=(pc);
			this->nrPortii = pc.nrPortii;
			this->temperaturaCongelare = pc.temperaturaCongelare;
		}
		return *this;
	}

	//down-casting
	ProdusCongelat(const Produs& p) :Produs(p) {
		this->nrPortii = 12;
		this->temperaturaCongelare = -56.12;
	}

	friend ostream& operator<<(ostream& out, const ProdusCongelat& pc) {
		out << (Produs&)pc;
		out << pc.nrPortii << endl;
		out << pc.temperaturaCongelare << endl;
		return out;
	}

	 string returneazaTipClasa() {
		return "Este un produs congelat!";
	 }

	 int intoareceValoare() {
		 return 100;
	 }

	 string afiseazaUnMesaj() {
		 return "Acest produs se pastreaza in congelator, la -3 grade!";
	 }
};
int main() {
	Produs p;
	cout << endl << endl << endl << endl;
	cout << "Getteri" << endl << endl;
	cout << p.getIdProdus() << endl;
	cout << p.getCodDeBare() << endl;
	cout << p.getNumeProdus() << endl;
	cout << p.getProducator() << endl;
	cout << p.getTaraProducatoare() << endl;
	cout << p.getCatAliment() << endl;
	//cout << p.getDenumireCatAliment() << endl;
	cout << p.getPret() << endl;
	//cout << p.getDataExpirare() << endl;//aici este vector si afiseaza adresa
	for (int i = 0; i < 3; i++) {
		cout << p.getDataExpirare()[i] << "/";
	}
	cout << endl;
	cout << p.getNrKcal() << endl;
	cout << p.getNrIngrediente() << endl;
	for (int i = 0; i < p.getNrIngrediente(); i++) {
		cout << p.getDenumireIngrediente()[i] << " ,";
	}
	cout << endl;
	for (int i = 0; i < p.getNrIngrediente(); i++) {
		cout << p.getCantitateIngrediente()[i] << " grame,";
	}
	cout << endl;
	//cout << p.getDenumireIngrediente() << endl;//aici este vector si afiseaza adresa
	//cout << p.getCantitateIngrediente() << endl;//aici este vector si afiseaza adresa
	cout << p.getEsteBio() << endl;

	cout << endl << endl << endl << endl;
	cout << "Setteri" << endl << endl;
	p.setNumeProdus("7Days");
	p.setNumeProdus(NULL);
	p.setNumeProdus("7D");
	p.setProducator("Coca Colca Company");
	p.setProducator("Xu");
	p.setCatAliment(Bauturi);
	p.setPret(5000);
	p.setPret(-1000);
	p.setPret(99999999);
	int dataNouaExpirare[3] = { 11,12,2025 };
	p.setDataExpirare(dataNouaExpirare);
	p.setNrKcal(250);
	string vecIng[] = { "Apa", "Unt","Ciocolata","Lapte" };
	float cantIng[] = { 400,50,12.5,67.6,5.5 };
	p.setIngrediente(3, new string[3]{ "Apa", "Zahar","Faina" }, new float[3] {45.13, 11.1, 41.1});
	p.setIngrediente(4, vecIng, cantIng);
	p.setEsteBio(true);

	utilizareGetteri(p);


	int dataExpProd[] = { 23,4,2026 };
	string vecIng1[] = { "Apa", "Ciocolata Amaruie","Faina","Drojdie","Lapte","Nuca" };
	float cantIng1[] = { 400,67.6,41.1,44.6,580,410 };
	Produs p1("987011", "Cozonac Boromir", "Boromir", "Romania", ProdusePanificatie, 15.5, dataExpProd, 700, 6, vecIng1, cantIng1, 1);
	utilizareGetteri(p1);


	Produs p2 = p;
	utilizareGetteri(p2);


	p2 = p1;
	utilizareGetteri(p2);

	cout << endl << endl << endl << endl;
	cout << "----------------------------------------------" << endl;
	cout << "METODE" << endl << endl;
	cout << "Suma cantitati ingrediente: " << p2.sumaCantitatiIngrediente() << " grame" << endl;
	cout << "Medie cantitati ingrediente: " << p2.medieCantitati() << " grame" << endl;
	cout << "Maxim cantitati ingrediente: " << p2.maximCantitate() << " grame" << endl;
	cout << "Minim cantitati ingrediente: " << p2.minimCantitate() << " grame" << endl;
	cout << "Adauga Ingrediente: " << endl;
	utilizareGetteri(p2);
	p2.adaugaIngredient("Apa", 600);
	p2.adaugaIngredient("Vanilie", 2.5);
	utilizareGetteri(p2);

	cout << "Elimina Ingrediente: " << endl;

	p2.eliminaIngredient("Apa");
	p2.eliminaIngredient("Nuca");
	p2.eliminaIngredient("Lapte");
	utilizareGetteri(p2);

	p2.scadereCantitateIngredient("Faina", 10);
	utilizareGetteri(p2);


	p2.scadereCantitateIngredient("Faina", 500);
	utilizareGetteri(p2);

	cout << endl << endl << endl << endl;
	cout << "----------------------------------------------" << endl;
	cout << "OPERATORI" << endl << endl;
	cout << p1 << endl;


	//cin >> p1;
	//cout << endl << endl;
	//cout << p1 << endl << endl;


	cout << "----------------------------------------------" << endl;
	cout << "----------------------------------------------" << endl;
	cout << "OPERATII CU FISIER TEXT" << endl << endl;
	ofstream f("exempluScriere.txt", ios::out);
	f << p1;
	f.close();
	cout << "S-a scris in fisier produsul dorit!" << endl;
	cout << endl << endl;

	Produs pCititText;
	cout << pCititText << endl << endl;
	ifstream g("exempluscriere.txt", ios::in);
	if (g.is_open()) {
		g >> pCititText;
		cout << "Produsul a fost citit din fisier!" << endl;
		cout << pCititText<<endl<<endl;
	}
	else {
		cout << "Fisierul cautat nu exista!" << endl;
	}

	cout << "----------------------------------------------" << endl;
	cout << "----------------------------------------------" << endl;
	cout << "OPERATII CU FISIER BINARE" << endl << endl;
	p1.serializare("produs.bin");
	Produs pCititBinar;
	cout << pCititBinar << endl << endl;
	pCititBinar.deserializare("produs.bin");

	cout << pCititBinar << endl << endl;
	cout << "----------------------------------------------" << endl;
	int dataExp[] = { 1,1,2024 };
	Produs prodFil1("987011", "Cozonac Boromir", "Boromir", "Romania", ProdusePanificatie, 15.5, dataExp, 700, 6, vecIng1, cantIng1, 1);
	Produs prodFil2("987011", "Ciocolata Milka", "Boromir", "Romania", ProdusePanificatie, 15.5, dataExp, 700, 6, vecIng1, cantIng1, 1);
	Produs prodFil3("987011", "Bere Timisoreana", "Boromir", "Romania", ProdusePanificatie, 15.5, dataExpProd, 700, 6, vecIng1, cantIng1, 1);
	Produs prodFil4("987011", "Tuica de prune", "Boromir", "Romania", ProdusePanificatie, 15.5, dataExp, 700, 6, vecIng1, cantIng1, 1);
	Produs prodFil5("987011", "Rulada", "Boromir", "Romania", ProdusePanificatie, 15.5, dataExp, 700, 6, vecIng1, cantIng1, 1);
	Produs prodFil6("987011", "Inghetata", "Boromir", "Romania", ProdusePanificatie, 15.5, dataExpProd, 700, 6, vecIng1, cantIng1, 1);

	/*cout << p1.zileRamasePanaLaExpirare() << endl;
	cout << prodFil1.zileRamasePanaLaExpirare() << endl;
	cout << prodFil3.zileRamasePanaLaExpirare() << endl;*/

	Produs verificareProd[6] = { prodFil1,prodFil2,prodFil3,prodFil4,prodFil5,prodFil6 };
	ofstream f1("produseExpirare.txt", ios::out);
	ofstream f2("produseIncaInTermen.txt", ios::out);
	for (int i = 0; i < 6; i++) {
		if (verificareProd[i].zileRamasePanaLaExpirare() == 0) {
			f1 << verificareProd[i] << endl;
		}
		else {
			f2 << verificareProd[i] << endl;
		}
	}
	f1.close();
	f2.close();
	cout << "----------------------------------------------" << endl;
	cout << "MOSTENIRE/DERIVARE/SPECIALIZARE(IS A)" << endl << endl;
	ProdusCongelat pc;
	cout << pc<<endl << endl;

	ProdusCongelat pc1("987011", "Inghetata", "Boromir", "Romania", ProdusePanificatie, 15.5, dataExpProd, 700, 6, vecIng1, cantIng1, 1, 12, -30);
	
	cout << pc1 << endl << endl;

	ProdusCongelat pc2 = pc;
	cout << pc2 << endl << endl;

	pc2 = pc1;
	cout << pc2 << endl << endl;

	ProdusCongelat pc3 = prodFil1;

	cout << pc3 << endl << endl;

	Produs pUpCasting = pc3;

	cout << pUpCasting << endl << endl;
	cout << endl << endl << endl;
	cout << "----------------------------------------------" << endl;
	cout << "Early binding(legatura timpurie) " << endl << endl << endl;
	//early-binding--> apare inca din momentul compilarii programului
	//de atunci este stabilit tipul obiectului si care este metoda apelata
	//ex: constructori




	cout << "----------------------------------------------" << endl;
	cout << "FUNCTII VIRTUALE " << endl << endl << endl;

	//ce este supradefinirea(suprascrierea)?
	//Supradefinirea/suprascrierea consta in modificarea corpului unei functii(modificam instructiunile unei functii)

	//ce este supraincarcarea?
	//Permite schimbarea corpului functiei, dar si a logicii(parametrilor din lista parametrii)

	//FUNCTIILE VIRTUALE SE DEMONSTREAZA(SE ARATA ROLUL DOAR PRIN POINTERI LA OBIECTE)
	//FUNCTII VIRTUALE SE DEFINESC CU CUVANTUL CHEIE virtual in fata

	//permit redefinerea comportamentului unei functii din claza de baza, in clasa derivata
	//in momentul in care cream o functie virtuala, se creeaza o tabela  de pointeri in memorie(care contine adresa fiecare functii)

	//in momentul in care face o mostenire, se va mosteni si aceasta tabela de pointeri, nu doar atributele din clasa parinte

	//cand redefinim o metoda din clasa de baza, in clasa derivata, se va modifica si adresa din tabela de pointeri

	

	cout << "----------------------------------------------" << endl;
	cout << "Late binding(legatura intarziata) " << endl << endl << endl;
	//late-binding(este specifica pointerilor)
	//mai intai se verifica natura obiectului (daca este pointer sau nu)-> daca nu este pointer la clasa derivata, stie deja ce metoda trebuie apelata
	//daca este pointer la clasa derivata, trebuie sa verifice daca exista o tabela de functii,
	//verifica daca metoda este virtuala sau nu, daca metoda nu este virtuala, o afiseaza pe cea din clasa de baza
	//metoda este virtuala, verifica daca exista o modificare in tabela de pointeri din clasa derivata
	//daca nu exista o modificare, foloseste metoda din clasa de baza, daca exista o modificare foloseste metoda din clasa derivata.

	Produs exVirtP = pc3;
	ProdusCongelat exVirtPC = pc3;


	cout << exVirtP.returneazaTipClasa() << endl;
	cout << exVirtP.intoareceValoare() << endl;//1
	cout << endl;
	cout << exVirtPC.returneazaTipClasa() << endl;
	cout << exVirtPC.intoareceValoare() << endl;//100
	cout << endl << endl;

	Produs* pp = new Produs(pc3);
	Produs* pp1 = new ProdusCongelat(pc3);

	cout << endl << endl;
	cout << pp->intoareceValoare() << endl;//1
	cout << pp1->intoareceValoare() << endl;//1


	cout << endl << endl;
	cout << pp->returneazaTipClasa() << endl;//
	cout << pp1->returneazaTipClasa() << endl;//

	cout << endl << endl;
	conditiePastrare* cp = new Produs();
	conditiePastrare* cp1 = new ProdusCongelat();

	cout << cp->afiseazaUnMesaj() << endl;//
	cout << cp1->afiseazaUnMesaj() << endl;//
}


