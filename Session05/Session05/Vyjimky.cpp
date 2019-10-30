#include "Vyjimky.h"

#include <string>

using namespace std;

string NeplatnyArgument::GetMessage() const {
	return _message;
}

string PrvekNenalezen::GetMessage() const {
	return _message;
}