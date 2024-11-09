%{
#include<stdio.h>
#include<string.h>

int yylex(void);
void yyerror(char*);
void Gen(char*);

char buffer[50][50];
char temp2[50];
int tCount = 0;

yydebug = 0;
%}

%union 
{
   char *string_value;
}

%type <string_value> exp 
%type <string_value> COND 
%type <string_value> s 
%type <string_value> stmt
%token <string_value> ID
%token <string_value> OP
%token IF ob1 cb1 ob2 cb2 EQ SC

%%
s	: IF ob1 COND cb1 ob2 stmt cb2	{ sprintf(temp2,"\nt%d=if(%s){JMP %s}",tCount,$3,$6); sprintf($$, "t%d", tCount++ ); Gen(temp2);}


stmt	:s						
        |ID EQ exp SC stmt 			{  	sprintf(temp2,"\nt%d=%s=%s",tCount,$1,$3); sprintf($$, "t%d", tCount++ ); Gen(temp2);   }
        |                           {}



exp  	: exp '+' exp  				{ 	sprintf(temp2,"\nt%d=%s+%s",tCount,$1,$3); sprintf($$, "t%d", tCount++ ); Gen(temp2);   }      
	    | exp '-' exp  				{ 	sprintf(temp2,"\nt%d=%s-%s",tCount ,$1,$3); sprintf($$, "t%d", tCount++ ); Gen(temp2);	} 
        | exp '*' exp  				{	sprintf(temp2,"\nt%d=%s*%s",tCount ,$1,$3); sprintf($$, "t%d", tCount++ ); Gen(temp2);	}   
        | ID	                    {	$$=$1;	}


COND 	:ID OP ID				    {   sprintf(temp2,"\nt%d=%s %s %s",tCount ,$1,$2,$3); sprintf($$, "t%d", tCount++ ); Gen(temp2); }


%%

void Gen(char *val)
{
	FILE *f;
	f=fopen("output.txt","a");
	fputs(val,f);
	fclose(f);
}

int yywrap() { return 1; }

void yyerror(char *s)
{
	return;
}

int main( int argc, char **argv ) {
	yyparse();
	return 1;
}
// if(i == 3){ m = 33; }
//  printf("%s", temp2);