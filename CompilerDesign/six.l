%{
    #include "y.tab.h"
    void yyerror(char*);

%}

alpha [a-zA-Z_]
digit [0-9]

%% 

"float"                         {return FLOAT;}
"int"                           {return INT;}
{alpha}                         { yylval = yytext[0] - 'a';  //To convert it to an integer index for storing in an array in the yacc file
                                  return ID;}
","|";"                          { return yytext[0];}
[ \t\n]                           ;
.                               {yyerror(yytext);}

%%

int yywrap(void)
{ return 1;}
