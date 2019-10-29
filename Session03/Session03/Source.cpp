#include "Objekt.h"
#include "StatickyObjekt.h"
#include "Hra.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {
	Objekt* objekt = new StatickyObjekt{ 1, StatickyObjekt::TypPrekazky::MalaRostlina };
	objekt->SetX(2);
	objekt->SetY(3);
	StatickyObjekt* so = dynamic_cast<StatickyObjekt*>(objekt);

	Objekt* objekt1 = new PohyblivyObjekt(2, 1.15);
	objekt1->SetX(4);
	objekt1->SetY(1);

	Objekt* objekt2 = new PohyblivyObjekt(3, 0.65);
	objekt2->SetX(3);
	objekt2->SetY(5);

	if (so != nullptr)
	{
		string nazevPrekazky;
		switch (so->GetTypPrekazky())
		{
		case StatickyObjekt::TypPrekazky::MalaRostlina: nazevPrekazky = "MalaRostlina"; break;
		case StatickyObjekt::TypPrekazky::VelkaRostlina: nazevPrekazky = "VelkaRostlina"; break;
		case StatickyObjekt::TypPrekazky::Skala: nazevPrekazky = "Skala"; break;
		default:
			break;
		}
		cout << "objekt je StatickyObjekt (nebo jeho potomek) " << nazevPrekazky << endl;
	}

	Hra hra;
	hra.vlozObjekt(objekt);
	hra.vlozObjekt(objekt1);
	hra.vlozObjekt(objekt2);
	hra.vypisObjekty();
	
	int pocetObjektu;
	int* idStatickychObjektu = hra.najdiIdStatickychObjektu(1, 10, 1, 10, &pocetObjektu);

	if (idStatickychObjektu != nullptr)
	{
		cout << "V hledane oblasti jsou objekty s ID: " << endl;
		for (size_t i = 0; i < pocetObjektu; i++)
		{
			cout << idStatickychObjektu[i] << endl;
		}
	}

	delete[] idStatickychObjektu;

	PohyblivyObjekt** polePohyblivychObjektu = hra.najdiPohybliveObjektyVOblasti(7,7,7, &pocetObjektu);
	if (polePohyblivychObjektu != nullptr) {
		cout << "V hledane kruhove oblasti jsou objekty s ID: " << endl;
		for (size_t i = 0; i < pocetObjektu; i++)
		{
			cout << polePohyblivychObjektu[i]->GetId() << endl;
		}
	}

	delete[] polePohyblivychObjektu;

	PohyblivyObjekt** polePohyblivychObjektu1 = hra.najdiPohybliveObjektyVOblasti(5, 5, 5, 1.1, 1.8, &pocetObjektu);
	if (polePohyblivychObjektu1 != nullptr) {
		cout << "V hledane kruhove oblasti s natocenim jsou objekty s ID: " << endl;
		for (size_t i = 0; i < pocetObjektu; i++)
		{
			cout << polePohyblivychObjektu1[i]->GetId() << endl;
		}
	}

	delete[] polePohyblivychObjektu1;
}