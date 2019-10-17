#ifndef OBJEKT_H
#define OBJEKT_H

class Objekt
{
private:
	int id;
	double x;
	double y;
public:
	Objekt(int id);
	virtual ~Objekt();
	int GetId() const;
	void SetId(int id);
	double GetX() const;
	void SetX(double x);
	double GetY() const;
	void SetY(double y);
};
#endif // !OBJEKT_H

