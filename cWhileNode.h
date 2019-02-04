#pragma once
//**************************************
// cWhileNode.h
//
// Defines AST node for a while statement
//
// Since while statements can take the place of statments, this class
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

class cWhileNode : public cStmtNode
{
    public:
        // params are the expr and code block
        cWhileNode(cExprNode *expr, cStmtNode *stmt)
            : cStmtNode()
        {
            AddChild(expr);
            AddChild(stmt);
        }

        virtual string NodeType() { return string("while"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
