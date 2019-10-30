#ifndef TELEFONNISEZNAM_H
#define TELEFONNISEZNAM_H

#include "Osoba.h"
#include <string>

using namespace std;
using namespace Entity;

namespace Model {	
	struct TelefonniSeznam {
	private:
		struct PrvekSeznam {
			PrvekSeznam* dalsi;
			Osoba* data;
			PrvekSeznam() : dalsi(nullptr), data(nullptr) {}
		};

		PrvekSeznam* _zacatek;
	public:
		TelefonniSeznam();
		~TelefonniSeznam();
		void PridejOsobu(Osoba *o);
		void VypisOsoby();
		string NajdiTelefon(string jmeno) const;
		string NajdiTelefon(int id) const;
	};
}
#endif // !TELEFONNISEZNAM_H

