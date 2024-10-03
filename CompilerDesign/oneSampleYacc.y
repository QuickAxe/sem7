%{
#include<stdlib.h>
#include<stdio.h>
int yylex(void);
void yyerror(char*, char*);
%}

%token ID 
%token FLOAT INT

%% 

S : D V '\n' {printf("valid statement");}

D : INT {}
  | FLOAT {} 

V : ID ';' {}
  | ID ';' V {}

%% 

void yyerror(char* s, char *errorChar)
{
    fprint(stderr, "%s %s", s, errorChar);
}

int main()
{
    yyparse();
    return 0;
}