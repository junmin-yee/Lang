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

cSymbolTable::cSymbolTable() : m_currentScope(nullptr)
{
    // Create initial scope
    symbolTable_t temp;

    // Add to symbol table
    m_symbolTable.push_back(temp);

    // Assign current scope
    m_currentScope = &m_symbolTable.back();
}

symbolTable_t * cSymbolTable::IncreaseScope()
{
    // Create new scope 
    symbolTable_t temp;

    // Add scope to symbol table
    m_symbolTable.push_back(temp);

    // Update current scope
    m_currentScope = &m_symbolTable.back();

    // Return reference to new scope
    return m_currentScope;
}

symbolTable_t * cSymbolTable::DecreaseScope()
{
    // Delete scope from symbol table
    m_symbolTable.pop_back();

    // Update current scope
    m_currentScope = &m_symbolTable.back();

    // Return reference to current scope
    return m_currentScope;
}

void cSymbolTable::Insert(cSymbol * sym)
{
    // Insert symbol into current scope
    m_currentScope->emplace(sym->GetName(), sym);
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
        // Search each scope using key
        symbolTable_t::iterator search = rit->find(name);

        // Check if anything found
        if (search != rit->end())
        {
            temp = search->second; // Assign if found

            // Bail out once symbol is found
            return temp;
        }
    }

    return temp;
}

cSymbol * cSymbolTable::FindLocal(string name)
{
    // Create temp symbol pointer
    cSymbol * temp = nullptr;
    
    // Search using key
    symbolTable_t::iterator search = m_currentScope->find(name);

    // Check if anything found
    if (search != m_currentScope->end())
        temp = search->second; // Assign if found

    return temp;
}

