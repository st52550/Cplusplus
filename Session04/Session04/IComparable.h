#ifndef ICOMPARABLE_H
#define ICOMPARABLE_H

#include "IObject.h"

struct IComparable : public IObject {
public:
	virtual int compareTo(IComparable* obj) const = 0;
};

#endif // !ICOMPARABLE_H

