%%

alpha [a-zA-Z_]
digit [0-9]

%% 

"float" return FLOAT;
"int" return INT;

{alpha}({alpha}|{digit})* return ID;

[,;\n] return *yytext;
[ \t] ;

. {yyerror("invalid character: ", *yytext); exit(0);}

%%

int yywrap(void)
{ return 1;}
