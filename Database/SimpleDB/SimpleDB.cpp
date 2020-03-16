#include "SimpleDB.h"
#include "Helpful.h"

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

// Otevøe databázi
Db* Db::open(std::string database) {
	Db* db = new Db();
	bool directoryCreated;
	vector<string> tableSchema;
	vector<string> tableData;
	string schemaFilename;
	string dataFilename;
	string filename;
	string path = "./data";

	if (fs::exists(fs::path(path))) {
		directoryCreated = true;
	} else {
		directoryCreated = false;
	}

	for (const auto& entry : fs::directory_iterator(path)) {
		filename = entry.path().filename().string();
		if (filename.find(database + "_") != string::npos) {
			if (filename.find(".schema") != string::npos) {
				tableSchema.push_back(filename);
			} else if (filename.find(".dat") != string::npos) {
				tableData.push_back(filename);
			}
		}
	}

	if (!tableSchema.empty()) {
		cout << "Reading database " << database << endl;
		string token;
		string stringValue;
		string tableName;
		int stringSize;
		int rowCount = 0;
		int fieldsCount = 0;
		int enumIndex;
		int intValue;
		double doubleValue;
		FieldObject** definition = nullptr;
		Object** row = nullptr;
		Table* table = nullptr;

		for (size_t i = 0; i < tableSchema.size(); i++) {			
			schemaFilename = path + "/" + tableSchema[i];
			ifstream in {};
			in.open(schemaFilename, ios::binary);

			if (in.is_open()) {
				in.read((char*)&stringSize, sizeof(stringSize));
				tableName.resize(stringSize);
				in.read((char*)&tableName[0], stringSize);
				in.read((char*)&rowCount, sizeof(rowCount));
				in.read((char*)&fieldsCount, sizeof(fieldsCount));

				definition = new FieldObject * [fieldsCount];
				for (size_t i = 0; i < fieldsCount; i++) {
					in.read((char*)&stringSize, sizeof(stringSize));
					stringValue.resize(stringSize);
					in.read((char*)&stringValue[0], stringSize);
					in.read((char*)&enumIndex, sizeof(enumIndex));

					definition[i] = db->Field(stringValue, FieldType(enumIndex));
				}

				table = db->createTable(tableName, fieldsCount, definition);
				table->setDatabaseName(database);
				in.close();
			} else {
				cerr << "Can't open schema file.";
			}

			token = tableSchema[i].substr(0, tableSchema[i].find(".")) + "_Data.dat";

			for (size_t j = 0; j < tableData.size(); j++) {
				if (tableData[j] == token) {
					dataFilename = path + "/" + tableData[j];
					in.open(dataFilename, ios::binary);
					if (in.is_open()) {					
						for (size_t k = 0; k < rowCount; k++) {
							row = new Object * [fieldsCount];
							for (size_t l = 0; l < fieldsCount; l++) {
								if (definition[l]->isType(FieldType::Integer)) {
									in.read((char*)&intValue, sizeof(intValue));
									row[l] = db->Int(intValue);
								} else if (definition[l]->isType(FieldType::Double)) {
									in.read((char*)&doubleValue, sizeof(doubleValue));
									row[l] = db->Double(doubleValue);
								} else if (definition[l]->isType(FieldType::String)) {
									in.read((char*)&stringSize, sizeof(stringSize));
									stringValue.resize(stringSize);
									in.read((char*)&stringValue[0], stringSize);
									row[l] = db->String(stringValue);
								}
							}

							table->insert(row);
						}
						in.close();
					} else {
						cerr << "Can't open data file.";
					}
					break;
				}
			}
		}
	} else {
		db->_database = database;
		cout << "Creating new database " << database << endl;
	}

	return db;
}
// Uzavøe databázi (dealokuje pamìové prostøedky)
void Db::close() {
	Table* table;
	for (size_t i = 0; i < _tables.size(); i++) {
		table = _tables[i];
		table->close();
	}
	delete this;
}

// Vypíše tabulky
void Db::showTables() {
	for (size_t i = 0; i < _tables.size(); i++) {
		cout << _tables[i]->getName() << endl;
	}
}

// Vytvoøí novou tabulku
Table* Db::createTable(std::string name, int fieldsCount, FieldObject** fields) {
	for (size_t i = 0; i < _tables.size(); i++) {
		if (_tables[i]->getName() == name) {
			throw std::invalid_argument("Table already exists.");
		}
	}

	Table* newTable = new Table(_database, name, fieldsCount, fields);
	_tables.push_back(newTable);

	return newTable;
}

// Otevøe existující tabulku
Table* Db::openTable(std::string name) {
	for (size_t i = 0; i < _tables.size(); i++) {
		if (_tables[i]->getName() == name) {
			return _tables[i];
		}
	}

	throw std::invalid_argument("Table doesn't exist. ");
}

// Otevøe tabulku (pokud neexistuje, vytvoøí automaticky novou)
Table* Db::openOrCreateTable(std::string name, int fieldsCount, FieldObject** fields) {
	try {
		return Db::openTable(name);
	} catch (const exception & e) {}

	Table* newTable = Db::createTable(name, fieldsCount, fields);
	cout << "New table was created." << endl;
	return newTable;
}

// Alokuje objekt „int“
Object* Db::Int(int value) {
	IntObject* intObject = new IntObject(value);
	return intObject;
}

// Alokuje objekt „double“
Object* Db::Double(double value) {
	DoubleObject* doubleObject = new DoubleObject(value);
	return doubleObject;
}

// Alokuje objekt „string“
Object* Db::String(std::string value) {
	StringObject* stringObject = new StringObject(value);
	return stringObject;
}

// Alokuje objekt „field“
FieldObject* Db::Field(std::string name, FieldType type) {
	FieldObject* fieldObject = new FieldObject(name, type);
	return fieldObject;
}

// --------------------------------------------------------
// Rozhraní definující podmínku – pouze pro bonusové metody
bool Condition::matches(int fieldCount, FieldObject** fields, Object** row) const {
	return true;
}
// --------------------------------------------------------

Iterator::~Iterator() { }

Table::TableIterator::TableIterator(Table* table) {
	this->_table = table;
	_currentRowId = 0;
}

// Posun na další øádek (vrací true, pokud je iterátor platný; logika podle Java Iterator)
bool Table::TableIterator::moveNext() {
	return _currentRowId < _table->_rowCount;
}

// Vrací pole Object* obsahující data øádku
Object** Table::TableIterator::getRow() {
	Object** row = _table->_data[_currentRowId];
	_currentRowId++;
	return row;
}

// Vrací interní rowId aktuálního øádku
int Table::TableIterator::getRowId() { return _currentRowId; }

// Uzavøe iterátor (dealokuje pamìové prostøedky)
void Table::TableIterator::close() {
	delete this;
}

Table::Table(string databaseName, string name, int fieldsCount, FieldObject** definition) {
	this->_databaseName = databaseName;
	this->_name = name;
	this->_fieldsCount = fieldsCount;
	this->_definition = definition;
	this->_rowCount = 0;
}

// Vložení nového øádku do tabulky (pole Object* (pro jednotlivé hodnoty sloupeèkù))
void Table::insert(Object** row) {
	if (_rowCount == 0) {
		_data = new Object * *[1];
		_data[0] = row;
		_rowCount++;
	} else {
		unsigned int newSize = _rowCount + 1;
		Object*** newData = new Object * *[newSize];

		for (size_t i = 0; i < newSize - 1; i++) {
			newData[i] = new Object * [_fieldsCount];
			for (size_t j = 0; j < _fieldsCount; j++) {
				if (_definition[j]->isType(FieldType::Integer)) {
					newData[i][j] = new IntObject(_data[i][j]->getInt());
				} else if (_definition[j]->isType(FieldType::Double)){
					newData[i][j] = new DoubleObject(_data[i][j]->getDouble());
				} else if (_definition[j]->isType(FieldType::String)) {
					newData[i][j] = new StringObject(_data[i][j]->getString());
				}
				delete _data[i][j];
			}
			delete[] _data[i];
		}
		delete _data;

		_data = newData;
		_data[_rowCount] = row;
		_rowCount++;
	}
}

// Smazání vyrabného øádku z tabulky
void Table::remove(int rowid) {
	if (_rowCount > 0 && rowid <= _rowCount && rowid > 0) {
		unsigned int newSize = _rowCount - 1;
		unsigned int rowIndex = rowid - 1;
		int index = 0;
		Object*** newData = new Object * *[newSize];

		for (size_t i = 0; i < _rowCount; i++) {
			if (i != rowIndex) {
				newData[index] = new Object * [_fieldsCount];
				for (size_t j = 0; j < _fieldsCount; j++) {
					if (_definition[j]->isType(FieldType::Integer)) {
						newData[index][j] = new IntObject(_data[i][j]->getInt());
					} else if (_definition[j]->isType(FieldType::Double)) {
						newData[index][j] = new DoubleObject(_data[i][j]->getDouble());
						} else if (_definition[j]->isType(FieldType::String)) {
							newData[index][j] = new StringObject(_data[i][j]->getString());
						}
						delete _data[i][j];
					}
					index++;
				} else {
					for (size_t j = 0; j < _fieldsCount; j++) {
						delete _data[i][j];
					}
				}
				delete[] _data[i];
			}
			delete _data;

			_data = newData;
			_rowCount--;		
	} else {
		throw std::out_of_range("Row doesn't exist");
	}
}

// Select – vytvoøí iterátor k procházení tabulky
Iterator* Table::select() {
	TableIterator* iterator = new TableIterator(this);
	return dynamic_cast<Iterator*>(iterator);
}

// Commit – pøenese zmìny z pamìti do datových souborù
void Table::commit() {
	string directory = "./data";
	bool directoryCreated;
	string schemaFilename;
	int intValue;
	double doubleValue;
	string stirngValue;
	int stringSize;
	int enumIndex;

	if (!fs::exists(fs::path(directory))) {
		if (fs::create_directories(directory)) {
			directoryCreated = true;
		}
	} else {
		directoryCreated = true;
	}

	if (directoryCreated) {
		schemaFilename = directory + "/" + _databaseName + "_" + _name + ".schema";
	} else {
		schemaFilename = _databaseName + "_" + _name + ".schema";
	}

	ofstream out{};	
	out.open(schemaFilename, ios::binary);

	if (out.is_open()) {
		// Save table schema
		stirngValue = _name;
		stringSize = _name.size();
		out.write((char*)&stringSize, sizeof(stringSize));
		out.write(stirngValue.c_str(), stringSize);
		out.write((char*)&_rowCount, sizeof(_rowCount));
		out.write((char*)&_fieldsCount, sizeof(_fieldsCount));
		for (size_t i = 0; i < _fieldsCount; i++) {
			stirngValue = _definition[i]->getName();
			stringSize = stirngValue.size();
			out.write((char*)&stringSize, sizeof(stringSize));
			out.write(stirngValue.c_str(), stringSize);

			enumIndex = static_cast<int>(_definition[i]->getType());
			out.write((char*)&enumIndex, sizeof(enumIndex));
		}

		out.close();
	} else {
		cerr << "Can't open file." << endl;
	}

	// Save table data
	string dataFilename;

	if (directoryCreated) {
		dataFilename = directory + "/" + _databaseName + "_" + _name + "_Data.dat";
	} else {
		dataFilename = _databaseName + "_" + _name + "_Data.dat";
	}

	out.open(dataFilename, ios::binary);

	if (out.is_open()) {
		for (size_t i = 0; i < _rowCount; i++) {
			for (size_t j = 0; j < _fieldsCount; j++) {
				if (_definition[j]->isType(FieldType::Integer)) {
					intValue = _data[i][j]->getInt();
					out.write((char*)&intValue, sizeof(intValue));
				} else if (_definition[j]->isType(FieldType::Double)) {
					doubleValue = _data[i][j]->getDouble();
					out.write((char*)&doubleValue, sizeof(doubleValue));
				} else if (_definition[j]->isType(FieldType::String)) {
					stirngValue = _data[i][j]->getString();
					stringSize = stirngValue.size();
					out.write((char*)&stringSize, sizeof(stringSize));
					out.write(stirngValue.c_str(), stringSize);
				}
			}
		}

		out.close();
	} else {
		cerr << "Can't open file." << endl;
	}
}

// Uzavøe tabulku (dealokuje pamìové prostøedky)
void Table::close() {
	for (size_t i = 0; i < _fieldsCount; i++) {
		delete _definition[i];
	}

	delete _definition;

	for (size_t i = 0; i < _rowCount; i++) {
		for (size_t j = 0; j < _fieldsCount; j++) {
			delete _data[i][j];
		}
		delete[] _data[i];
	}

	delete _data;
	delete this;
}

// Vrací poèet øádkù v tabulce
int Table::getRowCount() const { return _rowCount; }

// Vrací pole FieldObject* popisující sloupeèky tabulky
FieldObject** Table::getFields() const { return _definition; }

// Vrací poèet sloupeèkù
int Table::getFieldCount() const { return _fieldsCount; }

// Vrací název tabulky
std::string Table::getName() const { return _name; }

// Pøiøadí tabulce název databáze
void Table::setDatabaseName(std::string databaseName) { this->_databaseName = databaseName; }

Object::Object() { }

Object::~Object() { }

// Gettery a settery podle typu
// Jejich funkce je definována jen v pøípadì, že aktuální objekt je odpovídajícího typu
// Automatické konverze v základním API nejsou vyžadovány

std::string Object::getString() const { 
	if (this->isType(FieldType::String)) {
		return this->getString();
	}
	cerr << "Actual object isn't String.";
}

void Object::setString(std::string value) {
	if (this->isType(FieldType::String)) {
		this->setString(value);
	}
	cerr << "Actual object isn't String.";
}

int Object::getInt() const {
	if (this->isType(FieldType::Integer)) {
		return this->getInt();
	}
	cerr << "Actual object isn't Integer.";
}

void Object::setInt(int value) {
	if (this->isType(FieldType::Integer)) {
		return this->setInt(value);
	}
	cerr << "Actual object isn't Integer.";
}

double Object::getDouble() const { 
	if (this->isType(FieldType::Double)) {
		return this->getDouble();
	}
	cerr << "Actual object isn't Double.";
}

void Object::setDouble(double value) {
	if (this->isType(FieldType::Double)) {
		return this->setDouble(value);
	}
	cerr << "Actual object isn't Double.";
}

// Vrací true, pokud aktuální objekt pøedstavuje daný typ
bool Object::isType(FieldType type) const {	
	if (this->isType(type)) {
		return true;
	}
	return false; 
}

bool FieldObject::isType(FieldType type) const {
	if (this->_type == type) {
		return true;
	}
	return false;
}

int IntObject::getInt() const { return _value; }

void IntObject::setInt(int value) { this->_value = value; }

double DoubleObject::getDouble() const { return _value; }

void DoubleObject::setDouble(double value) { this->_value = value; }

std::string StringObject::getString() const { return _value; }

void StringObject::setString(std::string value) { this->_value = value; }