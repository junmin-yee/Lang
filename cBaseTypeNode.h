#pragma once
//**************************************
// cBaseTypeNode.h
//
// Defines a base type for declarations.
//
// Author: Junmin Yee
// Date: Feb. 14, 2019 
//
#include <string>
using std::string;
#include "cAstNode.h"
#include "cDeclNode.h"

class cBaseTypeNode : public cDeclNode
{
    public:
        // attribute inputs
        cBaseTypeNode(string name, int size, bool isfloat) : cDeclNode()
        {
            m_name = name;
            m_size = size;
            isFloat = isfloat;
        }

        // getters for attributes
        virtual string GetName()
        {
            return m_name;
        }
        int Size()
        {
            return m_size;
        }
        bool IsFloat()
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
        int m_size;             // size of type
        bool isFloat;           // whether the type is a float
};
