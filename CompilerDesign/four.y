%{
    #include<stdio.h>
    #include<stdlib.h>
    void yyerror(char *);
    int yylex(void);
    int val=0;
%}

%token ID NUM
%start S 

%% 

S: ID '=' Exp '\n'        {printf("Valid Expression, value is: %d", $3);}

Exp   :  Exp '-' Exp2     {$$ = $1 - $3;}
      |  Exp2             {$$ = $1;}

Exp2  :  Exp2 '+' Exp3    {$$ = $1 + $3;}
      |  Exp3             {$$ = $1;}

Exp3  :  Exp3 '*' Exp4    {$$ = $1 * $3;}
      |  Exp4             {$$ = $1;}

Exp4  :  Exp4 '/' Exp5    {$$ = $1 / $3;}
      |  Exp5             {$$ = $1;}

Exp5  :  '(' Exp ')'      {$$ = $2;}
      |  NUM              {$$ = $1;}

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