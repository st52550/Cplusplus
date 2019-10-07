#pragma once
#ifndef UCTENKA_H
struct Uctenka {
private:
	int cisloUctenky;
	double castka;
	double dph;

public:
	int GetCisloUctenky() const;
	void SetCisloUctenky(int cisloUctenky);
	double GetCastka() const;
	void SetCastka(double castka);
	double GetDph() const;
	void SetDph(double dph);

};
#endif // !UCTENKA_H

