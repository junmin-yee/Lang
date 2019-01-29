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
cSymbolTable g_symbolTable;

cSymbolTable::cSymbolTable() 
{
    // Create initial scope
    symbolTable_t temp;

    // Add to symbol table
    m_symbolTable.push_back(temp);
}

symbolTable_t * cSymbolTable::IncreaseScope()
{
    // Create new scope 
    symbolTable_t temp;

    // Add scope to symbol table
    m_symbolTable.push_back(temp);

    // Return reference to new scope
    return &m_symbolTable.back();
}

symbolTable_t * cSymbolTable::DecreaseScope()
{
    // Delete scope from symbol table
    m_symbolTable.pop_back();

    // Return reference to current scope
    return &m_symbolTable.back();;
}

void cSymbolTable::Insert(cSymbol * sym)
{
    // Insert symbol into current scope
    m_symbolTable.back().Insert(sym);
}

cSymbol * cSymbolTable::Find(string name)
{
    // Create temp symbol pointer
    cSymbol * temp = nullptr;

    // Iterate from innermost scope outwards
    // If nothing found, exits loop as nullptr
    for (list<symbolTable_t>::reverse_iterator rit = m_symbolTable.rbegin();
        rit != m_symbolTable.rend(); ++rit) 
    {
        // Find locally 
        temp = rit->Find(name);
        if (temp) // Check if not null
            return temp; // Bail out if found
    }

    return temp;
}

cSymbol * cSymbolTable::FindLocal(string name)
{
    // Call specific find on table
    return m_symbolTable.back().Find(name);
}

