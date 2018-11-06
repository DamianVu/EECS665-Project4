#include "ast.hpp"
#include "symbol_table.hpp"
#include <algorithm>

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
	if (myType->getType() == "void") {
		symTab->nonFunctionVoid(myId->getId().at(0));
		if (symTab->findByName(myId->getId())) {
			symTab->multiplyDeclaredId(myId->getId().at(0));
		}
	} else if (symTab->findByName(myId->getId())) {
		symTab->multiplyDeclaredId(myId->getId().at(0));
	} else if (myType->getType() == "struct") {
		std::string structId = myType->getId();
		// Verify this is a struct type in our scope table
		if (symTab->findByName(structId) && symTab->getTypeOf(structId) == "struct") {
			symTab->addStructUsage(myId->getId(), "structUsage", structId);
		} else {
			symTab->invalidStructName(structId.at(0));
		}
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
	if (myType->getType() == "void") {
		symTab->nonFunctionVoid(myId->getId().at(0));
		if (symTab->findByName(myId->getId())) {
			symTab->multiplyDeclaredId(myId->getId().at(0));
		}
	} else if (symTab->findByName(myId->getId())) {
		symTab->multiplyDeclaredId(myId->getId().at(0));
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
	// Left side HAS to be a struct access
	if (myExp->getType() == "id") {
		std::string id = myExp->getId();
		if (id == "uhoh") {
			std::cout << "\n\nDammit damian....\n\n";
			return false;
		}
		if (symTab->findByName(id)) {
			// Make sure it is of structUsage type
			if (!(symTab->getTypeOf(id) == "structUsage")) {
				symTab->dotAccess(id.at(0));
			} else {
				// Check RHS of struct usage
				std::string structId = symTab->getStructName(id);
				std::string accessId = myId->getId();
				if (!symTab->structListContains(structId, accessId)) {
					symTab->invalidStructField(accessId.at(0));
				}
			}
		} else {
			symTab->undeclaredId(id.at(0));
		}

	} else {
		// ??? Idk what would cause this.
	}
	return true;
}

} // End namespace LIL' C
