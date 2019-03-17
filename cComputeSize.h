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
        }

        virtual void VisitAllNodes(cAstNode *node)
        {
            VisitAllChildren(node);
        }
        
        virtual void Visit(cBlockNode *node)
        {
            // Save incoming values
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

        virtual void Visit(cDeclsNode *node)
        {
            int currentOffset = m_offset;
            VisitAllChildren(node);

            node->SetSize(m_offset - currentOffset);
        }
        
        virtual void Visit(cFuncDeclNode *node)
        {
            // Save incoming values
            int currentOffset = m_offset;
            int currentHigh = m_highWater;
            m_offset = 0;
            m_highWater = 0;
            node->SetOffset(m_offset);

            VisitAllChildren(node);
            
            m_highWater = RoundUp(m_highWater);
            node->SetSize(m_highWater);

            // Reset variables once func decl is over
            m_offset = currentOffset;
            m_highWater = currentHigh;
        }

        virtual void Visit(cParamsNode *node)
        {
            // Stack overhead
            m_offset = -12;

            // Need to loop because in other direction
            for (int i = 0; i < node->NumParams(); ++i)
            {
                cDeclNode * param = node->GetDecl(i);
                param->SetSize(param->GetType()->GetSize());
                param->SetOffset(m_offset);

                m_offset -= param->GetSize();
                m_offset = RoundDown(m_offset);
            }

            // Compute size based on call stack overhead
            node->SetSize(-12 - m_offset);

            // Reset offset for function locals
            m_offset = 0;
        }

        virtual void Visit(cStructDeclNode *node)
        {
            // Save and reset offset
            int currentOffset = m_offset;
            m_offset = 0;
            node->SetOffset(m_offset);

            VisitAllChildren(node);

            node->SetSize(m_offset);

            // Reset offset once struct decl is over
            m_offset = currentOffset;
        }

        virtual void Visit(cVarDeclNode *node)
        {
            VisitAllChildren(node);

            node->SetSize(node->GetType()->GetSize());

            // If offset is not a char or if from params
            if (node->GetSize() != 1)
            {
                m_offset = RoundUp(m_offset);
            }

            node->SetOffset(m_offset);
            m_offset += node->GetSize();

            if (m_offset > m_highWater) // Track high water mark if needed
                m_highWater = m_offset; 
        }

        virtual void Visit(cVarExprNode *node)
        {
            node->SetSize(node->GetDecl()->GetSize());

            // Iterate through each symbol to find each offset
            // If placed in Visit function for cSymbol,
            // visiting cSymbol would affect multiple classes
            int totalOffset = 0;
            for (int i = 0; i < node->NumSymbols(); ++i)
            {
                totalOffset += node->GetSymbol(i)->GetDecl()->GetOffset();
            }
            node->SetOffset(totalOffset);
        }

    private:
        int m_offset;           // offset for program
        int m_highWater;        // high water mark

        // Word aligns incoming value
        int RoundUp(int value)
        {
            if(value % 4 != 0)
                value += 4 - value % 4;

            return value;
        }

        // Word aligns incoming values for negative stack addresses
        int RoundDown(int value)
        {
            if(value % 4 != 0)
                value -= 4 + value % 4;

            return value;
        }
};
