#include "ast.hpp"
#include "symbol_table.hpp"

namespace LILC{

// TODO:
// 	Need to add error checking

bool ASTNode::nameAnalysis(SymbolTable * symTab){
	std::cout << "[DELETE ME] Whoops, I'm the ASTNode"
		" base class nameAnalysis function."
		" I should have been overridden."
		" My function declaration should have"
		" probably even been pure virtual.\n";
	return true;
}

bool ExpNode::nameAnalysis(SymbolTable * symTab) {
	std::cout << "[DELETE ME] Whoops, I'm the ExpNode"
		" base class nameAnalysis function."
		" I should have been overridden."
		" My function declaration should have"
		" probably even been pure virtual.\n";
	return true;
}

bool ProgramNode::nameAnalysis(SymbolTable * symTab){
	symTab->addScope();
	this->myDeclList->nameAnalysis(symTab);
	symTab->dropScope();
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
	if (symTab->findByName(myId->getId())) {
		symTab->multiplyDeclaredId(myId->getId().at(0));
	} else if (myType->getType() == "void") {
		symTab->nonFunctionVoid(myId->getId().at(0));
	} else {
		symTab->addItem(myId->getId(), myType->getType());
	}
	return true;
}

bool StructDeclNode::nameAnalysis(SymbolTable * symTab) {
	if (symTab->findByName(myId->getId())) {
		symTab->multiplyDeclaredId(myId->getId().at(0));
		return false;
	} else {
		std::list<std::string> list = myDeclList->getDeclIds();
		symTab->addStruct(myId->getId(), list);
	}
}

bool FnDeclNode::nameAnalysis(SymbolTable * symTab){
	// If function is not multiply declared
	if (symTab->findByName(myId->getId())) {
		symTab->multiplyDeclaredId(myId->getId().at(0));
	} else {
		symTab->addItem(myId->getId(), myType->getType());
	}
	symTab->addScope();
	// Process formals
	myFormals->nameAnalysis(symTab);
	myBody->nameAnalysis(symTab);
	symTab->dropScope();
	return true;
}

bool FormalsListNode::nameAnalysis(SymbolTable * symTab) {
	for (FormalDeclNode * formal : *myFormals) {
		formal->nameAnalysis(symTab);
	}
}

bool FormalDeclNode::nameAnalysis(SymbolTable * symTab) {
	if (symTab->findByName(myId->getId())) {
		symTab->multiplyDeclaredId(myId->getId().at(0));
	} else if (myType->getType() == "void") {
		symTab->nonFunctionVoid(myId->getId().at(0));
	} else {
		symTab->addItem(myId->getId(), myType->getType());
	}
	return true;
}

bool FnBodyNode::nameAnalysis(SymbolTable * symTab) {
	myDeclList->nameAnalysis(symTab);
	myStmtList->nameAnalysis(symTab);
}

bool StmtListNode::nameAnalysis(SymbolTable * symTab) {
	for (StmtNode * stmt : *myStmts) {
		stmt->nameAnalysis(symTab);
	}
}

bool StmtNode::nameAnalysis(SymbolTable * symTab) {
	std::cout << "[DELETE ME] Whoops, I'm the StmtNode"
		" base class nameAnalysis function."
		" I should have been overridden."
		" My function declaration should have"
		" probably even been pure virtual.\n";
	return true;
}

bool AssignStmtNode::nameAnalysis(SymbolTable * symTab) {
	myAssign->nameAnalysis(symTab);
}


// Exp Node Analysis

bool IdNode::nameAnalysis(SymbolTable * symTab) {
	if (!symTab->findByName(myStrVal)) {
		symTab->undeclaredId(myStrVal.at(0));
	}
}

bool AssignNode::nameAnalysis(SymbolTable * symTab) {
	// Check for undeclared things when assigning
	// TODO: Fill in struct access assignment
	myExpLHS->nameAnalysis(symTab);
	myExpRHS->nameAnalysis(symTab);
}

bool DotAccessNode::nameAnalysis(SymbolTable * symTab) {
	if (myExp->getType() == "id") {
		symTab->dotAccess(myExp->getId().at(0));
		return false;
	} else {
	}

	return myExp->nameAnalysis(symTab);
}

} // End namespace LIL' C
