#pragma once
//**************************************
// cParamListNode.h
//
// Defines a class to represent incoming parameters
//
// Author: Junmin Yee
// Date: Feb. 4, 2019
//

#include "cAstNode.h"
#include "cExprNode.h"

class cParamListNode : public cAstNode
{
    public:
        // first param in function
        cParamListNode(cExprNode *expr) : cAstNode()
        {
            AddChild(expr);
        }

        // Add another param to the list
        void Insert(cExprNode *expr)
        {
            AddChild(expr);
        }

        virtual string NodeType() { return string("params"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        int NumParams() { return NumChildren(); }

        cExprNode * GetExpr(int index)
        {
            return dynamic_cast<cExprNode*>(GetChild(index));
        }
};
