%{
#include <stdio.h>
#include <stdlib.h>

/* Declare yylex() properly */
extern int yylex();

/* Declare yyerror() properly */
void yyerror(const char *s);

%}

%union {
    int num;
}

/* Declare token and non-terminal types */
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
    expr '\n' { printf("Result: %d\n", $1); }
    ;

expr:
    NUMBER { $$ = $1; }
    | expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr { if ($3 == 0) { printf("Error: Division by zero!\n"); exit(1); } else $$ = $1 / $3; }
    | '(' expr ')' { $$ = $2; }
    | '-' expr %prec UMINUS { $$ = -$2; }
    ;

%%

/* Proper definition of yyerror() */
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

/* Main function */
int main() {
    printf("Simple Calculator (Type expressions and press Enter)\n");
    printf("Example: 3 + 5 * (2 - 1)\n");
    printf("Press Ctrl+C to exit\n");
    return yyparse();
}
