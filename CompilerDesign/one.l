%%

"(" return *yytext;
")" return *yytext;

"{" return *yytext;
"}" return *yytext;
"]" return *yytext;
"[" return *yytext;

[A-Za-z_][A-Za-z0-9_]* return *yytext;
[=+-/*%] return *yytext;

" " return *yytext;

\n return *yytext;
. return *yytext;

%% 

int yywrap()
{
    return 1;
}

int main()
{
    yylex();
    return 0;
}


