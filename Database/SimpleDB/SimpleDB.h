#ifndef SIMPLEDB_H
#define SIMPLEDB_H

#include "Platform.h"

#include <functional>
#include <string>
#include <vector>

class Table;
class FieldObject;
class Object;

// Typ datového pole
enum struct FieldType {
	Integer,
	Double,
	String,
	Field
};

// Databáze
class DLL_SPEC Db {
private:
	std::string _database;
	std::vector<Table*> _tables;
public:
	// Otevøe databázi
	static Db* open(std::string database);
	// Uzavøe databázi (dealokuje pamìové prostøedky)
	void close();

	// Vytvoøí novou tabulku
	Table* createTable(std::string name, int fieldsCount, FieldObject** fields);
	// Otevøe existující tabulku
	Table* openTable(std::string name);
	// Otevøe tabulku (pokud neexistuje, vytvoøí automaticky novou)
	Table* openOrCreateTable(std::string name, int fieldsCount, FieldObject** fields);
	// Vypíše tabulky
	void showTables();

	// Alokuje objekt „int“
	static Object* Int(int value);
	// Alokuje objekt „double“
	static Object* Double(double value);
	// Alokuje objekt „string“
	static Object* String(std::string value);
	// Alokuje objekt „field“
	static FieldObject* Field(std::string name, FieldType type);
};
// --------------------------------------------------------
// Rozhraní definující podmínku – pouze pro bonusové metody
class DLL_SPEC Condition {
	virtual ~Condition() { }
	virtual bool matches(int fieldCount, FieldObject** fields, Object** row) const = 0;
};
// --------------------------------------------------------

// Rozhraní iterátoru (select)
class DLL_SPEC Iterator {
public:
	virtual ~Iterator();
	// Posun na další øádek (vrací true, pokud je iterátor platnı; logika podle Java Iterator)
	virtual bool moveNext() = 0;
	// Vrací pole Object* obsahující data øádku
	virtual Object** getRow() = 0;
	// Vrací interní rowId aktuálního øádku
	virtual int getRowId() = 0;
	// Uzavøe iterátor (dealokuje pamìové prostøedky)
	virtual void close() = 0;
};

// Tabulka
class DLL_SPEC Table {
private:
	std::string _databaseName;
	std::string _name;
	int _fieldsCount;
	int _rowCount;
	FieldObject** _definition;
	Object*** _data;

	class TableIterator : public Iterator {
	private:
		Table* _table;
		int _currentRowId;
	public:
		TableIterator(Table* table);
		// Posun na další øádek (vrací true, pokud je iterátor platnı; logika podle Java Iterator)
		bool moveNext();
		// Vrací pole Object* obsahující data øádku
		Object** getRow();
		// Vrací interní rowId aktuálního øádku
		int getRowId();
		// Uzavøe iterátor (dealokuje pamìové prostøedky)
		void close();
	};
public:
	Table(std::string databaseName, std::string name, int fieldsCount, FieldObject** definition);
	// Vloení nového øádku do tabulky (pole Object* (pro jednotlivé hodnoty sloupeèkù))
	void insert(Object** row);
	// Smazání vyrabného øádku z tabulky
	void remove(int rowid);

	// Select – vytvoøí iterátor k procházení tabulky
	Iterator* select();

	// Commit – pøenese zmìny z pamìti do datovıch souborù
	void commit();

	// Uzavøe tabulku (dealokuje pamìové prostøedky)
	void close();

	// Vrací poèet øádkù v tabulce
	int getRowCount() const;

	// Vrací pole FieldObject* popisující sloupeèky tabulky
	FieldObject** getFields() const;

	// Vrací poèet sloupeèkù
	int getFieldCount() const;

	// Vrací název tabulky
	std::string getName() const;

	// Pøiøadí tabulce název databáze
	void setDatabaseName(std::string databaseName);

	// ============== Bonusové metody: ================
		// Select s podmínkou
	Iterator* select(Condition* condition) { throw 0; }
	// Nalezení rowId s podmínkou
	int findRowId(Condition* condition) { throw 0; }
	// Update – aktualizuje øádky vyhovující podmínce, aktualizaci provádí funkce „callback“
	// callback na vstupu obdrí data øádku a vrací data
	void update(Condition* condition, std::function<void(Object**)> callback) { throw 0; }
};

// Polymorfní datovı objekt (reprezentuje jednu datovou hodnotu v tabulce)
// Rozhraní vyhovuje základním typùm int, double, string; pro typ „field“ je rozhraní rozšíøeno
class DLL_SPEC Object {
public:
	Object();
	virtual ~Object();

	// Gettery a settery podle typu
	// Jejich funkce je definována jen v pøípadì, e aktuální objekt je odpovídajícího typu
	// Automatické konverze v základním API nejsou vyadovány

	virtual std::string getString() const;
	virtual void setString(std::string value);

	virtual int getInt() const;
	virtual void setInt(int value);

	virtual double getDouble() const;
	virtual void setDouble(double value);

	// Vrací true, pokud aktuální objekt pøedstavuje danı typ
	virtual bool isType(FieldType type) const;
};


class DLL_SPEC IntObject : public Object {
private:
	int _value;
public:
	IntObject() : _value(0) {}
	IntObject(int v) : _value(v) {}
	int getInt() const override;
	void setInt(int value) override;
};

class DLL_SPEC DoubleObject : public Object {
private:
	double _value;
public:
	DoubleObject() : _value(0.0) {}
	DoubleObject(double v) : _value(v) {}
	double getDouble() const override;
	void setDouble(double value) override;
};

class DLL_SPEC StringObject : public Object {
private:
	std::string _value;
public:
	StringObject() : _value("") {}
	StringObject(std::string v) : _value(v) {}
	std::string getString() const override;
	void setString(std::string value) override;
};

// Objekt popisující sloupeèek „field“
class DLL_SPEC FieldObject : public Object {
private:
	std::string _name;
	FieldType _type;
public:
	FieldObject() {}
	FieldObject(std::string name, FieldType type) :_name(name), _type(type) {}

	virtual bool isType(FieldType type) const override;

	// Název sloupeèku
	std::string getName() const { return _name; }
	// Typ sloupeèku
	FieldType getType() const { return _type; }
};

#endif // !SIMPLEDB_H

