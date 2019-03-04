#pragma once
//************************************************************
// cComputeSize.h
//
// Subclasses the Visitor class to compute the size and offsets
//
// Author: Junmin Yee
// Date: Feb. 28, 2019
//

#include "cVisitor.h"

class cComputeSize : public cVisitor
{
    public:
        cComputeSize() : cVisitor()
        {
            m_offset = 0;
            m_highWater = 0;
            m_isParams = 0;
        }

        virtual void VisitAllNodes(cAstNode *node)
        {
            VisitAllChildren(node);
        }

        virtual void Visit(cVarDeclNode *node)
        {
            VisitAllChildren(node);

            node->SetSize(node->GetType()->GetSize());

            // If offset is not a char or if from params
            if (node->GetSize() != 1 || m_isParams == true)
            {
                if (m_offset % 4 != 0)
                    m_offset += 4 - m_offset % 4;
            }

            node->SetOffset(m_offset);
            m_offset += node->GetSize();

            if (m_offset > m_highWater) // Track high water mark if needed
                m_highWater = m_offset; 
        }

        virtual void Visit(cVarExprNode *node)
        {
            VisitAllChildren(node);

            node->SetSize(node->GetDecl()->GetSize());

            int totalOffset = 0;
            for (int i = 0; i < node->NumSymbols(); ++i)
            {
                totalOffset += node->GetSymbol(i)->GetDecl()->GetOffset();
            }
            node->SetOffset(totalOffset);
        }

        virtual void Visit(cDeclsNode *node)
        {
            int currentOffset = m_offset;
            VisitAllChildren(node);

            node->SetSize(m_offset - currentOffset);
        }

        virtual void Visit(cBlockNode *node)
        {
            int incomingHigh = m_highWater;
            m_highWater = m_offset;
            int currentHigh = m_highWater;
            int currentOffset = m_offset;
            VisitAllChildren(node);

            node->SetSize(m_highWater - currentHigh);

            // Reset offset once block is over
            m_offset = currentOffset;

            // Select highest highwater mark
            m_highWater = (incomingHigh >= m_highWater)? incomingHigh : m_highWater;
        }

        virtual void Visit(cStructDeclNode *node)
        {
            int currentOffset = m_offset;
            m_offset = 0;
            node->SetOffset(m_offset);

            VisitAllChildren(node);

            node->SetSize(m_offset);

            // Reset offset once struct decl is over
            m_offset = currentOffset;
        }

        virtual void Visit(cParamsNode *node)
        {
            m_isParams = true;
            VisitAllChildren(node);
            
            if (m_offset % 4 != 0)
                m_offset += 4 - m_offset % 4;

            node->SetSize(m_offset);
            m_isParams = false;
        }

        virtual void Visit(cFuncDeclNode *node)
        {
            int currentOffset = m_offset;
            int currentHigh = m_highWater;
            m_offset = 0;
            m_highWater = 0;
            node->SetOffset(m_offset);

            VisitAllChildren(node);
            
            if (m_offset % 4 != 0)
                m_offset += 4 - m_offset % 4;

            if (m_highWater % 4 != 0)
                m_highWater += 4 - m_highWater % 4;

            node->SetSize(m_highWater);

            // Reset variables once func decl is over
            m_offset = currentOffset;
            m_highWater = currentHigh;
        }

    private:
        int m_offset;           // offset for program
        int m_highWater;        // high water mark

        int m_isParams;         // track if decls are from params
};
