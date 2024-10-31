alpha [a-zA-Z_]
digit [0-9]

%%



{alpha}({alpha}|{digit})*      {printf("\nID");}
{digit}+                       {printf("\nnum");}
[\;()+-=*/]                    {printf("\nspecial char");}
[ \t\n]                        printf("blank");
.                              {printf("\nerror");}

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

// "for"                        {printf("for\n");}
// {alpha}({alpha}|{digit})*    {printf("ID\n");}
// {digit}+                      {printf("NUM\n");}
// ">="|"<="                    {printf("relop\n"); }
// [;\n(){}=+-]                   {printf("special char\n");}
// [ \t]                        printf("space or tab\n");
// .                            {printf("error\n");}