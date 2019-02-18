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
#include <string>
using std::string;
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
            if (!CheckAssignmentType(ref, expr))
            {
                string error = "Cannot assign " + expr->GetType()->GetName() + 
                    " to " + ref->GetType()->GetName();
                SemanticError(error);
            }

            AddChild(ref);
            AddChild(expr);
        }

        virtual string NodeType() { return string("assign"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    private:
        // Check assignment types
        bool CheckAssignmentType(cVarExprNode *ref, cExprNode *expr)
        {
            // Check if types are different
            if (ref->GetType() != expr->GetType())
            {
                // Test for promotion rules
                if (ref->GetType()->GetName() == "int" &&
                        expr->GetType()->GetName() == "char")
                {
                    return true;
                }
                else if (ref->GetType()->GetName() == "float" &&
                        expr->GetType()->GetName() == "char")
                {
                    return true;
                }
                else if (ref->GetType()->GetName() == "float" &&
                        expr->GetType()->GetName() == "int")
                {
                    return true;
                }
                return false;
            }
            return true;
        }
};
