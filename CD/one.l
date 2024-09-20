%%

"(" printf("open brace\n");
")" printf("close brace\n");

"{" printf("open bracket curly\n");
"}" printf("close bracket curly\n");
"]" printf("close brace square\n");
"[" printf("open brace square\n");

[A-Za-z_][A-Za-z0-9_]* printf("token: %s\n", yytext); 
[=+-/*%] printf("operator: %s", yytext);

" " printf("white space\n");

\n printf("new line \n");
. printf("error\n");

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


