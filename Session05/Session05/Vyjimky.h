#ifndef VYJIMKY_H
#define VYJIMKY_H

#include <string>

using namespace std;

struct Vyjimky {

};

struct PrvekNenalezen : public Vyjimky {
private:
	string _message;
public:
	PrvekNenalezen(string message) : _message(message) {}
	string GetMessage() const;
};

struct NeplatnyArgument : public Vyjimky {
private:
	string _message;
public:
	NeplatnyArgument(string message) : _message(message) {}
	string GetMessage() const;
};

#endif // !VYJIMKY_H

