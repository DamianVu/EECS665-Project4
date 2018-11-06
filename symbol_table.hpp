#ifndef LILC_SYMBOL_TABLE_HPP
#define LILC_SYMBOL_TABLE_HPP
#include <unordered_map>
#include <list>

namespace LILC{

//A single entry for one name in the symbol table
class SymbolTableEntry{
	//TODO: Add type, kind, etc. instance variables
	//TODO: add getters/setters for type, kind, etc.
public:
	void setType(std::string type) {
		myType = type;
	}
	std::string getType() { return myType; }
	void setStructDecls(std::list<std::string> decls) {
		structDecls = decls;
	}
	std::list<std::string> getStructDecls() { return structDecls; }
private:
	std::string myType;
	std::list<std::string> structDecls;
};

//A single 
class ScopeTable{
	public:
		ScopeTable();
		//TODO: add functions for looking up symbols
		// and/or returning information to indicate
		// that the symbol does not exist within 
		// the current scope
		bool findByName(std::string name);
		std::string getTypeOf(std::string id);
		bool addItem(std::string id, std::string type);
		bool addStruct(std::string id, std::list<std::string> list);
		void printAll(); // Debug method
	private:
		std::unordered_map<std::string, SymbolTableEntry *>* map;
};

class SymbolTable{
	public:
		SymbolTable();
		void addScope();
		void dropScope();
		bool addItem(std::string id, std::string type);
		bool addStruct(std::string id, std::list<std::string> list);
		bool findByName(std::string name);
		std::string getTypeOf(std::string id);
		void reportError(std::string message);
		void printAll(); // Debug method
		void addLine(int lines);
		void addChar(int chars);
		void multiplyDeclaredId(char f);
		void undeclaredId(char f);
		void dotAccess(char f);
		void invalidStructField(char f);
		void nonFunctionVoid(char f);
		void invalidStructName(char f);
	private:
		std::list<ScopeTable *> * scopeTables;
		ScopeTable * getTableContaining(std::string id);
};

}
#endif
