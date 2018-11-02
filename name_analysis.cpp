#include "ast.hpp"
#include "symbol_table.hpp"

namespace LILC{

bool ASTNode::nameAnalysis(SymbolTable * symTab){
	std::cout << "[DELETE ME] Whoops, I'm the ASTNode"
		" base class nameAnalysis function."
		" I should have been overridden."
		" My function declaration should have"
		" probably even been pure virtual.\n";
	return true;
}

bool ProgramNode::nameAnalysis(SymbolTable * symTab){
	this->myDeclList->nameAnalysis(symTab);
}

bool DeclListNode::nameAnalysis(SymbolTable * symTab){
	bool result = true;
	for (std::list<DeclNode *>::iterator
		it=myDecls->begin();
		it != myDecls->end(); ++it){

	  DeclNode * elt = *it;
	  result = result && elt->nameAnalysis(symTab);
	}
}

bool VarDeclNode::nameAnalysis(SymbolTable * symTab){
	std::cout << "[DELETE ME] I'm a varDecl. "
		" you should add the information from my"
		" subtree to the to the symbol table"
		" as a new entry in the current scope table\n";
	return true;
}

bool FnDeclNode::nameAnalysis(SymbolTable * symTab){
	std::cout << "[DELETE ME] I'm a fnDecl. "
		" you should add my information to"
		" the current scope table.\n";
		" you should also add and make current"
		" a new scope table for my body\n";
	return true;
}

} // End namespace LIL' C
