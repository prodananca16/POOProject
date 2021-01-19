#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <cassert>
#include <fstream>
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

	Cinema(char* denumire, int numarSali, int* sali) :cod(2)
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
	friend ofstream& operator<<(ofstream&, Cinema);
	friend ifstream& operator>>(ifstream&, Cinema&);

};

ostream& operator<<(ostream& out, Cinema c)
{
	if (c.denumire != nullptr)
	{
		out << "CINEMA: " << c.denumire << endl;
	}
	else 
	{
		out << "CIENEMA : " << endl;
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

ofstream& operator<<(ofstream& g, Cinema c)
{
	if (g.is_open())
	{
		if (c.denumire != nullptr)
		{
			g << c.denumire << endl;
		}
		else
		{
			g << "N/A" << endl;
		}
		g << c.numarSali << endl;
		if (c.sali != nullptr)
		{
			for (int i = 0; i < c.numarSali; i++)
			{
				g << c.sali[i] << endl;
			}
		}
	}
	return g;
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
			cout << "Sala[" << i+1 << "] = ";
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

ifstream& operator>>(ifstream& g, Cinema& c)
{
	if (g.is_open())
	{
		if (c.denumire != nullptr)
		{
			delete[] c.denumire;
		}
		string buffer;
		g >> ws;
		getline(g, buffer);
		c.denumire = new char[buffer.length() + 1];
		strcpy_s(c.denumire, buffer.length() + 1, buffer.c_str());

		string numarElemente;
		g >> ws;
		getline(g, numarElemente);

		if (std::stoi(numarElemente) > 0)
		{
			c.numarSali = std::stoi(numarElemente);
			c.sali = new int[std::stoi(numarElemente)];
			for (int i = 0; i < std::stoi(numarElemente); i++)
			{
				g >> ws;
				getline(g, buffer);
				c.sali[i] = std::stoi(buffer);
			}
		}
		else
		{
			c.numarSali = 0;
			c.sali = nullptr;
		}

	}
	return g;
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

	restrictiiVarsta(char* denumire, int numarCategoriiVarsta, int* categoriiVarsta) :cod(2)
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
	friend ofstream& operator<<(ofstream&, restrictiiVarsta);
	friend ifstream& operator>>(ifstream&, restrictiiVarsta&);

};

ostream& operator<<(ostream& out, restrictiiVarsta rv)
{
	if (rv.denumire != nullptr)
	{
		out << "RESTRICTII VARSTA: " << rv.denumire << endl;
	}
	else
	{
		out << "RESTRICTII VARSTA : " << endl;
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

ofstream& operator<<(ofstream& g, restrictiiVarsta rv)
{
	if (g.is_open())
	{
		if (rv.denumire != nullptr)
		{
			g << rv.denumire << endl;
		}
		else
		{
			g << "N/A" << endl;
		}
		g << rv.numarCategoriiVarsta << endl;
		if (rv.categoriiVarsta != nullptr)
		{
			for (int i = 0; i < rv.numarCategoriiVarsta; i++)
			{
				g << rv.categoriiVarsta[i] << endl;
			}
		}
	}
	return g;
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
			cout << "Varsta[" << i+1 << "] = ";
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

ifstream& operator>>(ifstream& g, restrictiiVarsta& rv)
{
	if (g.is_open())
	{
		if (rv.denumire != nullptr)
		{
			delete[] rv.denumire;
		}
		string buffer;
		g >> ws;
		getline(g, buffer);
		rv.denumire = new char[buffer.length() + 1];
		strcpy_s(rv.denumire, buffer.length() + 1, buffer.c_str());

		string numarElemente;
		g >> ws;
		getline(g, numarElemente);

		if (std::stoi(numarElemente) > 0)
		{
			rv.numarCategoriiVarsta = std::stoi(numarElemente);
			rv.categoriiVarsta = new int[std::stoi(numarElemente)];
			for (int i = 0; i < std::stoi(numarElemente); i++)
			{
				g >> ws;
				getline(g, buffer);
				rv.categoriiVarsta[i] = std::stoi(buffer);
			}
		}
		else
		{
			rv.numarCategoriiVarsta = 0;
			rv.categoriiVarsta = nullptr;
		}

	}
	return g;
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

	sala(char* denumire, int etaj, int numarLocuri, int* locuri) :cod(2)
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

	char* getDenumire()
	{
		return denumire;
	}

	int getNumarLocuri ()
	{
		return numarLocuri;
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
	friend ofstream& operator<<(ofstream&, sala);
	friend ifstream& operator>>(ifstream&, sala&);

};

ostream& operator<<(ostream& out, sala s)
{
	if (s.denumire != nullptr)
	{
		out << "SALA: " << s.denumire << endl;
	}
	else
	{
		out << "SALA: " << endl;
	}

	out << "Etaj: " << s.etaj << endl;

	out << "Numar locuri: " << s.numarLocuri << endl;
	out << "Locuri: ";
	if (s.locuri != nullptr)
	{
		for (int i = 0; i < s.numarLocuri; i++)
		{
			out << s.locuri[i] << " ";
		}
	}
	return out;
}

ofstream& operator<<(ofstream& g, sala s)
{
	if (g.is_open())
	{
		if (s.denumire != nullptr)
		{
			g << s.denumire << endl;
		}
		else
		{
			g << "N/A" << endl;
		}
		g << s.etaj << endl;
		g << s.numarLocuri << endl;
		if (s.locuri != nullptr)
		{
			for (int i = 0; i < s.numarLocuri; i++)
			{
				g << s.locuri[i] << endl;
			}
		}
	}
	return g;
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

	cout << "Etaj: ";
	in >> s.etaj;

	if (s.locuri != nullptr)
	{
		delete[] s.locuri;
	}
	cout << "Numar locuri: ";
	in >> s.numarLocuri;
	if (s.numarLocuri > 0)
	{
		s.locuri = new int[s.numarLocuri];
		for (int i = 0; i < s.numarLocuri; i++)
		{
			cout << "Locul[" << i+1 << "] = ";
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

ifstream& operator>>(ifstream& g, sala& s)
{
	if (g.is_open())
	{
		if (s.denumire != nullptr)
		{
			delete[] s.denumire;
		}
		string buffer;
		g >> ws;
		getline(g, buffer);
		s.denumire = new char[buffer.length() + 1];
		strcpy_s(s.denumire, buffer.length() + 1, buffer.c_str());

		string etaj;
		g >> ws;
		getline(g, etaj);
		s.etaj = std::stoi(etaj);

		string numarElemente;
		g >> ws;
		getline(g, numarElemente);

		if (std::stoi(numarElemente) > 0)
		{
			s.numarLocuri = std::stoi(numarElemente);
			s.locuri = new int[std::stoi(numarElemente)];
			for (int i = 0; i < std::stoi(numarElemente); i++)
			{
				g >> ws;
				getline(g, buffer);
				s.locuri[i] = std::stoi(buffer);
			}
		}
		else
		{
			s.numarLocuri = 0;
			s.locuri = nullptr;
		}

	}
	return g;
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

	film(char* denumire, int rating, int numarRestrictiiVarsta, int* restrictiiVarsta) :cod(2)
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

	char* getDenumire()
	{
		return denumire;
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
	friend ofstream& operator<<(ofstream&, film);
	friend ifstream& operator>>(ifstream&, film&);

};

ostream& operator<<(ostream& out, film f)
{
	if (f.denumire != nullptr)
	{
		out << "FILM: " << f.denumire << endl;
	}
	else
	{
		out << "FILM: " << endl;
	}

	out << "Rating: " << f.rating << endl;
	out << "Numar restrictii de varsta: " << f.numarRestrictiiVarsta << endl;
	out << "Restrictii de varsta: ";
	if (f.restrictiiVarsta != nullptr)
	{
		for (int i = 0; i < f.numarRestrictiiVarsta; i++)
		{
			out << f.restrictiiVarsta[i] << " ";
		}
	}
	return out;
}

ofstream& operator<<(ofstream& g, film f)
{
	if (g.is_open())
	{
		if (f.denumire != nullptr)
		{
			g << f.denumire << endl;
		}
		else
		{
			g << "N/A" << endl;
		}
		g << f.rating << endl;
		g << f.numarRestrictiiVarsta << endl;
		if (f.restrictiiVarsta != nullptr)
		{
			for (int i = 0; i < f.numarRestrictiiVarsta; i++)
			{
				g << f.restrictiiVarsta[i] << endl;
			}
		}
	}
	return g;
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


	cout << "Rating: ";
	in >> f.rating;

	if (f.restrictiiVarsta != nullptr)
	{
		delete[] f.restrictiiVarsta;
	}
	cout << "Numar restrictii de varsta: ";
	in >> f.numarRestrictiiVarsta;
	if (f.numarRestrictiiVarsta > 0)
	{
		f.restrictiiVarsta = new int[f.numarRestrictiiVarsta];
		for (int i = 0; i < f.numarRestrictiiVarsta; i++)
		{
			cout << "Restrictie varsta[" << i+1 << "] = ";
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

ifstream& operator>>(ifstream& g, film& f)
{
	if (g.is_open())
	{
		if (f.denumire != nullptr)
		{
			delete[] f.denumire;
		}
		string buffer;
		g >> ws;
		getline(g, buffer);
		f.denumire = new char[buffer.length() + 1];
		strcpy_s(f.denumire, buffer.length() + 1, buffer.c_str());

		string rating;
		g >> ws;
		getline(g, rating);
		f.rating = std::stoi(rating);

		string numarElemente;
		g >> ws;
		getline(g, numarElemente);

		if (std::stoi(numarElemente) > 0)
		{
			f.numarRestrictiiVarsta = std::stoi(numarElemente);
			f.restrictiiVarsta = new int[std::stoi(numarElemente)];
			for (int i = 0; i < std::stoi(numarElemente); i++)
			{
				g >> ws;
				getline(g, buffer);
				f.restrictiiVarsta[i] = std::stoi(buffer);
			}
		}
		else
		{
			f.numarRestrictiiVarsta = 0;
			f.restrictiiVarsta = nullptr;
		}

	}
	return g;
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

	bilet(char* denumire, int pret, int numarPersoane, int* varstaPersoane) :cod(2)
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

	int getNumarPersoane()
	{
		return numarPersoane;
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
	friend ofstream& operator<<(ofstream&, bilet);
	friend ifstream& operator>>(ifstream&, bilet&);

};

ostream& operator<<(ostream& out, bilet b)
{
	if (b.denumire != nullptr)
	{
		out << "BILET: " << b.denumire << endl;
	}
	else
	{
		out << "BILET: " << endl;
	}
	
	out << "Pret: " << b.pret << endl;
	out << "Numar persoane: " << b.numarPersoane << endl;
	out << "Varsta persoane: ";
	if (b.varstaPersoane != nullptr)
	{
		for (int i = 0; i < b.numarPersoane; i++)
		{
			out << b.varstaPersoane[i] << " ";
		}
	}
	return out;
}

ofstream& operator<<(ofstream& g, bilet b)
{
	if (g.is_open())
	{
		if (b.denumire != nullptr)
		{
			g << b.denumire << endl;
		}
		else
		{
			g << "N/A" << endl;
		}
		g << b.pret << endl;
		g << b.numarPersoane << endl;
		if (b.varstaPersoane != nullptr)
		{
			for (int i = 0; i < b.numarPersoane; i++)
			{
				g << b.varstaPersoane[i] << endl;
			}
		}
	}
	return g;
}

istream& operator>> (istream& in, bilet& b)
{
	delete[] b.denumire;
	char buffer[100];
	cout << "Pachet: ";
	in >> ws;
	in.getline(buffer, 99);
	b.denumire = new char[strlen(buffer) + 1];
	strcpy_s(b.denumire, strlen(buffer) + 1, buffer);

	cout << "Pret bilet (banii sunt donati integral ONGului Salvati motanii): ";
	in >> b.pret;

	if (b.varstaPersoane != nullptr)
	{
		delete[] b.varstaPersoane;
	}
	cout << "Numar persoane: ";
	in >> b.numarPersoane;
	if (b.numarPersoane > 0)
	{
		b.varstaPersoane = new int[b.numarPersoane];
		for (int i = 0; i < b.numarPersoane; i++)
		{
			cout << "Varsta persoanei[" << i+1 << "] = ";
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


ifstream& operator>>(ifstream& g, bilet& b)
{
	if (g.is_open())
	{
		if (b.denumire != nullptr)
		{
			delete[] b.denumire;
		}
		string buffer;
		g >> ws;
		getline(g, buffer);
		b.denumire = new char[buffer.length() + 1];
		strcpy_s(b.denumire, buffer.length() + 1, buffer.c_str());

		string pret;
		g >> ws;
		getline(g, pret);
		b.pret = std::stoi(pret);

		string numarElemente;
		g >> ws;
		getline(g, numarElemente);

		if (std::stoi(numarElemente) > 0)
		{
			b.numarPersoane = std::stoi(numarElemente);
			b.varstaPersoane = new int[std::stoi(numarElemente)];
			for (int i = 0; i < std::stoi(numarElemente); i++)
			{
				g >> ws;
				getline(g, buffer);
				b.varstaPersoane[i] = std::stoi(buffer);
			}
		}
		else
		{
			b.numarPersoane = 0;
			b.varstaPersoane = nullptr;
		}

	}
	return g;
}

//---------------------------------------------------------------------------------------------------------------------------------------
//
//							FINAL CLASE
//
//---------------------------------------------------------------------------------------------------------------------------------------


int main()
{
//MENIU
	cout << "MENIU" << endl;
	cout << "Optiunea 1: Introducere cinema" << endl;
	cout << "Optiunea 2: Afiseaza cinema" << endl;
	cout << "Optiunea 3: Introducere sali cinema" << endl;
	cout << "Optiunea 4: Afiseaza sali cinema" << endl;
	cout << "Optiunea 5: Introducere restrictii varsta" << endl;
	cout << "Optiunea 6: Afiseaza restrictii varsta" << endl;
	cout << "Optiunea 7: Introducere filme" << endl;
	cout << "Optiunea 8: Afiseaza filme" << endl;
	cout << "Optiunea 9: Introducere bilete" << endl;
	cout << "Optiunea 10: Afiseaza bilet" << endl;
	cout << "Optiunea 11: Afiseaza situatie locuri" << endl;
	cout << "Optiunea 0: IESIRE" << endl;

	int optiune = 1;
	

	while (optiune > 0)
	{
		cout << endl << "Optiunea ta: ";
		cin >> optiune;

		switch (optiune) {
			case 1:
			{
				//CINEMA
				//int sali[] = { 1, 2, 3 };
				//char* denumireCinema;
				//denumireCinema = new char[7];
				//strcpy_s(denumireCinema, 7, "SCALA");
				//Cinema c(denumireCinema, 3, sali);
		
				Cinema c;
				cin >> c;

				//scriu/modific in fisier o unica CINEMA
				ofstream g;
				g.open("cinema.txt", ios::_Nocreate | ios::binary | ios::in);
				g << c;
				g.close();
			}
			break;
			case 2:
			{
				//citesc din fisier
				ifstream f("cinema.txt");
				Cinema c2;
				f >> c2;
				f.close();
				cout << "Cinema din fisier: " << endl;
				cout << c2 << endl;
			}
			break;
			case 3:
			{
				//SALA
				//int locuri[] = { 1, 2, 3 };
				//char* denumireSala;
				//denumireSala = new char[6];
				//strcpy_s(denumireSala, 6, "PARIS");
				//sala s(denumireSala, 2, 3, locuri);

				sala s;
				cin >> s;
				//scriu in fisier
				ofstream fs;
				fs.open("sala.txt", std::ios_base::app);
				fs << s;
				fs.close();
			}
				break;
			case 4:
			{
				//citesc din fisier
				ifstream fsc("sala.txt");
				sala s1;
				fsc >> s1;
				fsc.close();
				cout << "Sala din fisier: " << endl;
				cout << s1 << endl;
			}
			break;
			case 5:
			{
				//RESTRICTII VARSTA
				//int varste[] = { 10, 11, 12, 13 };
				//char* denumireCategorie;
				//denumireCategorie = new char[3];
				//strcpy_s(denumireCategorie, 3, "AP");
				//restrictiiVarsta rv(denumireCategorie, 4, varste);

				restrictiiVarsta rv;
				cin >> rv;
				//scriu in fisier
				ofstream frv;
				frv.open("restrictiiVarsta.txt", std::ios_base::app);
				frv << rv;
				frv.close();
			}
			break;
			case 6:
			{
				//citesc din fisier
				ifstream frvc("restrictiiVarsta.txt");
				restrictiiVarsta rv1;
				frvc >> rv1;
				frvc.close();
				cout << "Restrictii varsta din fisier: " << endl;
				cout << rv1 << endl;
			}
			break;
			case 7:
			{
				//FILM
				//char* denumire;
				//denumire = new char[19];
				//strcpy_s(denumire, 19, "Frumoasa si bestia");
				//film f1(denumire, 10, 0, nullptr);

				film f1;
				cin >> f1;

				//scriu in fisier
				ofstream ff;
				ff.open("film.txt", std::ios_base::app);
				ff << f1;
				ff.close();
			}
			break;
			case 8:
			{
				//citesc din fisier
				ifstream fl("film.txt");
				film f2;
				fl >> f2;
				fl.close();
				cout << "Filme din fisier: " << endl;
				cout << f2 << endl;
			}
			break;
			case 9:
			{
				//BILET
				//int locuribilet[] = { 10, 11, 12 };
				//char* pachet;
				//pachet = new char[8];
				//strcpy_s(pachet, 8, "Familie");
				//bilet b1(denumire, 10, 3, locuribilet);

				bilet b1;
				
				ifstream fl("film.txt");
				film f2;
				fl >> f2;
				fl.close();
				cout << "Film disponibil: " << f2.getDenumire() << endl;
				
				ifstream fsc("sala.txt");
				sala s1;
				fsc >> s1;
				fsc.close();
				cout << "Sala disponibila: " << s1.getDenumire() << endl;
				
				cout << "Pachete disponibile: ROMANCE, FAMILY, JustOne" << endl;
				cout << "Introdu datele biletului: " << endl;
				cin >> b1;

				//scriu in fisier
				ofstream fb;
				fb.open("bilet.txt", std::ios_base::app);
				fb << b1;
				fb.close();

			}
			break;
			case 10:
			{
				//citesc din fisier
				ifstream fbb("bilet.txt");
				bilet b2;
				fbb >> b2;
				fbb.close();
				cout << "Bilet din fisier: " << endl;
				cout << b2 << endl;
			}
			break;
			case 11:
			{
				ifstream fsc("sala.txt");
				sala s1;
				fsc >> s1;
				fsc.close();
				cout << "Locuri totale in sala: " << s1.getDenumire() << ": " << s1.getNumarLocuri() << endl;

				ifstream fbb("bilet.txt");
				bilet b2;
				fbb >> b2;
				fbb.close();
				cout << "Locuri pentru care am vandut bilete: " << b2.getNumarPersoane() << endl;

			}
			break;
			case 0:
				break;
			}
	}

	cout << "La revedere!";
}