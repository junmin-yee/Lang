#pragma once
//**************************************
// cVarExprNode.h
//
// Defines a variable reference which is an expression.
// Inherits from cExprNode so that variable references can be
// used anywhere. 
//
// Author: Junmin Yee 
// Date: Jan. 31, 2019
//

#include "cExprNode.h"
#include "cSymbol.h"

class cVarExprNode : public cExprNode
{
    public:
        // param is first ref
        cVarExprNode(cSymbol *ref) : cExprNode()
        {
            AddChild(ref);
        }

        // Add symbol to the list
        void Insert(cSymbol *sym)
        {
            AddChild(sym);
        }

        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
