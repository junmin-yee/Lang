#pragma once
//**************************************
// cIfNode.h
//
// Defines AST node for an if statement
//
// Since if statements can take the place of statments, this class
// inherits from cStmtNode
//
// Author: Junmin Yee
//
// Date: Feb. 3, 2019
//

#include "cAstNode.h"
#include "cStmtNode.h"
#include "cExprNode.h"
#include "cStmtsNode.h"

class cIfNode : public cStmtNode
{
    public:
        // params are the expr, if, and else block
        cIfNode(cExprNode *expr, cStmtsNode *ifstmts, cStmtsNode *elsestmts)
            : cStmtNode()
        {
            AddChild(expr);
            AddChild(ifstmts);
            AddChild(elsestmts);
        }

        virtual string NodeType() { return string("if"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        cExprNode *GetExpr()
        {
            return static_cast<cExprNode*>(GetChild(0));
        }
        cStmtsNode *GetIfStmts()
        {
            return static_cast<cStmtsNode*>(GetChild(1));
        }
        cStmtsNode *GetElseStmts()
        {
            return static_cast<cStmtsNode*>(GetChild(2));
        }
};
