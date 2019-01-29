#pragma once
//*******************************************
// symbolTable_t.h
//
// Defines a wrapper class for the hash table
//
// Author: Junmin Yee
// Date: January 29, 2019
//
#include <unordered_map>
#include "cSymbol.h"
using std::unordered_map;

class symbolTable_t
{
    public: 
        // Create a symbol table type
        symbolTable_t();

        // Insert a symbol into this symbolTable_t
        void Insert(cSymbol * sym);

        // Look up within table 
        cSymbol *Find(string name);

    protected: 
        unordered_map<string, cSymbol *> m_symbolTable_t;   // the wrapper
};
