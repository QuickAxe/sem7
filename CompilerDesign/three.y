%{
    #include<stdio.h>
    #include<stdlib.h>
    void yyerror(char *);
    int yylex(void);
%}

%token ID RELOP FOR NUM WHILE
%start S 

%% 

S: ForLoop {printf("\nValid For loop syntax\n\n");}
   | WhileLoop {printf("\nValid While loop syntax\n\n");}

ForLoop : FOR '(' Itr ';' Cond ';' Inc ')' ';'  {}

WhileLoop : WHILE '(' Cond ')' ';'

Itr : ID '=' Exp {}

Cond : ID RELOP ID {}
     | ID RELOP NUM {}

Inc : ID '+''+' {}
    | ID '-''-' {}
    | '+''+' ID {}
    | '-''-' ID {}

Exp  :  Exp '+' Exp2    {}
     |  Exp2            {}

Exp2 :  Exp2 '-' ID     {}
     |  ID              {}
     |  NUM              {}




%%

void yyerror(char *err)
{
    fprintf(stderr, "Error:  %s\n\n", err);
}

int main(void)
{
    yyparse();
    return 0;
}