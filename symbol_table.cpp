#include "symbol_table.hpp"
namespace LILC{

ScopeTable::ScopeTable(){
	map = new std::unordered_map<std::string, SymbolTableEntry *>();
}

SymbolTable::SymbolTable(){
	//TODO: implement the list of hashtables
	// approach to building a symbol table
	scopeTables = new std::list<ScopeTable *>();
};

}
