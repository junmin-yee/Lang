//*******************************************************************
// cSymbolTable.cpp
//
// Implements functions from cSymbolTable.h.
//
// Author: Junmin Yee
// junmin.yee@oit.edu
//
// Date: January 16, 2019
//
#include "cSymbolTable.h"

// Define global symbol table.
//cSymbolTable g_symbolTable;

//***************************************
// cSymbolTable ctor
cSymbolTable::cSymbolTable() 
{
    IncreaseScope();

    // Create type symbols
    cBaseTypeNode * char_type = new cBaseTypeNode("char", 1, false); 
    cSymbol * char_symbol = new cSymbol("char");
    char_symbol->SetType(true);
    char_symbol->SetDecl(char_type);

    cBaseTypeNode * int_type = new cBaseTypeNode("int", 4, false);
    cSymbol * int_symbol = new cSymbol("int");
    int_symbol->SetType(true);
    int_symbol->SetDecl(int_type);

    cBaseTypeNode * float_type = new cBaseTypeNode("float", 8, true);
    cSymbol * float_symbol = new cSymbol("float");
    float_symbol->SetType(true);
    float_symbol->SetDecl(float_type);

    // Insert types into outermost scope of symbol table
    Insert(char_symbol);
    Insert(int_symbol);
    Insert(float_symbol);
}

//**************************************
// Increase scope of symbol table
symbolTable_t * cSymbolTable::IncreaseScope()
{
    // Create new scope 
    symbolTable_t * temp = new symbolTable_t();

    // Add scope to symbol table
    m_symbolTable.push_back(temp);

    // Return reference to new scope
    return m_symbolTable.back();
}

//**************************************
// Decrease scope of symbol table
symbolTable_t * cSymbolTable::DecreaseScope()
{
    // Delete scope from symbol table
    m_symbolTable.pop_back();

    // Return reference to current scope
    return m_symbolTable.back();;
}

//**************************************
// Insert a symbol into symbol table
void cSymbolTable::Insert(cSymbol * sym)
{
    // Insert symbol into current scope
    m_symbolTable.back()->Insert(sym);
}

//**************************************
// Find a symbol in the symbol table
cSymbol * cSymbolTable::Find(string name)
{
    // Create temp symbol pointer
    cSymbol * temp = nullptr;

    // Iterate from innermost scope outwards
    // If nothing found, exits loop as nullptr
    for (list<symbolTable_t*>::reverse_iterator rit = m_symbolTable.rbegin();
        rit != m_symbolTable.rend(); ++rit) 
    {
        // Find locally 
        temp = (*rit)->Find(name);
        if (temp) // Check if not null
            return temp; // Bail out if found
    }

    return temp;
}

//****************************************
// Find a symbol in current scope
cSymbol * cSymbolTable::FindLocal(string name)
{
    // Call specific find on table
    return m_symbolTable.back()->Find(name);
}

