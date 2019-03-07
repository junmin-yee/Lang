#pragma once
//************************************************************
// cCodeGen.h
//
// Subclasses the Visitor class to generate code
//
// Author: Junmin Yee
// Date: Mar. 06, 2019
//

#include "emit.h"
#include "cVisitor.h"

class cCodeGen : public cVisitor
{
    public:
        cCodeGen(string filename) : cVisitor()
        {
            InitOutput(filename.c_str());
        }

        ~cCodeGen()
        {
            FinalizeOutput();
        }

        virtual void VisitAllNodes(cAstNode *node)
        {
            VisitAllChildren(node);
        }

        virtual void Visit(cIntExprNode *node)
        {
            EmitInt(node->GetValue());
        }

        virtual void Visit(cFloatExprNode *node)
        {}

        virtual void Visit(cPrintNode *node)
        {
            Temp = node->GetExpr()->Visit(this);
            EmitPrintTemp();
        }
};
