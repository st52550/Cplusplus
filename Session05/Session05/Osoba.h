#ifndef OSOBA_H
#define OSOBA_H

#include <string>

using namespace std;

namespace Entity {
	struct Osoba {
	private:
		string _jmeno;
		string _telefon;
		int _id;
	public:
		Osoba(string jmeno, string telefon, int id);
		string GetJmeno() const;
		string GetTelefon() const;
		int GetId() const;
	};
}

#endif // !OSOBA_H

