#pragma once
//**************************************
// cAssignNode.h
//
// Defines AST node for an assign statement
//
// Since assign statements can take the place of statments, this class
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
#include "cVarExprNode.h"

class cAssignNode : public cStmtNode
{
    public:
        // params are the lhs ref and rhs expr
        cAssignNode(cVarExprNode *ref, cExprNode *expr)
            : cStmtNode()
        {
            AddChild(ref);
            AddChild(expr);
        }

        virtual string NodeType() { return string("assign"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
