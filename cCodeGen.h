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

        virtual void Visit(cAssignNode *node)
        {
            node->GetRight()->Visit(this);
            
            // Save to memory location
            if(node->GetLeft()->GetSize() == 1)
            {
                EmitString("POPCVAR");
                EmitInt(node->GetLeft()->GetOffset());
            }
            else
            {
                EmitString("POPVAR");
                EmitInt(node->GetLeft()->GetOffset());
            }
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

        virtual void Visit(cFuncDeclNode *node)
        {
            // Only generate code if node is a definition
            if (node->IsDefinition())
            {
                // Function label
                EmitString(node->GetFuncName()->GetName() + ":\n");

                if (node->GetDecls() != nullptr)
                {
                    EmitString("ADJSP");
                    EmitInt(node->GetDecls()->GetSize());
                }
                VisitAllChildren(node);
            }
        }

        virtual void Visit(cFuncExprNode *node)
        {
            // If there are params, push on stack
            if (node->GetParamList() != nullptr)
                node->GetParamList()->Visit(this);
            EmitString("CALL @" + node->GetFuncName()->GetName() + "\n");

            if (node->GetParamList() != nullptr)
            {
                EmitString("POPARGS");
                EmitInt(node->GetParamList()->NumParams() * 4);
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
            if (node->GetElseStmts() != nullptr)
            {
                node->GetElseStmts()->Visit(this);
            }

            // End of if stmt
            EmitString(endiflabel + ":\n");
        }

        virtual void Visit(cIntExprNode *node)
        {
            EmitString("PUSH");
            EmitInt(node->GetValue());
        }

        virtual void Visit(cParamListNode *node)
        {
            // Visit right to left
            for (int i = node->NumParams() - 1; i >= 0; --i)
            {
                node->GetExpr(i)->Visit(this);
            }
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
            // Visit decls to generate func decls if necessary
            if (node->GetBlock()->GetDecls() != nullptr)
                node->GetBlock()->GetDecls()->Visit(this);

            EmitString("main:\n");
            EmitString("ADJSP");
            int temp = node->GetBlock()->GetSize();
            if (temp % 4 != 0)
                temp += 4 - temp % 4;
            EmitInt(temp);
            
            // Visit rest of block
            if (node->GetBlock()->GetStmts() != nullptr)
                node->GetBlock()->GetStmts()->Visit(this);
        }

        virtual void Visit(cReturnNode *node)
        {
            node->GetExpr()->Visit(this);
            EmitString("RETURNV\n");
        }

        virtual void Visit(cVarExprNode *node)
        {
            if(node->GetSize() == 1) // If char
            {
                EmitString("PUSHCVAR");
                EmitInt(node->GetOffset());
            }
            else // If int
            {
                EmitString("PUSHVAR");
                EmitInt(node->GetOffset());
            }
        }

        virtual void Visit(cWhileNode *node)
        {
            string looplabel = GenerateLabel();
            string endlooplabel = GenerateLabel();

            EmitString(looplabel + ":\n");

            // Evaluate expression
            node->GetExpr()->Visit(this);

            // If condition fails, end loop
            EmitString("JUMPE @" + endlooplabel + "\n");

            node->GetStmt()->Visit(this);

            // Go back to start of loop
            EmitString("JUMP @" + looplabel + "\n");

            EmitString(endlooplabel + ":\n");
        }
};
