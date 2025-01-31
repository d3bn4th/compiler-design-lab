%{
#include <math.h>
#include <stdlib.h>
%}

DIGIT   [0-9]
ID      [a-z][a-z0-9]*

%%
{DIGIT}+            { printf("An integer: %s (%d)\n", yytext, atoi(yytext)); }
{DIGIT}+"."{DIGIT}* { printf("A float: %s (%g)\n", yytext, atof(yytext)); }
if|then|begin|end|procedure|function { printf("A keyword: %s\n", yytext); }
{ID}                { printf("An identifier: %s\n", yytext); }
"+"|"-"|"*"|"/"     { printf("An operator: %s\n", yytext); }
"{"[^}]*"}"         { /* Ignore multi-line comments */ }
[ \t\n]+            { /* Ignore whitespace */ }
.                   { printf("Unrecognized character: %s\n", yytext); }
%%

int yywrap() {
    return 1;
}

int main(int argc, char **argv) {
    FILE *fp;
    char filename[50];
    
    printf("Enter the filename: ");
    scanf("%s", filename);
    
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    yyin = fp;
    yylex();
    
    fclose(fp);
    return 0;
}
