#pragma once
//**************************************
// cVarDeclNode.h
//
// Defines AST node for a variable declaration
//
// Since variable declaration can take place of declaration, it inherits 
// from cDeclNode
//
// Author: Phil Howard 
//
// Edited by: Junmin Yee
// Date: Feb. 3, 2019
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cSymbol.h"

class cVarDeclNode : public cDeclNode
{
    public:
        // params are the type and identifier of the declaration
        cVarDeclNode(cSymbol *type, cSymbol *name)
            : cDeclNode()
        {
            AddChild(type);

            // Check if in local scope
            cSymbol * temp;
            temp = g_SymbolTable.FindLocal(name->GetName());
            if (temp == nullptr)
            {
                temp = new cSymbol(name->GetName());
                g_SymbolTable.Insert(temp);
                AddChild(temp);
            }
            else
            {
                g_SymbolTable.Insert(name);
                AddChild(name);
            }
        }

        virtual string NodeType() { return string("var_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        cSymbol *GetSymbolType()
        {
            return static_cast<cSymbol*>(GetChild(0));
        }
        cSymbol *GetSymbolName()
        {
            return static_cast<cSymbol*>(GetChild(1));
        }
};
