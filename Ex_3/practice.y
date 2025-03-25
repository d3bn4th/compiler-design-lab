%{
    #include<stdio.h>
    #include<stdlib.h>
    extern int yylex();
    void yyerror(const char* s);
%}

%union {
    int num;
}

%token <num> NUMBER
%type <num> expr
%left '+' '-'
%left '*' '/'
%right UMINUS

%%
input:
    | input line
    ;
line:
    expr '\n' {printf("Result: %d\n", $1);}
    ;
expr:
    NUMBER {$$ = $1;}
    | expr '+' expr { $$ = $1 + $3;}
    | expr '-' expr { $$ = $1 - $3;}
    | expr '*' expr { $$ = $1 * $3;}
    | expr '/' expr { 
        if($3 == 0) {printf("Error: Division by zero\n"); exit(1);}
        else {$$ = $1 / $3;}
    }
    | '(' expr ')' {$$ = $2;}
    | '-' expr %prec UMINUS {$$ = -$2;}
    ;
%%

/* Proper definition of yyerror() */
void yyerror(const char* s) {
    fprintf(stderr, "Error: %s\n", s);
}

// Main function
int main() {
    printf("Simple Calculator: \n");
    return yyparse();
}