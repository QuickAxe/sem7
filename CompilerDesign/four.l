%{
    #include "y.tab.h"
    void yyerror(char*);

%}

alpha [a-zA-Z_]
digit [0-9]

%%

{alpha}                        {yylval = yytext[0];
                                return ID;}
{digit}+                       {yylval = yytext[0] - '0';
                                return NUM;}
[\n\;()+-=*/]                    {return yytext[0];}
[ \t]                        ;
.                              {yyerror(yytext);}

%% 

int yywrap(void)
{
    return 1;
}