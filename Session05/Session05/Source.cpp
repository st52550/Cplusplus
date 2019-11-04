#include "TelefonniSeznam.h"
#include "Vyjimky.h"

#include <string>
#include <iostream>

using namespace Model;
using namespace Entity;
using namespace std;

int main() {
	TelefonniSeznam telefonniSeznam;
	Osoba* osoba1 = new Osoba("Jan Novak", "731 745 785", 1);
	Osoba* osoba2 = new Osoba("Petr Havlicek", "724 658 724", 2);
	Osoba* osoba3 = new Osoba("Karel Hermanek", "737 956 214", 3);
	Osoba* osoba4 = new Osoba("Lucie Kudrova", "731 645 274", 4);
	Osoba* osoba5 = new Osoba("Jana Mala", "733 756 245", 5);

	telefonniSeznam.PridejOsobu(osoba1);
	telefonniSeznam.PridejOsobu(osoba2);
	telefonniSeznam.PridejOsobu(osoba3);
	telefonniSeznam.PridejOsobu(osoba4);
	telefonniSeznam.PridejOsobu(osoba5);

	telefonniSeznam.VypisOsoby();

	try {
		cout << "tel. osoby s ID 3: " << telefonniSeznam.NajdiTelefon(3) << endl;
		cout << "tel. Jana Mala: " << telefonniSeznam.NajdiTelefon("Jana Mala") << endl;
		cout << "tel. osoby s ID 6: " << telefonniSeznam.NajdiTelefon(6) << endl;
		cout << "tel. " << telefonniSeznam.NajdiTelefon("") << endl;
	}
	catch (PrvekNenalezen &pn){
		cout << pn.GetMessage() << endl;
	}
	catch (NeplatnyArgument &na) {
		cout << na.GetMessage() << endl;
	}
}