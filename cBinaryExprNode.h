#pragma once
//**************************************
// cBinaryExprNode.h
//
// Defines AST node for a binary expression
//
// Since binary expressions can take the place of expressions, this class
// inherits from cExprNode
//
// Author: Junmin Yee
//
// Date: Jan. 31, 2019
//

#include "cAstNode.h"
#include "cExprNode.h"
#include "cOpNode.h"

class cBinaryExprNode : public cExprNode
{
    public:
        // params are the lhs, rhs, and operator between
        cBinaryExprNode(cExprNode *lhs, int op, cExprNode *rhs)
            : cExprNode()
        {
            AddChild(lhs);
            cOpNode * temp = new cOpNode(op);
            AddChild(temp);
            AddChild(rhs);
        }

        virtual cDeclNode * GetType()
        {
            if (GetExprLeft()->GetType()->IsFloat() || 
                    GetExprRight()->GetType()->IsFloat())
                return g_SymbolTable.Find("float")->GetDecl();
            else if (GetExprLeft()->GetType()->Size() == 4 || 
                        GetExprRight()->GetType()->Size() == 4)
                return g_SymbolTable.Find("int")->GetDecl();
            else
                return g_SymbolTable.Find("char")->GetDecl();
        }

        virtual string NodeType() { return string("expr"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        cExprNode *GetExprLeft()
        {
            return dynamic_cast<cExprNode*>(GetChild(0));
        }
        cOpNode *GetOp()
        {
            return dynamic_cast<cOpNode*>(GetChild(1));
        }
        cExprNode *GetExprRight()
        {
            return dynamic_cast<cExprNode*>(GetChild(2));
        }
};
