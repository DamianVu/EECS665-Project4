#ifndef LILC_SYMBOL_TABLE_HPP
#define LILC_SYMBOL_TABLE_HPP
#include <unordered_map>
#include <list>

namespace LILC{

//A single entry for one name in the symbol table
class SymbolTableEntry{
	//TODO: Add type, kind, etc. instance variables
	//TODO: add getters/setters for type, kind, etc.
};

//A single 
class ScopeTable{
	public:
		ScopeTable();
		//TODO: add functions for looking up symbols
		// and/or returning information to indicate
		// that the symbol does not exist within 
		// the current scope
	private:
		std::unordered_map<std::string, SymbolTableEntry *>* map;
};

class SymbolTable{
	public:
		SymbolTable();
		//TODO: add functions to create a new scope
		// table when a new scope is entered, 
		// drop a scope table when a scope is finished,
		// etc.
	private:
		std::list<ScopeTable *> * scopeTables;
};

}
#endif
