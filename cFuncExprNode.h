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
            if (g_SymbolTable.Find(name->GetName()) == nullptr)
            {
                string error = (name->GetName() + " is not declared");
                SemanticError(error);
            }
            else if (!name->GetDecl()->IsFunc())
            {
                string error = (name->GetName() + " is not a function");
                SemanticError(error);
            }
            else if (!dynamic_cast<cFuncDeclNode*>(name->GetDecl())->IsDefinition())
            {
                string error = (name->GetName() + " is not fully defined");
                SemanticError(error);
            }
            else if (params) // Check for different number of args
            {
                if (params->NumParams() != dynamic_cast<cFuncDeclNode*>(name->GetDecl())
                        ->GetParams()->NumParams())
                {
                    string error = (name->GetName() + 
                            " called with wrong number of arguments");
                    SemanticError(error);
                }
            }
            else if (params == nullptr) // Check case for different number of args
            {
                if (dynamic_cast<cFuncDeclNode*>(name->GetDecl())->GetParams())
                { 
                    string error = (name->GetName() + 
                            " called with wrong number of arguments");
                    SemanticError(error);
                }
            }
            AddChild(name);
            AddChild(params);
        }

        virtual cDeclNode * GetType()
        {
            return GetFuncName()->GetDecl()->GetType();
        }

        virtual string NodeType() { return string("funcCall"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        cSymbol *GetFuncName()
        {
            return dynamic_cast<cSymbol*>(GetChild(0));
        }
        
        cParamListNode * GetParamList()
        {
            return dynamic_cast<cParamListNode*>(GetChild(1));
        }
};
