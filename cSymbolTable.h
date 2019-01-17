#pragma once
//**************************************
// cSymbolTable.h
//
// Defines a nested symbol table.
// Individual levels of the symbol table use a std::unordered_map from the STL
//
// Author: Junmin Yee 
// junmin.yee@oit.edu
//
//
#include <unordered_map>
#include <list>
#include "cSymbol.h"

using std::unordered_map;
using std::list;

typedef unordered_map<string, cSymbol *> symbolTable_t;

class cSymbolTable
{
    public:
        // Create a symbol table
        cSymbolTable();

        // Increase the scope: add a level to the nested symbol table
        // Return value is the newly created scope
        symbolTable_t *IncreaseScope();

        // Decrease the scope: remove the outer-most scope.
        // Returned value is the outer-most scope AFTER the pop.
        //
        // NOTE: do NOT clean up memory after poping the table. Parts of the
        // AST will probably contain pointers to symbols in the popped table.
        symbolTable_t *DecreaseScope();

        // insert a symbol into the table
        // Assumes the symbol is not already in the table
        void Insert(cSymbol *sym);

        // Do a lookup in the nested table. 
        // Return the symbol for the outer-most match. 
        // Returns nullptr if no match is found.
        cSymbol *Find(string name);

        // Find a symbol in the outer-most scope.
        // NOTE: does not search nested scopes, only the outermost scope.
        // Return the symbol if found.
        // Returns nullptr if the symbol is not found.
        cSymbol *FindLocal(string name);

    protected:
        symbolTable_t * m_currentScope;         // keeps track of current scope
        list<symbolTable_t> m_symbolTable;      // the symbol table 
};

// Declaration for the global symbol table.
// Definition is in main.cpp
extern cSymbolTable g_symbolTable;
