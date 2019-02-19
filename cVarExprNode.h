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
#include <string>
using std::string;
#include "cExprNode.h"
#include "cSymbol.h"

class cVarExprNode : public cExprNode
{
    public:
        // param is first ref
        cVarExprNode(cSymbol *ref) : cExprNode()
        {
            if (g_SymbolTable.Find(ref->GetName()) == nullptr)
            {
                string error = "Symbol " + ref->GetName() + 
                    " not defined";
                SemanticError(error);
            }
            
            AddChild(ref);
        }

        // Add symbol to the list
        void InsertField(cSymbol *sym)
        {
            AddChild(sym);
        }

        // Add expr to the list
        void InsertIndex(cExprNode *expr)
        {
            AddChild(expr);
        }

        virtual cDeclNode * GetType()
        {
            return GetLastChild()->GetDecl()->GetType();
        }

        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        cSymbol * GetLastChild()
        {
            return dynamic_cast<cSymbol*>(GetChild(NumChildren() - 1));
        }
};
