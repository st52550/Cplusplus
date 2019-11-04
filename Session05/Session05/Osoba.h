#ifndef OSOBA_H
#define OSOBA_H

#include <string>

namespace Entity {
	struct Osoba {
	private:
		std::string _jmeno;
		std::string _telefon;
		int _id;
	public:
		Osoba(std::string jmeno, std::string telefon, int id);
		std::string GetJmeno() const;
		std::string GetTelefon() const;
		int GetId() const;
	};
}

#endif // !OSOBA_H

