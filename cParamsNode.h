#pragma once
//**************************************
// cParamsNode.h
//
// Defines a class to represent parameters for a function
//
// Author: Junmin Yee
// Date: Feb. 4, 2019
//

#include "cAstNode.h"
#include "cDeclNode.h"

class cParamsNode : public cAstNode
{
    public:
        // first arg in function
        cParamsNode(cDeclNode *decl) : cAstNode()
        {
            AddChild(decl);
        }

        // Add another arg to the list
        void Insert(cDeclNode *decl)
        {
            AddChild(decl);
        }
        
        virtual string AttributesToString()
        {
            string result(" size=\"");
            result += std::to_string(m_size);
            result += "\"";
            return result;
        }
        virtual string NodeType() { return string("args"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        int NumParams() { return NumChildren(); } 
        
        cDeclNode * GetDecl(int index)
        {
            if(index >= NumParams()) return nullptr;
            return dynamic_cast<cDeclNode*>(GetChild(index));
        } 

        int GetSize() { return m_size; }
        void SetSize(int size) { m_size = size; }

    protected:
        int m_size;         // size of args 
};
