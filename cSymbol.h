#pragma once
//**************************************
// cSymbol.h
//
// Defines class used to represent symbols.
// Later labs will add features to this class.
//
// Author: Phil Howard 
//
// Edited by: Junmin Yee
// Date: Jan. 31, 2019
//

#include <string>

using std::string;

#include "cAstNode.h"

class cSymbol : public cAstNode
{
    public:
        // param is name of symbol
        cSymbol(string name) : cAstNode()
        {
            m_id = ++nextId;        // get next available ID
            m_name = name;
            m_type = false;         // auto create as false
        }

        // return name of symbol
        string GetName() { return m_name; }

        virtual string AttributesToString()
        {
            string result(" id=\"");
            result += std::to_string(m_id);
            result += "\" name=\"" + m_name + "\"";
            return result;
        }
        virtual string NodeType() { return string("sym"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        // getters and setters for type
        bool IsType()
        {
            return m_type;
        }

        void SetType(bool type)
        {
            m_type = type;
        }
    protected:
        static long long nextId;        // Next avail symbol ID
        long long m_id;                 // Unique ID for this symbol
        string m_name;                  // name of symbol
        bool m_type;                    // whether it is type or identifier
                                        // true is type, false is identifier
};
