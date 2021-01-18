#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <cassert>
using namespace std;

//---------------------------------------------------------------------------------------------------------------------------------------
//
//							CLASA CINEMA
//
//---------------------------------------------------------------------------------------------------------------------------------------

class Cinema
{
private:
	const int cod;
	static int cinema;
	char* denumire;
	int numarSali;
	int* sali;

public:
	Cinema() :cod(1)
	{
		this->denumire = new char[1];
		strcpy_s(this->denumire, 1, "");
		this->numarSali = 0;
		this->sali = nullptr;
	}

	Cinema(int cod, char* denumire, int numarSali, int* sali) :cod(cod)
	{
		if (denumire != nullptr)
		{
			int len = strlen(denumire) + 1;
			this->denumire = new char[len];
			strcpy_s(this->denumire, len, denumire);
		}
		else
		{
			this->denumire = new char[1];
			strcpy_s(this->denumire, 1, "");
		}
		
		if (numarSali > 0)
		{
			this->numarSali = numarSali;
			this->sali = new int[numarSali];
			for (int i = 0; i < numarSali; i++)
			{
				this->sali[i] = sali[i];
			}
		}
		else
		{
			this->numarSali = 0;
			this->sali = nullptr;
		}
	}

	Cinema(const Cinema& c) : cod(c.cod)
	{
		if (c.denumire != nullptr) 
		{
			int len = strlen(c.denumire) + 1;
			this->denumire = new char[len];
			strcpy_s(this->denumire, len, c.denumire);
		}
		else 
		{
			this->denumire = new char[1];
			strcpy_s(this->denumire, 1, "");
		}
		
		if (c.numarSali > 0 && c.sali != nullptr)
		{
			this->numarSali = c.numarSali;
			this->sali = new int[c.numarSali];
			for (int i = 0; i < c.numarSali; i++)
			{
				this->sali[i] = c.sali[i];
			}
		}
		else
		{
			this->numarSali = 0;
			this->sali = nullptr;
		}
	}

	Cinema operator=(Cinema c)
	{
		if (sali != nullptr) {
			delete[] sali;
		}

		if (denumire != nullptr) {
			delete[] denumire;
		}

		if (c.denumire != nullptr)
		{
			int len = strlen(c.denumire) + 1;
			this->denumire = new char[len];
			strcpy_s(this->denumire, len, c.denumire);
		}
		else
		{
			this->denumire = new char[1];
			strcpy_s(this->denumire, 1, "");
		}

		if (c.numarSali > 0 && c.sali != nullptr)
		{
			this->numarSali = c.numarSali;
			this->sali = new int[c.numarSali];
			for (int i = 0; i < c.numarSali; i++)
			{
				this->sali[i] = c.sali[i];
			}
		}
		else
		{
			this->numarSali = 0;
			this->sali = nullptr;
		}

		return *this;
	}

	~Cinema()
	{
		if (sali != nullptr)
		{
			delete[] sali;
		}
		delete[] denumire;
	}

	bool operator!()
	{
		return numarSali > 0;
	}

	bool operator==(char* denumire)
	{
		Cinema copy = *this;
		return (copy.denumire == denumire);
	}

	Cinema operator++()
	{
		this->numarSali++;
		return *this;
	}

	Cinema operator++(int i)
	{
		Cinema copy = *this;
		this->numarSali++;
		return copy;
	}

	Cinema operator+(int numarSaliAdd)
	{
		if (numarSaliAdd < 0)
		{
			throw 500;
		}
		else
		{
			Cinema copy = *this;
			copy.numarSali += numarSaliAdd;
			return copy;
		}
	}

	bool operator>(int numarSaliComp)
	{
		Cinema copy = *this;
		return (copy.numarSali > numarSaliComp);
	}

	int& operator[](int pozitie) throw (exception)
	{
		if (pozitie >= 0 && pozitie < numarSali && sali != nullptr)
		{
			return sali[pozitie];
		}
		else
		{
			throw exception("Pozitie invalida!");
		}
	}

	explicit operator int()
	{
		return numarSali;
	}

	static void setcinema(int cinema)
	{
		Cinema::cinema = cinema;
	}

	friend ostream& operator<<(ostream&, Cinema);
	friend istream& operator>>(istream&, Cinema&);

};

ostream& operator<<(ostream& out, Cinema c)
{
	if (c.denumire != nullptr)
	{
		out << "Denumire: " << c.denumire << endl;
	}
	out << "Numar sali: " << c.numarSali << endl;
	out << "sali: ";
	if (c.sali != nullptr)
	{
		for (int i = 0; i < c.numarSali; i++)
		{
			out << c.sali[i] << " ";
		}
	}
	return out;
}

istream& operator>> (istream& in, Cinema& c)
{
	delete[] c.denumire;
	char buffer[100];
	cout << "Denumire Cinema: ";
	in >> ws;
	in.getline(buffer, 99);
	c.denumire = new char[strlen(buffer) + 1];
	strcpy_s(c.denumire, strlen(buffer) + 1, buffer);


	if (c.sali != nullptr)
	{
		delete[] c.sali;
	}
	cout << "Numar sali: ";
	in >> c.numarSali;
	if (c.numarSali > 0)
	{
		c.sali = new int[c.numarSali];
		for (int i = 0; i < c.numarSali; i++)
		{
			cout << "Filmul[" << i << "] = ";
			in >> c.sali[i];
		}
	}
	else
	{
		c.numarSali = 0;
		c.sali = nullptr;
	}
	return in;
}


//---------------------------------------------------------------------------------------------------------------------------------------
//
//							CLASA RESTRICTII VARSTA
//
//---------------------------------------------------------------------------------------------------------------------------------------


class restrictiiVarsta
{
private:
	const int cod;
	static int cinema;
	char* denumire;
	int numarCategoriiVarsta;
	int* categoriiVarsta;

public:
	restrictiiVarsta() :cod(1)
	{
		this->denumire = new char[1];
		strcpy_s(this->denumire, 1, "");
		this->numarCategoriiVarsta = 0;
		this->categoriiVarsta = nullptr;
	}

	restrictiiVarsta(int cod, char* denumire, int numarCategoriiVarsta, int* categoriiVarsta) :cod(cod)
	{
		if (denumire != nullptr)
		{
			int len = strlen(denumire) + 1;
			this->denumire = new char[len];
			strcpy_s(this->denumire, len, denumire);
		}
		else
		{
			this->denumire = new char[1];
			strcpy_s(this->denumire, 1, "");
		}

		if (numarCategoriiVarsta > 0)
		{
			this->numarCategoriiVarsta = numarCategoriiVarsta;
			this->categoriiVarsta = new int[numarCategoriiVarsta];
			for (int i = 0; i < numarCategoriiVarsta; i++)
			{
				this->categoriiVarsta[i] = categoriiVarsta[i];
			}
		}
		else
		{
			this->numarCategoriiVarsta = 0;
			this->categoriiVarsta = nullptr;
		}
	}

	restrictiiVarsta(const restrictiiVarsta& rv) : cod(rv.cod)
	{
		if (rv.denumire != nullptr)
		{
			int len = strlen(rv.denumire) + 1;
			this->denumire = new char[len];
			strcpy_s(this->denumire, len, rv.denumire);
		}
		else
		{
			this->denumire = new char[1];
			strcpy_s(this->denumire, 1, "");
		}

		if (rv.numarCategoriiVarsta > 0 && rv.categoriiVarsta != nullptr)
		{
			this->numarCategoriiVarsta = rv.numarCategoriiVarsta;
			this->categoriiVarsta = new int[rv.numarCategoriiVarsta];
			for (int i = 0; i < rv.numarCategoriiVarsta; i++)
			{
				this->categoriiVarsta[i] = rv.categoriiVarsta[i];
			}
		}
		else
		{
			this->numarCategoriiVarsta = 0;
			this->categoriiVarsta = nullptr;
		}
	}

	restrictiiVarsta operator=(restrictiiVarsta rv)
	{
		if (categoriiVarsta != nullptr) {
			delete[] categoriiVarsta;
		}

		if (denumire != nullptr) {
			delete[] denumire;
		}

		if (rv.denumire != nullptr)
		{
			int len = strlen(rv.denumire) + 1;
			this->denumire = new char[len];
			strcpy_s(this->denumire, len, rv.denumire);
		}
		else
		{
			this->denumire = new char[1];
			strcpy_s(this->denumire, 1, "");
		}

		if (rv.numarCategoriiVarsta > 0 && rv.categoriiVarsta != nullptr)
		{
			this->numarCategoriiVarsta = rv.numarCategoriiVarsta;
			this->categoriiVarsta = new int[rv.numarCategoriiVarsta];
			for (int i = 0; i < rv.numarCategoriiVarsta; i++)
			{
				this->categoriiVarsta[i] = rv.categoriiVarsta[i];
			}
		}
		else
		{
			this->numarCategoriiVarsta = 0;
			this->categoriiVarsta = nullptr;
		}

		return *this;
	}

	~restrictiiVarsta()
	{
		if (categoriiVarsta != nullptr)
		{
			delete[] categoriiVarsta;
		}
		delete[] denumire;
	}

	bool operator!()
	{
		return numarCategoriiVarsta > 0;
	}

	bool operator==(char* denumire)
	{
		restrictiiVarsta copy = *this;
		return (copy.denumire == denumire);
	}

	restrictiiVarsta operator++()
	{
		this->numarCategoriiVarsta++;
		return *this;
	}

	restrictiiVarsta operator++(int i)
	{
		restrictiiVarsta copy = *this;
		this->numarCategoriiVarsta++;
		return copy;
	}

	restrictiiVarsta operator+(int numarCategoriiVarstaAdd)
	{
		if (numarCategoriiVarstaAdd < 0)
		{
			throw 500;
		}
		else
		{
			restrictiiVarsta copy = *this;
			copy.numarCategoriiVarsta += numarCategoriiVarstaAdd;
			return copy;
		}
	}

	bool operator>(int numarCategoriiVarstaComp)
	{
		restrictiiVarsta copy = *this;
		return (copy.numarCategoriiVarsta > numarCategoriiVarstaComp);
	}

	int& operator[](int pozitie) throw (exception)
	{
		if (pozitie >= 0 && pozitie < numarCategoriiVarsta && categoriiVarsta != nullptr)
		{
			return categoriiVarsta[pozitie];
		}
		else
		{
			throw exception("Pozitie invalida!");
		}
	}

	explicit operator int()
	{
		return numarCategoriiVarsta;
	}

	static void setrestrictiiVarsta(int cinema)
	{
		restrictiiVarsta::cinema = cinema;
	}

	friend ostream& operator<<(ostream&, restrictiiVarsta);
	friend istream& operator>>(istream&, restrictiiVarsta&);

};

ostream& operator<<(ostream& out, restrictiiVarsta rv)
{
	if (rv.denumire != nullptr)
	{
		out << "Denumire: " << rv.denumire << endl;
	}
	out << "Numar categorii de varsta: " << rv.numarCategoriiVarsta << endl;
	out << "Categorii de varsta: ";
	if (rv.categoriiVarsta != nullptr)
	{
		for (int i = 0; i < rv.numarCategoriiVarsta; i++)
		{
			out << rv.categoriiVarsta[i] << " ";
		}
	}
	return out;
}

istream& operator>> (istream& in, restrictiiVarsta& rv)
{
	delete[] rv.denumire;
	char buffer[100];
	cout << "Denumire: ";
	in >> ws;
	in.getline(buffer, 99);
	rv.denumire = new char[strlen(buffer) + 1];
	strcpy_s(rv.denumire, strlen(buffer) + 1, buffer);


	if (rv.categoriiVarsta != nullptr)
	{
		delete[] rv.categoriiVarsta;
	}
	cout << "Numar categorii de varsta: ";
	in >> rv.numarCategoriiVarsta;
	if (rv.numarCategoriiVarsta > 0)
	{
		rv.categoriiVarsta = new int[rv.numarCategoriiVarsta];
		for (int i = 0; i < rv.numarCategoriiVarsta; i++)
		{
			cout << "Varsta[" << i << "] = ";
			in >> rv.categoriiVarsta[i];
		}
	}
	else
	{
		rv.numarCategoriiVarsta = 0;
		rv.categoriiVarsta = nullptr;
	}
	return in;
}


//---------------------------------------------------------------------------------------------------------------------------------------
//
//							CLASA SALA
//
//---------------------------------------------------------------------------------------------------------------------------------------

class sala
{
private:
	const int cod;
	static int cinema;
	char* denumire;
	int etaj;
	int numarLocuri;
	int* locuri;

public:
	sala() :cod(1)
	{
		this->denumire = new char[1];
		strcpy_s(this->denumire, 1, "");
		this->numarLocuri = 0;
		this->etaj = 0;
		this->locuri = nullptr;
	}

	sala(int cod, char* denumire, int etaj, int numarLocuri, int* locuri) :cod(cod)
	{
		this->etaj = etaj;

		if (denumire != nullptr)
		{
			int len = strlen(denumire) + 1;
			this->denumire = new char[len];
			strcpy_s(this->denumire, len, denumire);
		}
		else
		{
			this->denumire = new char[1];
			strcpy_s(this->denumire, 1, "");
		}

		if (numarLocuri > 0)
		{
			this->numarLocuri = numarLocuri;
			this->locuri = new int[numarLocuri];
			for (int i = 0; i < numarLocuri; i++)
			{
				this->locuri[i] = locuri[i];
			}
		}
		else
		{
			this->numarLocuri = 0;
			this->locuri = nullptr;
		}
	}

	sala(const sala& s) : cod(s.cod)
	{
		this->etaj = s.etaj;

		if (s.denumire != nullptr)
		{
			int len = strlen(s.denumire) + 1;
			this->denumire = new char[len];
			strcpy_s(this->denumire, len, s.denumire);
		}
		else
		{
			this->denumire = new char[1];
			strcpy_s(this->denumire, 1, "");
		}

		if (s.numarLocuri > 0 && s.locuri != nullptr)
		{
			this->numarLocuri = s.numarLocuri;
			this->locuri = new int[s.numarLocuri];
			for (int i = 0; i < s.numarLocuri; i++)
			{
				this->locuri[i] = s.locuri[i];
			}
		}
		else
		{
			this->numarLocuri = 0;
			this->locuri = nullptr;
		}
	}

	sala operator=(sala s)
	{
		if (locuri != nullptr) {
			delete[] locuri;
		}

		if (denumire != nullptr) {
			delete[] denumire;
		}

		this->etaj = s.etaj;

		if (s.denumire != nullptr)
		{
			int len = strlen(s.denumire) + 1;
			this->denumire = new char[len];
			strcpy_s(this->denumire, len, s.denumire);
		}
		else
		{
			this->denumire = new char[1];
			strcpy_s(this->denumire, 1, "");
		}

		if (s.numarLocuri > 0 && s.locuri != nullptr)
		{
			this->numarLocuri = s.numarLocuri;
			this->locuri = new int[s.numarLocuri];
			for (int i = 0; i < s.numarLocuri; i++)
			{
				this->locuri[i] = s.locuri[i];
			}
		}
		else
		{
			this->numarLocuri = 0;
			this->locuri = nullptr;
		}

		return *this;
	}

	~sala()
	{
		if (locuri != nullptr)
		{
			delete[] locuri;
		}
		delete[] denumire;
	}

	bool operator!()
	{
		return numarLocuri > 0;
	}

	bool operator==(char* denumire)
	{
		sala copy = *this;
		return (copy.denumire == denumire);
	}

	sala operator++()
	{
		this->numarLocuri++;
		return *this;
	}

	sala operator++(int i)
	{
		sala copy = *this;
		this->numarLocuri++;
		return copy;
	}

	sala operator+(int numarLocuriAdd)
	{
		if (numarLocuriAdd < 0)
		{
			throw 500;
		}
		else
		{
			sala copy = *this;
			copy.numarLocuri += numarLocuriAdd;
			return copy;
		}
	}

	bool operator>(int numarLocuriComp)
	{
		sala copy = *this;
		return (copy.numarLocuri > numarLocuriComp);
	}

	int& operator[](int pozitie) throw (exception)
	{
		if (pozitie >= 0 && pozitie < numarLocuri && locuri != nullptr)
		{
			return locuri[pozitie];
		}
		else
		{
			throw exception("Pozitie invalida!");
		}
	}

	explicit operator int()
	{
		return numarLocuri;
	}

	static void setsala(int cinema)
	{
		sala::cinema = cinema;
	}

	friend ostream& operator<<(ostream&, sala);
	friend istream& operator>>(istream&, sala&);

};

ostream& operator<<(ostream& out, sala s)
{
	if (s.denumire != nullptr)
	{
		out << "Denumire: " << s.denumire << endl;
	}
	out << "Numar categorii de varsta: " << s.numarLocuri << endl;
	out << "Categorii de varsta: ";
	if (s.locuri != nullptr)
	{
		for (int i = 0; i < s.numarLocuri; i++)
		{
			out << s.locuri[i] << " ";
		}
	}
	return out;
}

istream& operator>> (istream& in, sala& s)
{
	delete[] s.denumire;
	char buffer[100];
	cout << "Denumire: ";
	in >> ws;
	in.getline(buffer, 99);
	s.denumire = new char[strlen(buffer) + 1];
	strcpy_s(s.denumire, strlen(buffer) + 1, buffer);


	if (s.locuri != nullptr)
	{
		delete[] s.locuri;
	}
	cout << "Numar categorii de varsta: ";
	in >> s.numarLocuri;
	if (s.numarLocuri > 0)
	{
		s.locuri = new int[s.numarLocuri];
		for (int i = 0; i < s.numarLocuri; i++)
		{
			cout << "Varsta[" << i << "] = ";
			in >> s.locuri[i];
		}
	}
	else
	{
		s.numarLocuri = 0;
		s.locuri = nullptr;
	}
	return in;
}

//---------------------------------------------------------------------------------------------------------------------------------------
//
//							CLASA FILM
//
//---------------------------------------------------------------------------------------------------------------------------------------

class film
{
private:
	const int cod;
	static int cinema;
	char* denumire;
	int rating;
	int numarRestrictiiVarsta;
	int* restrictiiVarsta;

public:
	film() :cod(1)
	{
		this->denumire = new char[1];
		strcpy_s(this->denumire, 1, "");
		this->numarRestrictiiVarsta = 0;
		this->rating = 0;
		this->restrictiiVarsta = nullptr;
	}

	film(int cod, char* denumire, int rating, int numarRestrictiiVarsta, int* restrictiiVarsta) :cod(cod)
	{
		this->rating = rating;

		if (denumire != nullptr)
		{
			int len = strlen(denumire) + 1;
			this->denumire = new char[len];
			strcpy_s(this->denumire, len, denumire);
		}
		else
		{
			this->denumire = new char[1];
			strcpy_s(this->denumire, 1, "");
		}

		if (numarRestrictiiVarsta > 0)
		{
			this->numarRestrictiiVarsta = numarRestrictiiVarsta;
			this->restrictiiVarsta = new int[numarRestrictiiVarsta];
			for (int i = 0; i < numarRestrictiiVarsta; i++)
			{
				this->restrictiiVarsta[i] = restrictiiVarsta[i];
			}
		}
		else
		{
			this->numarRestrictiiVarsta = 0;
			this->restrictiiVarsta = nullptr;
		}
	}

	film(const film& f) : cod(f.cod)
	{
		this->rating = f.rating;

		if (f.denumire != nullptr)
		{
			int len = strlen(f.denumire) + 1;
			this->denumire = new char[len];
			strcpy_s(this->denumire, len, f.denumire);
		}
		else
		{
			this->denumire = new char[1];
			strcpy_s(this->denumire, 1, "");
		}

		if (f.numarRestrictiiVarsta > 0 && f.restrictiiVarsta != nullptr)
		{
			this->numarRestrictiiVarsta = f.numarRestrictiiVarsta;
			this->restrictiiVarsta = new int[f.numarRestrictiiVarsta];
			for (int i = 0; i < f.numarRestrictiiVarsta; i++)
			{
				this->restrictiiVarsta[i] = f.restrictiiVarsta[i];
			}
		}
		else
		{
			this->numarRestrictiiVarsta = 0;
			this->restrictiiVarsta = nullptr;
		}
	}

	film operator=(film f)
	{
		if (restrictiiVarsta != nullptr) {
			delete[] restrictiiVarsta;
		}

		if (denumire != nullptr) {
			delete[] denumire;
		}

		this->rating = f.rating;

		if (f.denumire != nullptr)
		{
			int len = strlen(f.denumire) + 1;
			this->denumire = new char[len];
			strcpy_s(this->denumire, len, f.denumire);
		}
		else
		{
			this->denumire = new char[1];
			strcpy_s(this->denumire, 1, "");
		}

		if (f.numarRestrictiiVarsta > 0 && f.restrictiiVarsta != nullptr)
		{
			this->numarRestrictiiVarsta = f.numarRestrictiiVarsta;
			this->restrictiiVarsta = new int[f.numarRestrictiiVarsta];
			for (int i = 0; i < f.numarRestrictiiVarsta; i++)
			{
				this->restrictiiVarsta[i] = f.restrictiiVarsta[i];
			}
		}
		else
		{
			this->numarRestrictiiVarsta = 0;
			this->restrictiiVarsta = nullptr;
		}

		return *this;
	}

	~film()
	{
		if (restrictiiVarsta != nullptr)
		{
			delete[] restrictiiVarsta;
		}
		delete[] denumire;
	}

	bool operator!()
	{
		return numarRestrictiiVarsta > 0;
	}

	bool operator==(char* denumire)
	{
		film copy = *this;
		return (copy.denumire == denumire);
	}

	film operator++()
	{
		this->numarRestrictiiVarsta++;
		return *this;
	}

	film operator++(int i)
	{
		film copy = *this;
		this->numarRestrictiiVarsta++;
		return copy;
	}

	film operator+(int numarRestrictiiVarstaAdd)
	{
		if (numarRestrictiiVarstaAdd < 0)
		{
			throw 500;
		}
		else
		{
			film copy = *this;
			copy.numarRestrictiiVarsta += numarRestrictiiVarstaAdd;
			return copy;
		}
	}

	bool operator>(int numarRestrictiiVarstaComp)
	{
		film copy = *this;
		return (copy.numarRestrictiiVarsta > numarRestrictiiVarstaComp);
	}

	int& operator[](int pozitie) throw (exception)
	{
		if (pozitie >= 0 && pozitie < numarRestrictiiVarsta && restrictiiVarsta != nullptr)
		{
			return restrictiiVarsta[pozitie];
		}
		else
		{
			throw exception("Pozitie invalida!");
		}
	}

	explicit operator int()
	{
		return numarRestrictiiVarsta;
	}

	static void setfilm(int cinema)
	{
		film::cinema = cinema;
	}

	friend ostream& operator<<(ostream&, film);
	friend istream& operator>>(istream&, film&);

};

ostream& operator<<(ostream& out, film f)
{
	if (f.denumire != nullptr)
	{
		out << "Denumire: " << f.denumire << endl;
	}
	out << "Numar categorii de varsta: " << f.numarRestrictiiVarsta << endl;
	out << "Categorii de varsta: ";
	if (f.restrictiiVarsta != nullptr)
	{
		for (int i = 0; i < f.numarRestrictiiVarsta; i++)
		{
			out << f.restrictiiVarsta[i] << " ";
		}
	}
	return out;
}

istream& operator>> (istream& in, film& f)
{
	delete[] f.denumire;
	char buffer[100];
	cout << "Denumire: ";
	in >> ws;
	in.getline(buffer, 99);
	f.denumire = new char[strlen(buffer) + 1];
	strcpy_s(f.denumire, strlen(buffer) + 1, buffer);


	if (f.restrictiiVarsta != nullptr)
	{
		delete[] f.restrictiiVarsta;
	}
	cout << "Numar categorii de varsta: ";
	in >> f.numarRestrictiiVarsta;
	if (f.numarRestrictiiVarsta > 0)
	{
		f.restrictiiVarsta = new int[f.numarRestrictiiVarsta];
		for (int i = 0; i < f.numarRestrictiiVarsta; i++)
		{
			cout << "Varsta[" << i << "] = ";
			in >> f.restrictiiVarsta[i];
		}
	}
	else
	{
		f.numarRestrictiiVarsta = 0;
		f.restrictiiVarsta = nullptr;
	}
	return in;
}

//---------------------------------------------------------------------------------------------------------------------------------------
//
//							CLASA BILET
//
//---------------------------------------------------------------------------------------------------------------------------------------

class bilet
{
private:
	const int cod;
	static int cinema;
	char* denumire;
	int pret;
	int numarPersoane;
	int* varstaPersoane;

public:
	bilet() :cod(1)
	{
		this->denumire = new char[1];
		strcpy_s(this->denumire, 1, "");
		this->numarPersoane = 0;
		this->pret = 0;
		this->varstaPersoane = nullptr;
	}

	bilet(int cod, char* denumire, int pret, int numarPersoane, int* varstaPersoane) :cod(cod)
	{
		this->pret = pret;

		if (denumire != nullptr)
		{
			int len = strlen(denumire) + 1;
			this->denumire = new char[len];
			strcpy_s(this->denumire, len, denumire);
		}
		else
		{
			this->denumire = new char[1];
			strcpy_s(this->denumire, 1, "");
		}

		if (numarPersoane > 0)
		{
			this->numarPersoane = numarPersoane;
			this->varstaPersoane = new int[numarPersoane];
			for (int i = 0; i < numarPersoane; i++)
			{
				this->varstaPersoane[i] = varstaPersoane[i];
			}
		}
		else
		{
			this->numarPersoane = 0;
			this->varstaPersoane = nullptr;
		}
	}

	bilet(const bilet& b) : cod(b.cod)
	{
		this->pret = b.pret;

		if (b.denumire != nullptr)
		{
			int len = strlen(b.denumire) + 1;
			this->denumire = new char[len];
			strcpy_s(this->denumire, len, b.denumire);
		}
		else
		{
			this->denumire = new char[1];
			strcpy_s(this->denumire, 1, "");
		}

		if (b.numarPersoane > 0 && b.varstaPersoane != nullptr)
		{
			this->numarPersoane = b.numarPersoane;
			this->varstaPersoane = new int[b.numarPersoane];
			for (int i = 0; i < b.numarPersoane; i++)
			{
				this->varstaPersoane[i] = b.varstaPersoane[i];
			}
		}
		else
		{
			this->numarPersoane = 0;
			this->varstaPersoane = nullptr;
		}
	}

	bilet operator=(bilet b)
	{
		if (varstaPersoane != nullptr) {
			delete[] varstaPersoane;
		}

		if (denumire != nullptr) {
			delete[] denumire;
		}

		this->pret = b.pret;

		if (b.denumire != nullptr)
		{
			int len = strlen(b.denumire) + 1;
			this->denumire = new char[len];
			strcpy_s(this->denumire, len, b.denumire);
		}
		else
		{
			this->denumire = new char[1];
			strcpy_s(this->denumire, 1, "");
		}

		if (b.numarPersoane > 0 && b.varstaPersoane != nullptr)
		{
			this->numarPersoane = b.numarPersoane;
			this->varstaPersoane = new int[b.numarPersoane];
			for (int i = 0; i < b.numarPersoane; i++)
			{
				this->varstaPersoane[i] = b.varstaPersoane[i];
			}
		}
		else
		{
			this->numarPersoane = 0;
			this->varstaPersoane = nullptr;
		}

		return *this;
	}

	~bilet()
	{
		if (varstaPersoane != nullptr)
		{
			delete[] varstaPersoane;
		}
		delete[] denumire;
	}

	bool operator!()
	{
		return numarPersoane > 0;
	}

	bool operator==(char* denumire)
	{
		bilet copy = *this;
		return (copy.denumire == denumire);
	}

	bilet operator++()
	{
		this->numarPersoane++;
		return *this;
	}

	bilet operator++(int i)
	{
		bilet copy = *this;
		this->numarPersoane++;
		return copy;
	}

	bilet operator+(int numarPersoaneAdd)
	{
		if (numarPersoaneAdd < 0)
		{
			throw 500;
		}
		else
		{
			bilet copy = *this;
			copy.numarPersoane += numarPersoaneAdd;
			return copy;
		}
	}

	bool operator>(int numarPersoaneComp)
	{
		bilet copy = *this;
		return (copy.numarPersoane > numarPersoaneComp);
	}

	int& operator[](int pozitie) throw (exception)
	{
		if (pozitie >= 0 && pozitie < numarPersoane && varstaPersoane != nullptr)
		{
			return varstaPersoane[pozitie];
		}
		else
		{
			throw exception("Pozitie invalida!");
		}
	}

	explicit operator int()
	{
		return numarPersoane;
	}

	static void setbilet(int cinema)
	{
		bilet::cinema = cinema;
	}

	friend ostream& operator<<(ostream&, bilet);
	friend istream& operator>>(istream&, bilet&);

};

ostream& operator<<(ostream& out, bilet b)
{
	if (b.denumire != nullptr)
	{
		out << "Denumire: " << b.denumire << endl;
	}
	out << "Numar categorii de varsta: " << b.numarPersoane << endl;
	out << "Categorii de varsta: ";
	if (b.varstaPersoane != nullptr)
	{
		for (int i = 0; i < b.numarPersoane; i++)
		{
			out << b.varstaPersoane[i] << " ";
		}
	}
	return out;
}

istream& operator>> (istream& in, bilet& b)
{
	delete[] b.denumire;
	char buffer[100];
	cout << "Denumire: ";
	in >> ws;
	in.getline(buffer, 99);
	b.denumire = new char[strlen(buffer) + 1];
	strcpy_s(b.denumire, strlen(buffer) + 1, buffer);


	if (b.varstaPersoane != nullptr)
	{
		delete[] b.varstaPersoane;
	}
	cout << "Numar categorii de varsta: ";
	in >> b.numarPersoane;
	if (b.numarPersoane > 0)
	{
		b.varstaPersoane = new int[b.numarPersoane];
		for (int i = 0; i < b.numarPersoane; i++)
		{
			cout << "Varsta[" << i << "] = ";
			in >> b.varstaPersoane[i];
		}
	}
	else
	{
		b.numarPersoane = 0;
		b.varstaPersoane = nullptr;
	}
	return in;
}

//---------------------------------------------------------------------------------------------------------------------------------------
//
//							FINAL CLASE
//
//---------------------------------------------------------------------------------------------------------------------------------------


int main()
{
	cout << "test";

}