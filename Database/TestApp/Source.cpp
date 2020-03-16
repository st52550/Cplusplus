#include "SimpleDB.h"
#include "Helpful.h"
#include <iostream>
#include <sstream>

using namespace std;

enum struct Commands {
	OpenDatabase,
	CloseDatabase,
	ShowTables,
	CreateTable,
	UpdateTable,
	SelectFrom,
	InsertInto,
	JoinOn,
	RemoveFrom,
	Commit,
	Exit,
	Incorrect
};

Commands compareCommand(string const& input) {
	if (input == "OPEN DATABASE") return Commands::OpenDatabase;
	if (input == "CLOSE DATABASE") return Commands::CloseDatabase;
	if (input == "SHOW TABLES") return Commands::ShowTables;
	if (input == "CREATE TABLE") return Commands::CreateTable;
	if (input == "UPDATE TABLE") return Commands::UpdateTable;
	if (input == "SELECT FROM") return Commands::SelectFrom;
	if (input == "INSERT INTO") return Commands::InsertInto;
	if (input == "JOIN ON") return Commands::JoinOn;
	if (input == "REMOVE FROM") return Commands::RemoveFrom;
	if (input == "COMMIT") return Commands::Commit;
	if (input == "EXIT") return Commands::Exit;
	return Commands::Incorrect;
}

string getColumnValue(string column) {
	auto start = column.find("(") + 1;
	auto end = column.find(")");
	return column.substr(start, end - start);
}

int main() {
	Db* database = nullptr;
	string command;
	cout << "Databazova aplikace (Josef Plasil)\n" << "----------------------------------" << endl;
	cout << "Instrukce:" << endl <<
		"OPEN DATABASE  - Otevre existujici databazi nebo vytvori novou databazi" << endl <<
		"CLOSE DATABASE - Zavre aktualni databazi" << endl <<
		"SHOW TABLES    - Vypise nazvy vsech tabulek v databazi" << endl <<
		"CREATE TABLE   - Vytvori novou tabulku. Sloupce tabulky zadavajte dle platne syntaxe:" << endl <<
		"                 nazev_sloupce(DATOVY_TYP) -> Pr. Id(INTEGER)" << endl <<
		"                 Platne datove typy: INTEGER, DOUBLE, STRING" << endl <<
		"                 Maximalni pocet sloupcu tabulky je pet. Vice sloupcu oddelujeme carkou bez mezery." << endl <<
		"                 Pr. Id(INTEGER),Name(String),..." << endl <<
		"UPDATE TABLE   - Aktualizuje hodnotu sloupce v tabulce" << endl <<
		"SELECT FROM    - Vypise data v tabulce" << endl <<
		"JOIN ON        - Vrati data ze dvou tabulek na zaklade relacni tabulky." << endl <<
		"                 Relacni tabulka musi mit nazev slozeny z nazvu prvni tabulky a nazvu druhe tabulky!" << endl <<
		"INSERT INTO    - Vlozi novy radek do tabulky. Hodnoty sloupcu zadavejte dle platne syntaxe:" << endl <<
		"                 nazev_sloupce(hodnota) -> Pr. Id(1)" << endl <<
		"                 Vice sloupcu oddelujeme carkou bez mezery." << endl <<
		"                 Pr. Id(1),Name(Petr),..." << endl <<
		"REMOVE FROM    - Odstrani radek z tabulky dle cisla radku." << endl <<
		"COMMIT         - Ulozi zmeny v tabulce. Neulozena data budou ztracena!" << endl <<
		"EXIT           - Ukonci aplikaci" << endl << endl;
	cout << "(Nazev testovaci databaze: TestDB)" << endl << endl;

	string databaseName;
	string tableName;
	string tableColumns;
	string column;
	string columnValue;
	string stringInput;
	bool checkInput = true;
	int rowNumber = 0;
	int fieldNumber = 0;
	vector<FieldObject*> fields;
	FieldObject** tableFields;
	vector<Object*> rowData;
	Object** tableRow;
	Table* table;

	do {
		cout << "Prikaz: ";
		getline(cin, command);
		switch (compareCommand(command)) {
		case Commands::OpenDatabase:		
			cout << "Zadejte nazev databaze: ";
			getline(cin, databaseName);
			if (!databaseName.empty()) {
				database = Db::open(databaseName);
			}
			else {
				cerr << "Chyba syntaxe." << endl;
			}
			break;		
		case Commands::CloseDatabase:		
			cout << "Zadejte nazev databaze: ";
			getline(cin, databaseName);
			if (!databaseName.empty()) {
				if (database != nullptr) {
					database->close();
					database = nullptr;
					cout << "Databaze byla zavrena." << endl;
				}
				else {
					cerr << "Neni otevrena zadna databaze." << endl;
				}
			}
			else {
				cerr << "Chyba syntaxe." << endl;
			}
			break;		
		case Commands::ShowTables:		
			if (database != nullptr) {
				database->showTables();
			}
			else {
				cerr << "Neni otevrena zadna databaze." << endl;
			}
			break;		
		case Commands::CreateTable:		
			if (database != nullptr) {
				cout << "Zadejte nazev tabulky: ";
				getline(cin, tableName);
				cout << "Zadejte sloupce tabulky: ";
				getline(cin, tableColumns);
				if (!tableName.empty() && !tableColumns.empty()) {
					stringstream ss(tableColumns);
					while (getline(ss, column, ',')) {
						columnValue = getColumnValue(column);
						if (columnValue == "INTEGER") {
							auto field = Db::Field(column.substr(0, column.find_last_of("(")), FieldType::Integer);
							fields.push_back(field);
						}
						else if (columnValue == "DOUBLE") {
							auto field = Db::Field(column.substr(0, column.find_last_of("(")), FieldType::Double);
							fields.push_back(field);
						}
						else if (columnValue == "STRING") {
							auto field = Db::Field(column.substr(0, column.find_last_of("(")), FieldType::String);
							fields.push_back(field);
						}
						else {
							cerr << "Chyba syntaxe." << endl;
							break;
						}
					}

					switch (fields.size()) {
					case 1:
						tableFields = combineToDefinition(fields[0]);
						database->openOrCreateTable(tableName, fields.size(), tableFields);
						cout << "Tabulka byla vytvorena." << endl;
						break;
					case 2:
						tableFields = combineToDefinition(fields[0], fields[1]);
						database->openOrCreateTable(tableName, fields.size(), tableFields);
						cout << "Tabulka byla vytvorena." << endl;
						break;
					case 3:
						tableFields = combineToDefinition(fields[0], fields[1], fields[2]);
						database->openOrCreateTable(tableName, fields.size(), tableFields);
						cout << "Tabulka byla vytvorena." << endl;
						break;
					case 4:
						tableFields = combineToDefinition(fields[0], fields[1], fields[2], fields[3]);
						database->openOrCreateTable(tableName, fields.size(), tableFields);
						cout << "Tabulka byla vytvorena." << endl;
						break;
					case 5:
						tableFields = combineToDefinition(fields[0], fields[1], fields[2], fields[3], fields[4]);
						database->openOrCreateTable(tableName, fields.size(), tableFields);
						cout << "Tabulka byla vytvorena." << endl;
						break;
					default:
						cerr << "Chyba syntaxe." << endl;
						break;
					}
				}
				else {
					cerr << "Chyba syntaxe." << endl;
				}
			}
			else {
				cerr << "Nejdrive otevrete databazi pomoci OPEN DATABASE." << endl;
			}
			break;		
		case Commands::UpdateTable:
			if (database != nullptr) {
				cout << "Zadejte nazev tabulky: ";
				getline(cin, tableName);
				if (!tableName.empty()) {
					try {
						table = database->openTable(tableName);
						cout << "Zadejte nazev sloupce: ";
						getline(cin, column);
						for (size_t i = 0; i < table->getFieldCount(); i++) {
							if (table->getFields()[i]->getName() == column) {
								checkInput = true;
								fieldNumber = i;
							}
							else {
								checkInput = false;
							}
						}
						if (checkInput) {
							cout << "Zadejte cislo radku: ";
							getline(cin, stringInput);
							for (size_t i = 0; i < stringInput.length(); i++) {
								if (isdigit(stringInput[i]) == false) {
									checkInput = false;
								}
								else {
									checkInput = true;
								}
							}
							if (checkInput) {
								rowNumber = stoi(stringInput);
								if (table->getRowCount() > 0 && rowNumber <= table->getRowCount() && rowNumber > 0) {
									auto iterator = table->select();
									while (iterator->moveNext()) {
										auto row = iterator->getRow();
										if (iterator->getRowId() == rowNumber) {
											cout << "Zadejte novou hodnotu: ";
											getline(cin, stringInput);
											if (!stringInput.empty()) {
												if (table->getFields()[fieldNumber]->isType(FieldType::Integer)) {
													try {
														row[fieldNumber]->setInt(stoi(stringInput));
														cout << "Hodnota byla upravena." << endl;
														break;
													}
													catch (const std::exception&) {
														cerr << "Chybny vstup." << endl;
													}
												}
												else if (table->getFields()[fieldNumber]->isType(FieldType::Double)) {
													try {
														row[fieldNumber]->setDouble(stod(stringInput));
														cout << "Hodnota byla upravena." << endl;
														break;
													}
													catch (const std::exception&) {
														cerr << "Chybny vstup." << endl;
													}
												}
												else if (table->getFields()[fieldNumber]->isType(FieldType::String)) {
													row[fieldNumber]->setString(stringInput);
													cout << "Hodnota byla upravena." << endl;
													break;
												}
											}
											else {
												cerr << "Chybny vstup." << endl;
												break;
											}
										}
									}
									iterator->close();
								}
								else {
									cerr << "Radek neexistuje." << endl;
									break;
								}
							}
							else {
								cerr << "Chybny vstup." << endl;
								break;
							}
						}
						else {
							cerr << "Sloupec v tabulce neexistuje." << endl;
							break;
						}
					}
					catch (const std::exception & e) {
						cerr << e.what() << endl;
					}
				}
				else {
					cerr << "Chyba syntaxe." << endl;
				}
			}
			else {
				cerr << "Nejdrive otevrete databazi pomoci OPEN DATABASE." << endl;
			}
			break;
		case Commands::SelectFrom:
			if (database != nullptr) {
				cout << "Zadejte nazev tabulky: ";
				getline(cin, tableName);
				if (!tableName.empty()) {
					try {
						table = database->openTable(tableName);
						cout << "Table : " << table->getName() << endl << "-----------------------------" << endl;
						for (size_t i = 0; i < table->getFieldCount(); i++) {
							cout << table->getFields()[i]->getName() << "\t";
						}
						cout << endl;
						auto iterator = table->select();
						while (iterator->moveNext()) {
							auto row = iterator->getRow();
							for (size_t i = 0; i < table->getFieldCount(); i++) {
								if (table->getFields()[i]->isType(FieldType::Integer)) {
									cout << row[i]->getInt() << "\t";
								}
								else if (table->getFields()[i]->isType(FieldType::Double)) {
									cout << row[i]->getDouble() << "\t";
								}
								else if (table->getFields()[i]->isType(FieldType::String)) {
									cout << row[i]->getString() << "\t";
								}
							}
							cout << endl;
						}
						iterator->close();
						cout << endl;
					}
					catch (const std::exception & e) {
						cerr << e.what() << endl;
					}
				}
				else {
					cerr << "Chyba syntaxe." << endl;
				}
			}
			else {
				cerr << "Nejdrive otevrete databazi pomoci OPEN DATABASE." << endl;
			}
			break;
		case Commands::InsertInto:
			if (database != nullptr) {
				cout << "Zadejte nazev tabulky: ";
				getline(cin, tableName);
				if (!tableName.empty()) {
					try {
						table = database->openTable(tableName);
						cout << "Zadejte hodnoty sloupcu: ";
						getline(cin, tableColumns);
						if (!tableColumns.empty()) {
							stringstream ss(tableColumns);
							while (getline(ss, column, ',')) {
								columnValue = getColumnValue(column);
								for (size_t i = 0; i < table->getFieldCount(); i++) {
									stringInput = column.substr(0, column.find_last_of("("));
									if (stringInput == table->getFields()[i]->getName()) {
										if (table->getFields()[i]->isType(FieldType::Integer)) {
											auto columnData = Db::Int(stoi(columnValue));
											rowData.push_back(columnData);
										}
										else if (table->getFields()[i]->isType(FieldType::Double)) {
											auto columnData = Db::Double(stod(columnValue));
											rowData.push_back(columnData);
										}
										else if (table->getFields()[i]->isType(FieldType::String)) {
											auto columnData = Db::String(columnValue);
											rowData.push_back(columnData);
										}
										else {
											cerr << "Chyba syntaxe." << endl;
											break;
										}
									}
								}
							}
							switch (rowData.size()) {
							case 1:
								tableRow = combineToRow(rowData[0]);
								table->insert(tableRow);
								cout << "Radek byl pridan." << endl;
								break;
							case 2:
								tableRow = combineToRow(rowData[0], rowData[1]);
								table->insert(tableRow);
								cout << "Radek byl pridan." << endl;
								break;
							case 3:
								tableRow = combineToRow(rowData[0], rowData[1], rowData[2]);
								table->insert(tableRow);
								cout << "Radek byl pridan." << endl;
								break;
							case 4:
								tableRow = combineToRow(rowData[0], rowData[1], rowData[2], rowData[3]);
								table->insert(tableRow);
								cout << "Radek byl pridan." << endl;
								break;
							case 5:
								tableRow = combineToRow(rowData[0], rowData[1], rowData[2], rowData[3], rowData[4]);
								table->insert(tableRow);
								cout << "Radek byl pridan." << endl;
								break;
							default:
								cerr << "Chyba syntaxe." << endl;
								break;
							}
						}
						else {
							cerr << "Chyba syntaxe." << endl;
						}
					}
					catch (const std::exception & e) {
						cerr << e.what() << endl;
					}
				}
				else {
					cerr << "Chyba syntaxe." << endl;
				}
			}
			else {
				cerr << "Nejdrive otevrete databazi pomoci OPEN DATABASE." << endl;
			}
			break;
		case Commands::JoinOn:
			if (database != nullptr) {
				cout << "Zadejte nazev relacni tabulky: ";
				getline(cin, tableName);
				if (!tableName.empty()) {
					try {
						table = database->openTable(tableName);
						
						Table* table1;
						Table* table2;
						int index1;
						int index2;
						bool relation = false;

						cout << "Zadejte nazev prvni tabulky relace: ";
						getline(cin, tableName);
						try {
							table1 = database->openTable(tableName);
							for (size_t i = 0; i < table1->getFieldCount(); i++) {
								if (table->getFields()[0]->getName() == table1->getFields()[i]->getName()) {
									index1 = i;
								}
							}
							cout << "Zadejte nazev druhe tabulky relace: ";
							getline(cin, tableName);
							try {
								table2 = database->openTable(tableName);
								if (table->getName() == (table1->getName() + table2->getName()))
								{
									relation = true;
								}
								for (size_t i = 0; i < table2->getFieldCount(); i++) {
									if (table->getFields()[1]->getName() == table2->getFields()[i]->getName()) {
										index2 = i;
									}
								}
								if (relation) {
									cout << "\nTable : " << table->getName() << endl << "-------------------" << endl;
									for (size_t i = 0; i < table1->getFieldCount(); i++) {
										cout << table1->getFields()[i]->getName() << "\t";
									}
									for (size_t i = 0; i < table2->getFieldCount(); i++) {
										cout << table2->getFields()[i]->getName() << "\t";
									}
									cout << endl;

									auto itTable = table->select();
									while (itTable->moveNext()) {
										auto rowTable = itTable->getRow();

										auto itTable1 = table1->select();
										while (itTable1->moveNext()) {
											auto rowTable1 = itTable1->getRow();
											if (rowTable[0]->getInt() == rowTable1[index1]->getInt()) {
												for (size_t i = 0; i < table1->getFieldCount(); i++) {
													if (table1->getFields()[i]->isType(FieldType::Integer)) {
														cout << rowTable1[i]->getInt() << "\t";
													}
													else if (table1->getFields()[i]->isType(FieldType::Double)) {
														cout << rowTable1[i]->getDouble() << "\t";
													}
													else if (table1->getFields()[i]->isType(FieldType::String)) {
														cout << rowTable1[i]->getString() << "\t";
													}
												}
											}
										}
										itTable1->close();

										auto itTable2 = table2->select();
										while (itTable2->moveNext()) {
											auto rowTable2 = itTable2->getRow();
											if (rowTable[1]->getInt() == rowTable2[index2]->getInt()) {
												for (size_t i = 0; i < table2->getFieldCount(); i++) {
													if (table2->getFields()[i]->isType(FieldType::Integer)) {
														cout << rowTable2[i]->getInt() << "\t";
													}
													else if (table2->getFields()[i]->isType(FieldType::Double)) {
														cout << rowTable2[i]->getDouble() << "\t";
													}
													else if (table2->getFields()[i]->isType(FieldType::String)) {
														cout << rowTable2[i]->getString() << "\t";
													}
												}
											}
										}
										itTable2->close();
										cout << endl;
									}
									itTable->close();
									cout << endl;
								}
								else {
									cerr << "Mezi tabulkami neni relace." << endl;
								}
							}
							catch (const std::exception & e) {
								cerr << e.what() << endl;
							}
						}
						catch (const std::exception & e) {
							cerr << e.what() << endl;
						}
					}
					catch (const std::exception & e) {
						cerr << e.what() << endl;
					}
				}
				else {
					cerr << "Chyba syntaxe." << endl;
				}
			} else {
				cerr << "Nejdrive otevrete databazi pomoci OPEN DATABASE." << endl;
			}
			break;
		case Commands::RemoveFrom:
			if (database != nullptr) {
				cout << "Zadejte nazev tabulky: ";
				getline(cin, tableName);
				if (!tableName.empty()) {
					try {
						table = database->openTable(tableName);
						cout << "Zadejte cislo radku: ";
						getline(cin, stringInput);
						if (!stringInput.empty()) {
							try {
								table->remove(stoi(stringInput));
								cout << "Row " << stringInput << " was deleted.\n" << endl;
							}
							catch (const std::exception & e) {
								cout << e.what() << endl;
							}
						}
						else {
							cerr << "Chyba syntaxe." << endl;
						}
					}
					catch (const std::exception & e) {
						cerr << e.what() << endl;
					}
				}
				else {
					cerr << "Chyba syntaxe." << endl;
				}
			}
			else {
				cerr << "Nejdrive otevrete databazi pomoci OPEN DATABASE." << endl;
			}
			break;
		case Commands::Commit:
			if (database != nullptr) {
				cout << "Zadejte nazev tabulky: ";
				getline(cin, tableName);
				if (!tableName.empty()) {
					try {
						table = database->openTable(tableName);
						table->commit();
						cout << "Tabulka byla ulozena." << endl;
					}
					catch (const std::exception & e) {
						cerr << e.what() << endl;
					}
				}
				else {
					cerr << "Chyba syntaxe." << endl;
				}
			}
			else {
				cerr << "Nejdrive otevrete databazi pomoci OPEN DATABASE." << endl;
			}
			break;
		case Commands::Exit:
			if (database != nullptr) {
				database->close();
			}
			break;
		default:
			cout << "Chybny prikaz." << endl;
			break;
		}
	} while (command != "EXIT");

	return 0;
}