%{
#include<stdlib.h>
#include<stdio.h>
int yylex(void);
void yyerror(char*);
%}

%token ID 
%token FLOAT INT

%% 

S : D V '\n' {printf("valid statement");}

D : INT {}
  | FLOAT {} 

V : ID ';' {}
  | ID ',' V {}

%% 

void yyerror(char *errorChar)
{
    fprintf(stderr, "Error, invalid chars: %s", errorChar);
}

int main()
{
    yyparse();
    return 0;
}