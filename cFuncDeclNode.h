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
            m_isDefinition = false;
            m_hasParams = false;
            AddChild(type);
            AddChild(name);
            AddChild(nullptr);
            AddChild(nullptr);
            AddChild(nullptr);

            cSymbol * temp = g_SymbolTable.Find(name->GetName());
            
            if(temp != nullptr)
            {
                cDeclNode * decl = temp->GetDecl();

                if (!decl->IsFunc())
                {
                    SemanticError(name->GetName() + 
                            " previously defined as other than a function");
                }
                else
                {
                    cFuncDeclNode * funcDecl = dynamic_cast<cFuncDeclNode*>(decl);
                    if (funcDecl->GetType() != type->GetDecl())
                    {
                        SemanticError(name->GetName() + 
                                " previously defined with different return type");
                    }
                    else
                    {
                        for (int i = 0; i < NumChildren(); ++i)
                        {
                            SetChild(i, funcDecl->GetChild(i));
                        }
                        m_isDefinition = funcDecl->m_isDefinition;
                        m_hasParams = funcDecl->m_hasParams;
                        name->SetDecl(this);
                    }
                }
            }
            else
            {
                name->SetDecl(this);
                g_SymbolTable.Insert(name);
            }
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

        bool IsDefinition() { return m_isDefinition; }
        void SetDefinition(bool def) { m_isDefinition = def; }

        void SetParams(cParamsNode *params)
        {
            cParamsNode *old_params = GetParams();

            if (m_hasParams && (params != nullptr || old_params != nullptr))
            {
                if ((params != nullptr && old_params == nullptr) ||
                    (params == nullptr && old_params != nullptr) ||
                    (params->NumParams() != old_params->NumParams()))
                {
                    string error = GetName() + 
                        " redeclared with a different number of parameters";
                    SemanticError(error);
                    return;
                }

                for (int i = 0; i < params->NumParams(); ++i)
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
            SetChild(2, params);
            m_hasParams = true;
        }
        void SetDecls(cDeclsNode *decls)
        {
            SetChild(3, decls);
        }
        void SetStmts(cStmtsNode *stmts)
        {
            if (m_isDefinition)
            {
                SemanticError(GetName() + "already has a definition");
                return;
            }
            
            SetChild(4, stmts);
            m_isDefinition = true;
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
        bool m_isDefinition;
        bool m_hasParams;
};
