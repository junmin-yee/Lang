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
            AddChild(type);
            name->SetDecl(this);
            g_SymbolTable.Insert(name);
            AddChild(name);
            AddChild(params);
            AddChild(decls);
            AddChild(stmts);
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

        void SetParams(cParamsNode *params)
        {
            SetChild(2, params);
        }
        void SetDecls(cDeclsNode *decls)
        {
            SetChild(3, decls);
        }
        void SetStmts(cStmtsNode *stmts)
        {
            SetChild(4, stmts);
        }

        cSymbol * GetFuncType()
        {
            return dynamic_cast<cSymbol*>(GetChild(0));
        }
};
