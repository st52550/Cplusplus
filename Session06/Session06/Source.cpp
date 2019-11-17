#include "Osoba.h"

#include <iostream>
#include <fstream>
#include <sstream>

#define N 3

using namespace std;

void uloz();
void nacti();
void ulozBinarne();
void nactiBinarne();
void vypisOsoby(Osoba** poleOsob, int pocetOsob);

int main() {
	uloz();
	nacti();
	ulozBinarne();
	nactiBinarne();
}

void vypisOsoby(Osoba** poleOsob, int pocetOsob) {
	for (size_t i = 0; i < pocetOsob; i++)
	{
		cout << *poleOsob[i] << endl;
	}
}

void uloz() {
	Osoba** poleOsob = new Osoba*[N];
	string hlavicka = "Prijmeni;Jmeno;Datum narozeni;Ulice;Mesto;PSC";

	poleOsob[0] = new Osoba("Jan", "Novak", new Adresa("Palackeho", "Pardubice", 53301), new Datum(21, 5, 1984));
	poleOsob[1] = new Osoba("Karel", "Maly", new Adresa("17. listopadu", "Hradec Kralove", 53103), new Datum(2, 4, 1991));
	poleOsob[2] = new Osoba("Helena", "Kozena", new Adresa("Lidicka", "Pardubice", 53301), new Datum(16, 10, 1996));

	ofstream out{};
	out.open("data.txt");

	if (out.is_open())
	{
		out << hlavicka << endl;

		for (size_t i = 0; i < N; i++)
		{
			out << *poleOsob[i] << endl;
		}
		out.close();
	}
	else {
		cerr << "Soubor se nepodarilo otevrit";
	}

	for (size_t i = 0; i < N; i++)
	{
		delete poleOsob[i];
	}

	delete[] poleOsob;
}

void nacti() {
	printf("Z textoveho souboru:\n");

	Osoba** poleOsob = nullptr;
	string radek;
	int pocetOsob = -1;

	ifstream in{};
	in.open("data.txt");

	if (in.is_open())
	{
		while (getline(in, radek)) {
			pocetOsob++;
		}

		in.clear();
		in.seekg(0);			

		poleOsob = new Osoba * [pocetOsob];

		string prijmeni;
		string jmeno;
		int den;
		int mesic;
		int rok;
		string ulice;
		string mesto;
		int psc;

		int citac = 0;
		char delimiter = ';';
		char delimiterDatum = '.';
		string token;
		string tokenDatum;

		getline(in, radek);

		while (getline(in, radek)) {
			stringstream ss(radek);
			getline(ss, token, delimiter);
			prijmeni = token;
			getline(ss, token, delimiter);
			jmeno = token;
			
			getline(ss, token, delimiter);
			stringstream ssDatum(token);
			getline(ssDatum, tokenDatum, delimiterDatum);
			den = stoi(tokenDatum);
			getline(ssDatum, tokenDatum, delimiterDatum);
			mesic = stoi(tokenDatum);
			getline(ssDatum, tokenDatum, delimiterDatum);
			rok = stoi(tokenDatum);

			getline(ss, token, delimiter);
			ulice = token;
			getline(ss, token, delimiter);
			mesto = token;
			getline(ss, token, delimiter);
			psc = stoi(token);

			poleOsob[citac] = new Osoba(jmeno, prijmeni, new Adresa(ulice, mesto, psc), new Datum(den, mesic, rok));
			citac++;
		}
	}
	else {
		cerr << "Soubor se nepodarilo otevrit";
	}

	in.close();

	if (poleOsob != nullptr)
	{
		vypisOsoby(poleOsob, pocetOsob);

		for (size_t i = 0; i < N; i++)
		{
			delete poleOsob[i];
		}

		delete[] poleOsob;
	}
}

void ulozBinarne() {
	Osoba** poleOsob = new Osoba * [N];

	poleOsob[0] = new Osoba("Jan", "Novak", new Adresa("Palackeho", "Pardubice", 53301), new Datum(21, 5, 1984));
	poleOsob[1] = new Osoba("Karel", "Maly", new Adresa("17. listopadu", "Hradec Kralove", 53103), new Datum(2, 4, 1991));
	poleOsob[2] = new Osoba("Helena", "Kozena", new Adresa("Lidicka", "Pardubice", 53301), new Datum(16, 10, 1996));

	ofstream out{};
	out.open("dataBin.dat", ios::binary);

	if (out.is_open())
	{
		Osoba osoba;
		int pocetOsob = N;

		string prijmeni;
		string jmeno;
		string ulice;
		string mesto;
		int psc;
		size_t size;

		out.write((char*)&pocetOsob, sizeof(pocetOsob));

		for (size_t i = 0; i < N; i++)
		{
			osoba = *poleOsob[i];

			prijmeni = osoba.GetPrijmeni();
			size = prijmeni.size();
			out.write((char*)&size, sizeof(size));
			out.write(prijmeni.c_str(), size);
			
			jmeno = osoba.GetJmeno();
			size = jmeno.size();
			out.write((char*)&size, sizeof(size));
			out.write(jmeno.c_str(), jmeno.size());

			out.write((char*)&osoba.GetDatum(), sizeof(osoba.GetDatum()));

			ulice = osoba.GetAdresa().GetUlice();
			size = ulice.size();
			out.write((char*)&size, sizeof(size));
			out.write(ulice.c_str(), ulice.size());

			mesto = osoba.GetAdresa().GetMesto();
			size = mesto.size();
			out.write((char*)&size, sizeof(size));
			out.write(mesto.c_str(), mesto.size());

			int psc = osoba.GetAdresa().GetPsc();
			out.write((char*)&psc, sizeof(psc));
		}

		out.close();
	}
	else {
		cerr << "Nepodarilo se otevrit soubor" << endl;
	}

	for (size_t i = 0; i < N; i++)
	{
		delete poleOsob[i];
	}

	delete[] poleOsob;
}

void nactiBinarne() {
	printf("Z binarniho souboru:\n");

	Osoba** poleOsob = nullptr;
	int pocetOsob;

	ifstream in{};
	in.open("dataBin.dat", ios::binary);

	string prijmeni;
	string jmeno;
	Datum datum;
	string ulice;
	string mesto;
	int psc;
	size_t size;

	if (in.is_open())
	{		
		in.read((char*)&pocetOsob, sizeof(pocetOsob));

		poleOsob = new Osoba * [pocetOsob];

		for (size_t i = 0; i < pocetOsob; i++)
		{
			in.read((char*)&size, sizeof(size));
			prijmeni.resize(size);
			in.read((char*)&prijmeni[0], size);

			in.read((char*)&size, sizeof(size));
			jmeno.resize(size);
			in.read((char*)&jmeno[0], size);

			in.read((char*)&datum, sizeof(datum));

			in.read((char*)&size, sizeof(size));
			ulice.resize(size);
			in.read((char*)&ulice[0], size);

			in.read((char*)&size, sizeof(size));
			mesto.resize(size);
			in.read((char*)&mesto[0], size);

			in.read((char*)&psc, sizeof(psc));

			poleOsob[i] = new Osoba(jmeno, prijmeni, new Adresa(ulice, mesto, psc), new Datum(datum));			
		}	
	}
	else {
		cerr << "Soubor se nepodarilo otevrit";
	}

	in.close();

	if (poleOsob != nullptr)
	{
		vypisOsoby(poleOsob, pocetOsob);

		for (size_t i = 0; i < N; i++)
		{
			delete poleOsob[i];
		}

		delete[] poleOsob;
	}
}