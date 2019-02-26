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
            if (expr->GetType()->IsStruct())
            {
                string error = "Cannot assign a struct";
                SemanticError(error);
            }
            AddChild(expr);
        }

        // Add another param to the list
        void Insert(cExprNode *expr)
        {
            if (expr->GetType()->IsStruct())
            {
                string error = "Cannot assign a struct";
                SemanticError(error);
            }
            AddChild(expr);
        }

        virtual string NodeType() { return string("params"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        int NumParams() { return NumChildren(); }
};
