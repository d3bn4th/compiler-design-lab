/* Code for lexical analyzer generator */
/* Declaration Section */
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
%}

DIGIT   [0-9]
ID      [a-z][a-zA-Z0-9]*

/* Rules Section*/
%%
[ \t\n]                   /* Ignore whitespaces*/
"int"|"main"|"return"     { printf("Keyword: %s\n", yytext);}
{DIGIT}+                  { printf("Integer: %s\n", yytext);}
{ID}                      { printf("Identifier: %s\n", yytext);}
"="                       { printf("Assignment: %s\n", yytext);}  
"+"|"-"|"/"|"*"           { printf("Operator: %s\n", yytext);}  
"("                       { printf("Parenthesis: %s\n", yytext);}  
")"                       { printf("Parenthesis: %s\n", yytext);}  
"{"                       { printf("Braces: %s\n", yytext);}  
"}"                       { printf("Braces: %s\n", yytext);}  
","|";"                   { printf("Separator: %s\n", yytext);}  
.                         { printf("Unrecognized: %s\n", yytext);}  
%%

int yywrap() {
    return 1; 
}
int main() {
    FILE *fp;
    char filename[20];
    printf("Enter filename: ");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("Error");
        return 1;
    }
    yyin = fp; 
    yylex();
    fclose(fp);
    return 0;
}
