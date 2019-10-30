#include "TelefonniSeznam.h"
#include "Osoba.h"
#include "Vyjimky.h"

#include <string>
#include <iostream>

using namespace std;
using namespace Entity;
using namespace Model;

TelefonniSeznam::TelefonniSeznam() {
	_zacatek = nullptr;
}

TelefonniSeznam::~TelefonniSeznam() {
	PrvekSeznam* temp = _zacatek;

	while (temp != nullptr)
	{
		PrvekSeznam* naslednik = temp->dalsi;
		delete temp;
		temp = naslednik;
	}
}

void TelefonniSeznam::PridejOsobu(Osoba *o) {
	PrvekSeznam* prvekSeznamu = new PrvekSeznam();
	prvekSeznamu->data = o;

	if (_zacatek != nullptr)
	{
		PrvekSeznam* temp = _zacatek;

		while (temp->dalsi != nullptr)
		{
			temp = temp->dalsi;
		}

		temp->dalsi = prvekSeznamu;
	}
	else {
		_zacatek = prvekSeznamu;
	}
}

void TelefonniSeznam::VypisOsoby() {
	PrvekSeznam* temp = _zacatek;

	while (temp != nullptr)
	{
		cout << temp->data->GetJmeno() << endl;
		temp = temp->dalsi;
	}
}

string TelefonniSeznam::najdiTelefon(string jmeno) const {
	if (jmeno.empty())
	{
		throw NeplatnyArgument("Jmeno je prazdne");
	}

	PrvekSeznam* temp = _zacatek;

	while (temp != nullptr)
	{
		if (temp->data->GetJmeno() == jmeno) {
			return temp->data->GetTelefon();
		}

		temp = temp->dalsi;
	}

	throw PrvekNenalezen("Prvek se jmenem " + jmeno + " nenalezen");
}

string TelefonniSeznam::najdiTelefon(int id) const {
	if (id < 0)
	{
		throw NeplatnyArgument("ID " + to_string(id) + " je neplatne");
	}

	PrvekSeznam* temp = _zacatek;

	while (temp != nullptr)
	{
		if (temp->data->GetId() == id) {
			return temp->data->GetTelefon();
		}

		temp = temp->dalsi;
	}

	throw PrvekNenalezen("Prvek s ID " + to_string(id) + " nenalezen");
}