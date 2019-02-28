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
        virtual bool IsFunc() { return false; }
        virtual bool IsStruct() { return false; }

        // Pure virtual functions for its subclasses
        virtual cDeclNode * GetType() = 0;
        virtual string GetName() = 0;
   
        virtual string AttributesToString()
        {
            if (m_size == 0 && m_offset == 0) return "";
            else
            {
                string result(" size=\"");
                result += std::to_string(m_size);
                result += "\" offset=\"";
                result += std::to_string(m_offset);
                result += "\"";
                return result;
            }
        } 

        int GetSize() { return m_size; }
        void SetSize(int size) { m_size = size; }

        int GetOffset() { return m_offset; }
        void SetOffset(int offset) { m_offset = offset; }

    protected:
        int m_size;     // size of node
        int m_offset;   // offset of node
};
