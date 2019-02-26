#pragma once
//**************************************
// cFuncDeclNode.h
//
// Defines AST node for a function declaration
//
// Since function declaration can take place of declaration, it inherits 
// from cDeclNode
//
// Author: Junmin Yee
// Date: Feb. 4, 2019
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cDeclsNode.h"
#include "cParamsNode.h"
#include "cStmtsNode.h"
#include "cSymbol.h"

class cFuncDeclNode : public cDeclNode
{
    public:
        // params initial return type and name, params, 
        // local declarations, and code statements
        cFuncDeclNode(cSymbol *type, cSymbol *name, cParamsNode *params,
                    cDeclsNode *decls, cStmtsNode *stmts)
            : cDeclNode()
        {
            isDefinition = false;
            AddChild(type);
            AddChild(name);

            cSymbol * temp = g_SymbolTable.Find(name->GetName());
            if(temp)
            {
                if(temp->GetDecl()->GetType() != type->GetDecl()->GetType())
                {
                    string error = (name->GetName() + " previously defined with different"
                        + " return type");
                    SemanticError(error);
                }
                // Copy stuff if previously defined
                cFuncDeclNode * found = dynamic_cast<cFuncDeclNode*>(temp->GetDecl());
                AddChild(found->GetParams());
                AddChild(found->GetDecls());
                AddChild(found->GetStmts());
                if (found->IsDefinition())
                {
                    found->SetDefinition(false);
                    isDefinition = true;
                }
            }
            else
            {
                AddChild(params);
                AddChild(decls);
                AddChild(stmts);
            }
            name->SetDecl(this);
            g_SymbolTable.Insert(name);
        }

        virtual cDeclNode * GetType()
        {
            return GetFuncType()->GetDecl();
        }
        virtual string GetName()
        {
            return GetFuncType()->GetDecl()->GetName();
        }

        virtual bool IsFunc() { return true; }

        virtual string NodeType() { return string("func"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        bool IsDefinition() { return isDefinition; }
        void SetDefinition(bool def) { isDefinition = def; }

        void SetParams(cParamsNode *params)
        {
            cSymbol * temp = g_SymbolTable.Find(GetFuncName()->GetName());

            // If symbol exists
            if (temp)
            {
                cFuncDeclNode * found = dynamic_cast<cFuncDeclNode*>(temp->GetDecl());
                // Check if previous definition has params
                if(found->GetParams())
                {
                    // Check number of params
                    if(found->GetParams()->NumParams() 
                            != params->NumParams())
                    {
                        string error = (GetFuncName()->GetName() + " redeclared with" + 
                                " a different number of parameters");
                        SemanticError(error);
                    }
                    else
                    {
                        for(int i = 0; i < params->NumParams(); ++i)
                        {
                            if(params->GetDecl(i)->GetType() != 
                                    GetParams()->GetDecl(i)->GetType())
                            {
                                string error = (GetFuncName()->GetName() + 
                                        " previously defined with different parameters");
                                SemanticError(error);
                            }
                        }
                    }
                }
            }
            SetChild(2, params);
        }
        void SetDecls(cDeclsNode *decls)
        {
            SetChild(3, decls);
        }
        void SetStmts(cStmtsNode *stmts)
        {
            cSymbol * temp = g_SymbolTable.Find(GetFuncName()->GetName());

            // If symbol exists
            if (temp)
            {
                cFuncDeclNode * found = dynamic_cast<cFuncDeclNode*>(temp->GetDecl());
                if (found->IsDefinition())
                {
                    string error = (GetFuncName()->GetName() + 
                            " already has a definition");
                    SemanticError(error);
                }
                else 
                {
                    isDefinition = true;
                }
            }
            SetChild(4, stmts);
        }

        cSymbol * GetFuncType()
        {
            return dynamic_cast<cSymbol*>(GetChild(0));
        }

        cSymbol * GetFuncName()
        {
            return dynamic_cast<cSymbol*>(GetChild(1));
        }

        cParamsNode * GetParams()
        {
            return dynamic_cast<cParamsNode*>(GetChild(2));
        }

        cDeclsNode * GetDecls()
        {
            return dynamic_cast<cDeclsNode*>(GetChild(3));
        }

        cStmtsNode * GetStmts()
        {
            return dynamic_cast<cStmtsNode*>(GetChild(4));
        }

    private:
        bool isDefinition;
};
