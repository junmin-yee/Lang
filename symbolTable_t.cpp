//*******************************************
// symbolTable_t.cpp
//
// Implements functions from symbolTable_t.h
//
// Author: Junmin Yee
// Date: January 29, 2019
//
#include "symbolTable_t.h"

//*******************************************
// Wrapper class ctor
symbolTable_t::symbolTable_t()
{
    // Calls unordered_map ctor
}

//*******************************************
// Insert a symbol into the unordered map
void symbolTable_t::Insert(cSymbol * sym)
{
    // Insert symbol into table
    m_symbolTable_t.emplace(sym->GetName(), sym);
}

//*******************************************
// Find a symbol in the unordered map
cSymbol * symbolTable_t::Find(string name)
{
    // Create temp symbol pointer
    cSymbol * temp = nullptr;

    // Search within table
    unordered_map<string, cSymbol *>::iterator search = 
        m_symbolTable_t.find(name);

    // Check if anything found
    if (search != m_symbolTable_t.end())
        temp = search->second; // Assign if found

    return temp;
} 
