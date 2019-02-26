#pragma once
//**************************************
// cDeclNode
//
// Defines base class for all declarations.
// Future labs will add features to this class.
//
// Author: Phil Howard
//
// Edited by: Junmin Yee
// Date: Feb. 14, 2019 
//
#include "cAstNode.h"

class cDeclNode : public cAstNode
{
    public:
        cDeclNode() : cAstNode() {}

        // Virtual functions for its subclasses
        virtual bool IsVar() { return false; }
        virtual bool IsFloat() { return false; }
        virtual int Size() { return 0; }
        virtual bool IsFunc() { return false; }
        virtual bool IsStruct() { return false; }

        // Pure virtual functions for its subclasses
        virtual cDeclNode * GetType() = 0;
        virtual string GetName() = 0;
};
