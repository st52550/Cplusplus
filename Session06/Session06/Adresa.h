#ifndef ADRESA_H
#define ADRESA_H

#include <string>
#include <iostream>

struct Adresa {
private:
	std::string _ulice;
	std::string _mesto;
	int _psc;
public:
	Adresa();
	Adresa(std::string ulice, std::string mesto, int psc);
	std::string GetUlice() const;
	void SetUlice(std::string ulice);
	std::string GetMesto() const;
	void SetMesto(std::string mesto);
	int GetPsc() const;
	void SetPsc(int psc);
};

std::ostream& operator<<(std::ostream& os, const Adresa& adresa);
std::istream& operator>>(std::istream& is, Adresa& adresa);

#endif // !ADRESA_H

