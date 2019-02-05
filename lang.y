%{
//**************************************
// lang.y
//
// Parser definition file. bison uses this file to generate the parser.
//
// Author: Junmin Yee 
//

#include <iostream>
#include "lex.h"
#include "cSymbolTable.h"
#include "astnodes.h"

%}

%locations

 /* union defines the type for lexical values */
%union{
    int             int_val;
    float           float_val;
    cAstNode*       ast_node;
    cProgramNode*   program_node;
    cBlockNode*     block_node;
    cStmtsNode*     stmts_node;
    cStmtNode*      stmt_node;
    cExprNode*      expr_node;
    cIntExprNode*   int_node;
    cFloatExprNode* float_node;
    cSymbol*        symbol;
    symbolTable_t*  symbol_table;
    cDeclNode*      decl_node;
    cDeclsNode*     decls_node;
    cVarDeclNode*   var_decl_node;
    cVarExprNode*   var_expr_node;
    cStructDeclNode* struct_decl_node;
    cParamsNode*    params_node;
    cParamListNode* param_list_node;
    cFuncDeclNode*  func_decl_node;
    cFuncExprNode*  func_expr_node;
    }

%{
    int yyerror(const char *msg);

    cAstNode *yyast_root;
%}

%start  program

%token <symbol>    IDENTIFIER
%token <symbol>    TYPE_ID
%token <int_val>   CHAR_VAL
%token <int_val>   INT_VAL
%token <float_val> FLOAT_VAL
%token <int_val>   AND
%token <int_val>   OR
%token <int_val>   EQUALS
%token <int_val>   NOT_EQUALS

%token  PROGRAM
%token  PRINT
%token  WHILE IF ELSE ENDIF
%token  STRUCT ARRAY
%token  RETURN
%token  JUNK_TOKEN

%type <program_node> program
%type <block_node> block
%type <symbol_table> open
%type <symbol_table> close
%type <decls_node> decls
%type <decl_node> decl
%type <var_decl_node> var_decl
%type <struct_decl_node> struct_decl
%type <ast_node> array_decl
%type <symbol_table> func_decl
%type <ast_node> func_header
%type <symbol_table> func_prefix
%type <ast_node> func_call
%type <ast_node> paramsspec
%type <ast_node> paramspec
%type <stmts_node> stmts
%type <stmt_node> stmt
%type <var_expr_node> lval
%type <ast_node> params
%type <ast_node> param
%type <expr_node> expr
%type <expr_node> addit
%type <expr_node> term
%type <expr_node> fact
%type <var_expr_node> varref
%type <symbol> varpart

%%

program: PROGRAM block          { $$ = new cProgramNode($2);
                                  yyast_root = $$;
                                  if (yynerrs == 0) 
                                      YYACCEPT;
                                  else
                                      YYABORT;
                                }
block:  open decls stmts close  { $$ = new cBlockNode($2, $3); }
    |   open stmts close        { $$ = new cBlockNode(nullptr, $2); }

open:   '{'                     { $$ = g_SymbolTable.IncreaseScope();  }

close:  '}'                     { $$ = g_SymbolTable.DecreaseScope(); }

decls:      decls decl          { $$->Insert($2); }
        |   decl                { $$ = new cDeclsNode($1); }
decl:       var_decl ';'        { $$ = $1; }
        |   struct_decl ';'     { $$ = $1; }
        |   array_decl ';'      {  }
        |   func_decl           {  }
        |   error ';'           {  }

var_decl:   TYPE_ID IDENTIFIER  { $$ = new cVarDeclNode($1, $2); }
struct_decl:  STRUCT open decls close IDENTIFIER    
                                { $$ = new cStructDeclNode($3, $5); }
array_decl: ARRAY TYPE_ID '[' INT_VAL ']' IDENTIFIER
                                {  }

func_decl:  func_header ';'
                                { $$ = g_SymbolTable.DecreaseScope(); }
        |   func_header  '{' decls stmts '}'
                                { $$ = g_SymbolTable.DecreaseScope(); }
        |   func_header  '{' stmts '}'
                                { $$ = g_SymbolTable.DecreaseScope(); }
func_header: func_prefix paramsspec ')'
                                {  }
        |    func_prefix ')'    {  }
func_prefix: TYPE_ID IDENTIFIER '('
                                { $$ = g_SymbolTable.IncreaseScope(); }
paramsspec: paramsspec',' paramspec 
                                {  }
        |   paramspec           {  }

paramspec:  var_decl            {  }

stmts:      stmts stmt          { $$->Insert($2); }
        |   stmt                { $$ = new cStmtsNode($1); }

stmt:       IF '(' expr ')' stmts ENDIF ';'
                                { $$ = new cIfNode($3, $5, nullptr); }
        |   IF '(' expr ')' stmts ELSE stmts ENDIF ';'
                                { $$ = new cIfNode($3, $5, $7); }
        |   WHILE '(' expr ')' stmt 
                                { $$ = new cWhileNode($3, $5); }
        |   PRINT '(' expr ')' ';'
                                { $$ = new cPrintNode($3); }
        |   lval '=' expr ';'   { $$ = new cAssignNode($1, $3); }
        |   lval '=' func_call ';'   {  }
        |   func_call ';'       {  }
        |   block               {  }
        |   RETURN expr ';'     { $$ = new cReturnNode($2); }
        |   error ';'           {}

func_call:  IDENTIFIER '(' params ')' {  }
        |   IDENTIFIER '(' ')'  {  }

varref:   varref '.' varpart    { $$->Insert($3); }
        | varref '[' expr ']'   {  }
        | varpart               { $$ = new cVarExprNode($1); }

varpart:  IDENTIFIER            {  }

lval:     varref                { $$ = $1; }

params:     params',' param     {  }
        |   param               {  }

param:      expr                {  }

expr:       expr EQUALS addit   {  }
        |   addit               { $$ = $1; }

addit:      addit '+' term      { $$ = new cBinaryExprNode($1, '+', $3); }
        |   addit '-' term      { $$ = new cBinaryExprNode($1, '-', $3); }
        |   term                {  }

term:       term '*' fact       { $$ = new cBinaryExprNode($1, '*', $3); }
        |   term '/' fact       { $$ = new cBinaryExprNode($1, '/', $3); }
        |   term '%' fact       { $$ = new cBinaryExprNode($1, '%', $3); }
        |   fact                {  }

fact:        '(' expr ')'       { $$ = $2; }
        |   INT_VAL             { $$ = new cIntExprNode($1); }
        |   FLOAT_VAL           { $$ = new cFloatExprNode($1); }
        |   varref              { $$ = $1; }

%%

// Function to format error messages
int yyerror(const char *msg)
{
    std::cerr << "ERROR: " << msg << " at symbol "
        << yytext << " on line " << yylineno << "\n";

    return 0;
}
