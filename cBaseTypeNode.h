#pragma once
//**************************************
// cBaseTypeNode.h
//
// Defines a base type for declarations.
//
// Author: Junmin Yee
// Date: Feb. 14, 2019 
//
#include "cAstNode.h"
#include "cDeclNode.h"

class cBaseTypeNode : public cDeclNode
{
    public:
        // attribute inputs
        cBaseTypeNode(string name, int size, bool isfloat) : cDeclNode()
        {
            m_name = name;
            SetSize(size);
            isFloat = isfloat;
        }

        // getters for attributes
        virtual string GetName()
        {
            return m_name;
        }
        virtual bool IsFloat()
        {
            return isFloat;
        }

        virtual cDeclNode * GetType()
        {
            return this;
        }

        virtual string NodeType() { return string("basetype"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        string m_name;          // name of base type
        bool isFloat;           // whether the type is a float
};
