#ifndef DATUM_H
#define DATUM_H

#include <iostream>

struct Datum {
private:
	int _den;
	int _mesic;
	int _rok;
public:
	Datum();
	Datum(int den, int mesic, int rok);
	int GetDen() const;
	void SetDen(int den);
	int GetMesic() const;
	void SetMesic(int mesic);
	int GetRok() const;
	void SetRok(int rok);
};

#endif // !DATUM_H

std::ostream& operator<<(std::ostream& os, const Datum& datum);
std::istream& operator>>(std::istream& is, Datum& datum);