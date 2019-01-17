%{
//**************************************
// lang.l
//
// scanner definition file. flex uses this file to create the scanner
//
// Author: <<<< Junmin Yee >>>>
//

#include "lex.h"
#include "tokens.h"
#include "cSymbolTable.h"
// Macros that can be used to create debug output from the scanner
// The first one does NOT create debug output, the second does.
// Uncomment one or the other then use DO_RETURN(val) for all your return 
// statements
#define DO_RETURN(a) { return (a); }
//#define DO_RETURN(a) { return Return(a); }

int Return(int val);

%}

%option noyywrap
%option noinput
%option nounput
%option yylineno


    /* definitions go here. period is an example. */
    /* NOTE: You do not need to use definitions */
identifier      [_a-zA-Z][_a-zA-Z0-9]*
intconst        [0-9]+
floatconst      [0-9]+\.[0-9]+
comment         "//".*
whitespace      [\t \n]
%%

    // token definitions. I gave "program" as an example
"("                         DO_RETURN('(');
")"                         DO_RETURN(')');
"{"                         {
                                g_symbolTable.IncreaseScope();
                                return yytext[0];
                            }
"}"                         {
                                g_symbolTable.DecreaseScope();
                                return yytext[0];
                            }
"["                         DO_RETURN('[');
"]"                         DO_RETURN(']');
";"                         DO_RETURN(';');
","                         DO_RETURN(',');
"."                         DO_RETURN('.');
"+"                         DO_RETURN('+');
"-"                         DO_RETURN('-');
"*"                         DO_RETURN('*');
"/"                         DO_RETURN('/');
"%"                         DO_RETURN('%');
"="                         DO_RETURN('=');
"!="                        DO_RETURN(NOT_EQUALS);
"=="                        DO_RETURN(EQUALS);
"&&"                        DO_RETURN(AND);
"||"                        DO_RETURN(OR);
"program"                   DO_RETURN(PROGRAM);
"if"                        DO_RETURN(IF);
"else"                      DO_RETURN(ELSE);
"endif"                     DO_RETURN(ENDIF);
"while"                     DO_RETURN(WHILE);
"print"                     DO_RETURN(PRINT);
"int"                       DO_RETURN(INT);
"float"                     DO_RETURN(FLOAT);
"char"                      DO_RETURN(CHAR);
"struct"                    DO_RETURN(STRUCT);
"array"                     DO_RETURN(ARRAY);
"return"                    DO_RETURN(RETURN);
{identifier}                {
                                yylval.symbol = g_symbolTable.FindLocal(yytext);
                                if (yylval.symbol == nullptr)
                                {
                                    cSymbol * temp = new cSymbol(yytext);
                                    g_symbolTable.Insert(temp);
                                    yylval.symbol = temp;
                                }
                                return IDENTIFIER;
                            }
{intconst}                  DO_RETURN(INT_VAL);
{floatconst}                DO_RETURN(FLOAT_VAL);
{comment}                   {}
{whitespace}                {}
.                           DO_RETURN(JUNK_TOKEN);

%%

// This function allows us to do extra processing on each token
// It is used to generate lexer debug info
int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}
