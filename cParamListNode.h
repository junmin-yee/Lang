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

        virtual string NodeType() { return string("args"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
