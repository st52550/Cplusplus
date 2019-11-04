#ifndef VYJIMKY_H
#define VYJIMKY_H

#include <string>

struct Vyjimky {

};

struct PrvekNenalezen : public Vyjimky {
private:
	std::string _message;
public:
	PrvekNenalezen(std::string message) : _message(message) {}
	std::string GetMessage() const;
};

struct NeplatnyArgument : public Vyjimky {
private:
	std::string _message;
public:
	NeplatnyArgument(std::string message) : _message(message) {}
	std::string GetMessage() const;
};

#endif // !VYJIMKY_H

