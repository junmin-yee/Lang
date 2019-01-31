%{
//**************************************
// lang.l
//
// scanner definition file. flex uses this file to create the scanner
//
// Author: <<<< Junmin Yee >>>>
//

#include "lex.h"
#include "astnodes.h"
#include "langparse.h"
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
"{"                         DO_RETURN('{');
"}"                         DO_RETURN('}');
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
"struct"                    DO_RETURN(STRUCT);
"array"                     DO_RETURN(ARRAY);
"return"                    DO_RETURN(RETURN);
{identifier}                {
                                yylval.symbol = g_SymbolTable.Find(yytext);
                                if (yylval.symbol == nullptr)
                                {
                                    cSymbol * temp = new cSymbol(yytext);
                                    yylval.symbol = temp;
                                }
                                if (yylval.symbol->IsType())
                                {
                                    DO_RETURN(TYPE_ID);
                                }
                                else
                                {
                                    DO_RETURN(IDENTIFIER);
                                }
                            }
{intconst}                  {
                                yylval.int_val = atoi(yytext);
                                DO_RETURN(INT_VAL);
                            }
{floatconst}                {
                                yylval.float_val = atof(yytext);
                                DO_RETURN(FLOAT_VAL);
                            }
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
