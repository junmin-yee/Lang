#pragma once
//**************************************
// cStructDeclNode.h
//
// Defines AST node for a struct declaration
//
// Since struct declaration can take place of declaration, it inherits 
// from cDeclNode
//
// Author: Junmin Yee
// Date: Feb. 4, 2019
//
#include "cAstNode.h"
#include "cDeclNode.h"
#include "cDeclsNode.h"
#include "cSymbol.h"

class cStructDeclNode : public cDeclNode
{
    public:
        // params are the list of decls and the struct name
        cStructDeclNode(cDeclsNode *decls, cSymbol *name)
            : cDeclNode()
        {
            AddChild(decls);

            // Set as type and add to symbol table
            name->SetType(true);
            name->SetDecl(this);
            g_SymbolTable.Insert(name);
            AddChild(name);
        }

        virtual cDeclNode * GetType()
        {
            return this;
        }

        virtual string GetName()
        {
            return GetStructName()->GetName();
        }

        virtual string NodeType() { return string("struct_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        cSymbol * GetStructName()
        {
            return dynamic_cast<cSymbol*>(GetChild(1));
        }
};
