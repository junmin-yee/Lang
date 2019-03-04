#pragma once
//**************************************
// cVarExprNode.h
//
// Defines a variable reference which is an expression.
// Inherits from cExprNode so that variable references can be
// used anywhere. 
//
// Author: Junmin Yee 
// Date: Jan. 31, 2019
//
#include "cExprNode.h"
#include "cSymbol.h"

class cVarExprNode : public cExprNode
{
    public:
        // param is first ref
        cVarExprNode(cSymbol *ref) : cExprNode()
        {
            if (g_SymbolTable.Find(ref->GetName()) == nullptr)
            {
                string error = "Symbol " + ref->GetName() + " not defined";
                SemanticError(error);
            }
            AddChild(ref);
        }

        // Add symbol to the list
        void InsertField(cSymbol *sym)
        {
            if(!GetLastChild()->GetDecl()->IsStruct())
            {
                string error = (GetName() + " is not a struct");
                SemanticError(error);
            }
            else 
            {
                // Get the struct decl
                cStructDeclNode * found = dynamic_cast<cStructDeclNode*>
                    (GetLastChild()->GetDecl()->GetType());

                cSymbol * temp = found->GetElement(sym->GetName());
                if(temp == nullptr)
                {
                    string error = (sym->GetName() + " is not a field of " + GetName());
                    SemanticError(error); 
                }
                else
                {
                    sym = temp; // Save symbol from above decls
                }
            }
            AddChild(sym);
        }

        // Add expr to the list
        void InsertIndex(cExprNode *expr)
        {
            AddChild(expr);
        }

        int NumSymbols() { return NumChildren(); }

        cSymbol * GetSymbol(int index) 
        {
            return dynamic_cast<cSymbol*>(GetChild(index));
        }

        virtual cDeclNode * GetType()
        {
            return GetLastChild()->GetDecl()->GetType();
        }

        cDeclNode * GetDecl()
        {
            return GetLastChild()->GetDecl();
        }
        
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
        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        // Function to build the variable expression string
        string GetName()
        {
            string name = dynamic_cast<cSymbol*>(GetChild(0))->GetName();
            for(int i = 1; i < NumChildren(); i++)
            {
                name += ".";
                name += dynamic_cast<cSymbol*>(GetChild(i))->GetName();
            }
            return name;
        }

        int GetSize() { return m_size; }
        void SetSize(int size) { m_size = size; }
        int GetOffset() { return m_offset; }
        void SetOffset(int offset) { m_offset = offset; }
        
    protected:
        cSymbol * GetLastChild()
        {
            return dynamic_cast<cSymbol*>(GetChild(NumChildren() - 1));
        }

        int m_size;                 // size of varref
        int m_offset;               // offset of varref
};
