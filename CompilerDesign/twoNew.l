
%{
#include <stdio.h>

%}

%%

int|float|char|double|long|if|else|switch|void|for|while|do|case|return|#inlcude|#define {printf("Keyword: %s\n", yytext);}

\*|\+|\-|\/|\%				{ printf("Arithmetic Operator: %s\n", yytext);}
==|<=|>=|<|>    			{ printf("Comparison Operator: %s\n", yytext); }
=               			{ printf("Assignment Operator: %s\n", yytext); }
" "	{printf("Assignment Operator: %s\n", yytext);}
\n                          {printf("New line: %s\n", yytext);}
[_a-zA-Z][_a-zA-Z0-9]* 		{ printf("Identifier : %s\n", yytext); }
[0-9]+                      {printf("Number: %s\n", yytext);}

\(|\{|\[           			{ printf("Opening Bracket : %s\n", yytext);}  
\)|\}|\]           			{ printf("Closing Bracket : %s\n", yytext);}  

;							{ printf("Statement Terminator : %s\n", yytext);}
\\n 						{ printf("Newline : %s\n", yytext);}
\\t 						{ printf("Horizontal End : %s\n", yytext);}

&|\|						{ printf("Bitwise Operator : %s\n", yytext);}
&&|\|\||!					{ printf("Logical Operator : %s\n", yytext);}

.							{ printf("Invalid Token: %s\n", yytext);}


%%

int yywrap(void)
{
    return 1;
}

int main() {
	printf("Enter the expression: \n");
    yylex();
    return 0;
}

// lex two.l && gcc lex.yy.c -o two 