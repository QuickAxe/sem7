%{
#include "y.tab.h"
#include<stdio.h>
%}

%%
if    			{return IF;}

"(" return ob1;
")" return cb1;
"{" return ob2;
"}" return cb2;
";" return SC;

[\t ]+        

[-+*\n]		        {return *yytext;}

"="			return EQ;

[a-zA-Z0-9]+       	{yylval.string_value = strdup(yytext) ;return ID;}

">"|"<"|">="|"<="|"!="|"=="	{yylval.string_value = strdup(yytext) ;return OP;}
%%
