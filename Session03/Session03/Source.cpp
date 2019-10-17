#include "Objekt.h"
#include "StatickyObjekt.h"
#include "Hra.h"

#include <iostream>

using namespace std;

int main() {
	Objekt* objekt = new StatickyObjekt{ 1, StatickyObjekt::TypPrekazky::MalaRostlina };
	objekt->SetX(2);
	objekt->SetY(3);
	StatickyObjekt* so = dynamic_cast<StatickyObjekt*>(objekt);

	Objekt* objekt1 = new PohyblivyObjekt(2, 1.15);
	objekt1->SetX(4);
	objekt1->SetY(1);

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
	hra.vypisObjekty();
	
	int* idStatickychObjektu = hra.najdiIdStatickychObjektu(1, 10, 1, 10);
	if (idStatickychObjektu != nullptr)
	{
		cout << "V hledane oblasti jsou objekty s ID: " << endl;
		for (size_t i = 0; i < sizeof(idStatickychObjektu) / sizeof(idStatickychObjektu[0]); i++)
		{
			cout << idStatickychObjektu[i] << endl;
		}
	}

	PohyblivyObjekt** polePohyblivychObjektu = hra.najdiPohybliveObjektyVOblasti(1,1,1);
	if (polePohyblivychObjektu != nullptr) {
		cout << "V hledane kruhove oblasti jsou objekty s ID: " << endl;
		for (size_t i = 0; i < sizeof(polePohyblivychObjektu) / sizeof(polePohyblivychObjektu[0]); i++)
		{
			cout << polePohyblivychObjektu[i]->GetId() << endl;
		}
	}

	PohyblivyObjekt** polePohyblivychObjektu1 = hra.najdiPohybliveObjektyVOblasti(5, 5, 5, 1.1, 1.8);
	if (polePohyblivychObjektu1 != nullptr) {
		cout << "V hledane kruhove oblasti s natocenim jsou objekty s ID: " << endl;
		for (size_t i = 0; i < sizeof(polePohyblivychObjektu1) / sizeof(polePohyblivychObjektu1[0]); i++)
		{
			cout << polePohyblivychObjektu1[i]->GetId() << endl;
		}
	}
}