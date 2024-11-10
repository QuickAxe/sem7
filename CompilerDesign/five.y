%{
    #include<stdio.h>
    #include<stdlib.h>
    void yyerror(char *);
    int yylex(void);
%}

%token ID RELOP FOR NUM WHILE IF
%start S 

%% 



S : ForLoop '{' Stmt ';' Stmt ';' Stmt ';' '}'                           {printf("\nValid For loop syntax\n\n");}
   |WhileLoop '{' Stmt ';' Stmt ';' Stmt ';' '}'                         {printf("\nValid while loop syntax\n\n");}

ForLoop : FOR '(' Itr ';' Cond ';' Inc ')'                               {}

WhileLoop : WHILE '(' Cond ')'                                           {}

Ifstmt : IF '(' Cond ')' Stmt                                            {}

Stmt : ForLoop                                                           {}
        | WhileLoop                                                      {}
        | Ifstmt                                                         {}
        | Itr                                                            {}
        | ';' Stmt                                                       {}

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

#ifdef YYDEBUG 
    yydebug = 0;
#endif 

int main(void)
{
    yyparse();
    return 0;
}
// while(i<=2){if(i>=2) i = i + 3;m = 33; y = y+4;}