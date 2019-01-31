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
// Date: Jan. 31, 2019
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
            AddChild(name);
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
