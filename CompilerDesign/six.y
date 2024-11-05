%{
    #include<stdlib.h>
    #include<stdio.h>
    int yylex(void);
    void yyerror(char*);

    // functino to actually assign memory to variables
    void assignData(int);

    // simulating memory locations for variables
    float fMem[30];
    int iMem[30];

    //simulating a symbol table 
    int symbol[30];

    // a flag to store the datatype of the current declaration statement
    // integer by default 
    char datatypeFlag = 'i'; 

    // global values to store the count of integer and float variables 
    int intCount = 0, floatCount = 0;

%}

%token ID 
%token FLOAT INT
 

%% 

S : D V ';'     {printf("valid statement, memory allocated successfully\n\n");}

D : INT         {}
  | FLOAT       {datatypeFlag = 'f';} 

V : ID          {assignData($1);}
  | ID ',' V    {assignData($1);}

%% 

void assignData(int index)
{   
    // simulating assigning memory
    // a better way to do this would be using linked lists and dynamic memory,
    // but that's probably beyond the scope of this experiment requirements

    // check if the symbol is already being used
    if(symbol[index] != -1)
    {
        printf("Error, variable name \"%c\" already assigned\n", (char)index + 'a' );
        exit(0);
    }

    if(datatypeFlag == 'f')
        {   printf("Added new float variable at location: %d \n", floatCount);
            symbol[index] = floatCount;
            fMem[floatCount++] = 0;}
    else 
        {   printf("Added new int variable at location: %d \n", intCount);
            symbol[index] = intCount;
            iMem[intCount++] = 0;}
}

void yyerror(char *errorChar)
{
    fprintf(stderr, "Error, invalid char: %s", errorChar);
}

int main()
{
    // init symbol table
    for(int i=0; i<30; i++)
        {symbol[i] = -1;}
    
    yyparse();
    return 0;
}