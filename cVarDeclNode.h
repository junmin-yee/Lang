#pragma once
//**************************************
// cVarDeclNode.h
//
// Defines AST node for a variable declaration
//
// Since variable declaration can take place of declaration, it inherits 
// from cDeclNode
//
// Author: Phil Howard 
//
// Edited by: Junmin Yee
// Date: Feb. 3, 2019
//
#include "cAstNode.h"
#include "cDeclNode.h"
#include "cSymbol.h"

class cVarDeclNode : public cDeclNode
{
    public:
        // params are the type and identifier of the declaration
        cVarDeclNode(cSymbol *type, cSymbol *name)
            : cDeclNode()
        {
            if (g_SymbolTable.FindLocal(name->GetName()))
            {
                string error = "Symbol " + name->GetName() + 
                    " already defined in current scope";
                SemanticError(error);
            }
            
            AddChild(type);

            // Check if in local scope
            cSymbol * temp;
            temp = g_SymbolTable.Find(name->GetName());
            if (temp) //If found
            {
                temp = new cSymbol(name->GetName());
                temp->SetDecl(this);
                g_SymbolTable.Insert(temp);
                AddChild(temp);
            }
            else
            {
                name->SetDecl(this);
                g_SymbolTable.Insert(name);
                AddChild(name);
            }
        }

        virtual cDeclNode * GetType()
        {
            return GetTypeSymbol()->GetDecl();
        }

        virtual string GetName()
        {
            return GetTypeSymbol()->GetDecl()->GetName();
        }

        virtual bool IsVar() { return true; }
        virtual bool IsFloat() { return GetTypeSymbol()->GetDecl()->IsFloat(); }
        virtual bool IsStruct() { return GetTypeSymbol()->GetDecl()->IsStruct(); }

        virtual string NodeType() { return string("var_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); 
        }
        cSymbol *GetTypeSymbol()
        {
            return dynamic_cast<cSymbol*>(GetChild(0));
        }
        cSymbol *GetNameSymbol()
        {
            return dynamic_cast<cSymbol*>(GetChild(1));
        }
};
