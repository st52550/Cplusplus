#ifndef IOBJECT_H
#define IOBJECT_H

#include <string>

struct IObject {
public:
	virtual std::string toString() const = 0;
};
#endif // !IOBJECT_H

