#pragma once
//**************************************
// cReturnNode.h
//
// Defines AST node for return statements
//
// Inherits from cStmtNode so return statments can go in statement lists, and be
// used anywhere a statement is legal.
//
// Author: Junmin Yee
// Date: Feb. 3, 2019
//

#include "cAstNode.h"
#include "cStmtNode.h"
#include "cExprNode.h"

class cReturnNode : public cStmtNode
{
    public:
        // param is the value to be returned
        cReturnNode(cExprNode *expr) : cStmtNode()
        {
            AddChild(expr);
        }

        virtual string NodeType() { return string("return"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        cExprNode * GetExpr() 
        {
            return dynamic_cast<cExprNode*>(GetChild(0));
        }
};
