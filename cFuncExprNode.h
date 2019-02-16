#pragma once
//**************************************
// cFuncExprNode.h
//
// Defines AST node for a function expression
//
// Since function expressionn can take place of an expression, it inherits 
// from cExprNode
//
// Author: Junmin Yee
// Date: Feb. 4, 2019
//

#include "cAstNode.h"
#include "cExprNode.h"
#include "cParamListNode.h"
#include "cSymbol.h"

class cFuncExprNode : public cExprNode
{
    public:
        // params are function name and param list
        cFuncExprNode(cSymbol *name, cParamListNode *params)
            : cExprNode()
        {
            AddChild(name);
            AddChild(params);
        }

        virtual cDeclNode * GetType()
        {
            //if (GetFirstChild()->GetDecl()->IsFloat())
            //    return g_SymbolTable.Find("float")->GetDecl();
            //else if (GetFirstChild()->GetDecl()->Size() == 4)
            //    return g_SymbolTable.Find("int")->GetDecl();
            //else
            //    return g_SymbolTable.Find("char")->GetDecl();
            return nullptr;
        }

        virtual string NodeType() { return string("funcCall"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        cSymbol *GetFirstChild()
        {
            return static_cast<cSymbol*>(GetChild(0));
        }
};
