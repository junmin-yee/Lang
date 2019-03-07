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
#include "langparse.h"
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
            node->Visit(this);
        }

        virtual void Visit(cBinaryExprNode *node)
        {
            node->GetExprLeft()->Visit(this);
            node->GetExprRight()->Visit(this);
            switch (node->GetOp()->GetOp())
            {
                case '+':
                    EmitString("PLUS\n");
                    break;
                case '-':
                    EmitString("MINUS\n");
                    break;
                case '*':
                    EmitString("TIMES\n");
                    break;
                case '/':
                    EmitString("DIVIDE\n");
                    break;
                case '%':
                    EmitString("MOD\n");
                    break;
                case EQUALS:
                    EmitString("EQ\n");
                    break;
                case NEQUALS:
                    EmitString("NE\n");
                    break;
                case AND:
                    EmitString("AND\n");
                    break;
                case OR:
                    EmitString("OR\n");
                    break;
            }
        }

        virtual void Visit(cIfNode *node)
        {
            node->GetExpr()->Visit(this);
            string elselabel = GenerateLabel();
            string endiflabel = GenerateLabel();

            // Jump to else if condition = 0
            EmitString("JUMPE @" + elselabel + "\n");

            // If block
            node->GetIfStmts()->Visit(this);
            EmitString("JUMP @" + endiflabel + "\n");

            // Else block
            EmitString(elselabel + ":\n");
            node->GetElseStmts()->Visit(this);

            // End of if stmt
            EmitString(endiflabel + ":\n");
        }

        virtual void Visit(cIntExprNode *node)
        {
            EmitString("PUSH ");
            EmitInt(node->GetValue());
        }

        virtual void Visit(cPrintNode *node)
        {
            node->GetExpr()->Visit(this);
            EmitString("CALL @print\n");
            EmitString("POP\n");
            EmitString("POP\n");
        }

        virtual void Visit(cProgramNode *node)
        {
            EmitString("main:\n");
            VisitAllChildren(node);
        }
};
