#pragma once
//**************************************
// cArrayDeclNode.h
//
// Defines AST node for an array declaration
//
// Since array declarations can take place of declarations, it inherits 
// from cDeclNode
//
// Author: Junmin Yee 
// Date: Feb. 6, 2019
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cSymbol.h"

class cArrayDeclNode : public cDeclNode
{
    public:
        // params are the type and identifier of the declaration
        cArrayDeclNode(cSymbol *type, int size, cSymbol *name)
            : cDeclNode()
        {
            m_size = size;

            AddChild(type);

            // Set as type and add to symbol table
            name->SetType(true);
            g_SymbolTable.Insert(name);
            AddChild(name);
        }

        virtual string AttributesToString()
        {
            return " count=\"" + std::to_string(m_size) + "\"";
        }
        virtual string NodeType() { return string("array_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    protected:
        int m_size;         // size of array
};
