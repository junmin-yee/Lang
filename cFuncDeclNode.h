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
                    cDeclsNode *local, cStmtsNode *stmts)
            : cDeclNode()
        {
            AddChild(type);
            AddChild(name);
            AddChild(params);
            AddChild(local);
            AddChild(stmts);
        }

        virtual string NodeType() { return string("func"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
