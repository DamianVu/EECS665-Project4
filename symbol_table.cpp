#include "symbol_table.hpp"
#include <iostream>
#include <utility>
namespace LILC{

ScopeTable::ScopeTable(){
	map = new std::unordered_map<std::string, SymbolTableEntry *>();
}

void ScopeTable::printAll() {
	for (std::pair<std::string, SymbolTableEntry *> e : *map) {
		std::cout << "Name: " << e.first << ", Type: " << e.second->getType() << "\n";
	}
}

bool ScopeTable::findByName(std::string name) {
	return (map->count(name) > 0);
}

bool ScopeTable::addItem(std::string id, std::string type) {
	if (map->count(id) == 0) {
		SymbolTableEntry * temp = new SymbolTableEntry();
		temp->setType(type);
		map->insert({{id, temp}});
		temp = nullptr;
	} else {
		// maybe put an error...
		return false;
	}
}

SymbolTable::SymbolTable(){
	scopeTables = new std::list<ScopeTable *>();
	line = 0;
	charPos = 0;
};

void SymbolTable::addScope() {
	scopeTables->push_back(new ScopeTable());
}

void SymbolTable::dropScope() {
	scopeTables->pop_back();
}

bool SymbolTable::addItem(std::string id, std::string type) {
	return scopeTables->back()->addItem(id, type);
}

bool SymbolTable::findByName(std::string name) {
	for (ScopeTable* table: *scopeTables) {
		if (table->findByName(name)) return true;
	}
	return false;
}

void SymbolTable::reportError(std::string message) {
	std::cerr << message << "\n";
}

void SymbolTable::printAll() {
	int i = 0;
	for (ScopeTable* table : *scopeTables) {
		std::cout << "Scope " << i << ":\n";
		table->printAll();
	}
}

void SymbolTable::addLine(int lines) {
	line += lines;
}

void SymbolTable::addChar(int chars) {
	charPos += chars;
}


}
