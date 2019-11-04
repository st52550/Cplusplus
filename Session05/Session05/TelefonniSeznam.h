#ifndef TELEFONNISEZNAM_H
#define TELEFONNISEZNAM_H

#include "Osoba.h"
#include <string>

namespace Model {	
	struct TelefonniSeznam {
	private:
		struct PrvekSeznam {
			PrvekSeznam* dalsi;
			Entity::Osoba* data;
			PrvekSeznam() : dalsi(nullptr), data(nullptr) {}
		};

		PrvekSeznam* _zacatek;
	public:
		TelefonniSeznam();
		~TelefonniSeznam();
		void PridejOsobu(Entity::Osoba *o);
		void VypisOsoby();
		std::string NajdiTelefon(std::string jmeno) const;
		std::string NajdiTelefon(int id) const;
	};
}
#endif // !TELEFONNISEZNAM_H

