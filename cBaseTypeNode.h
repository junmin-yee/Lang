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
        cBaseTypeNode(string name, int typesize, bool isfloat) : cDeclNode()
        {
            m_name = name;
            m_typesize = typesize;
            isFloat = isfloat;
        }

        // getters for attributes
        virtual string GetName()
        {
            return m_name;
        }
        virtual int Size()
        {
            return m_typesize;
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
        int m_typesize;         // size of type
        bool isFloat;           // whether the type is a float
};
