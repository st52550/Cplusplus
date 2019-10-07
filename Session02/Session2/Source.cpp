#include "Pokladna.h"
#include "Uctenka.h"

#include <iostream>

using namespace std;

int main() {
	Pokladna pokladna {};

	Uctenka uctenka1 = pokladna.VystavUctenku(1000, 0.2);
	Uctenka uctenka2 = pokladna.VystavUctenku(4300, 0.21);
	Uctenka uctenka3 = pokladna.VystavUctenku(2150, 0.32);

	Uctenka uctenka = pokladna.DejUctenku(1001);
	cout << "Uctenka c. " << uctenka.GetCisloUctenky() << " | Castka: " << uctenka.GetCastka() << " | DPH: " << uctenka.GetDph() << endl;

	cout << "Celkova castka bez DPH: " << pokladna.DejCastku() << endl;
	cout << "Celkova castka vc. DPH: " << pokladna.DejCastkuVcDph() << endl;
}