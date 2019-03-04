#pragma once
//**************************************
// cDeclsNode.h
//
// Defines a class to represent a list of declarations.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cDeclNode.h"

class cDeclsNode : public cAstNode
{
    public:
        // param is the first decl in this decls
        cDeclsNode(cDeclNode *decl) : cAstNode()
        {
            AddChild(decl);
        }

        // Add a decl to the list
        void Insert(cDeclNode *decl)
        {
            AddChild(decl);
        }

        virtual string AttributesToString()
        {
            if (m_size == 0) return "";
            else
            {
                string result(" size=\"");
                result += std::to_string(m_size);
                result += "\"";
                return result;
            }
        }
        virtual string NodeType() { return string("decls"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        int NumDecls() { return NumChildren(); }
        cDeclNode * GetDecl(int index) 
        { 
            return dynamic_cast<cDeclNode*>(GetChild(index)); 
        }

        int GetSize() { return m_size; }
        void SetSize(int size) { m_size = size; }

    protected:
        int m_size;             // size of decls
};
