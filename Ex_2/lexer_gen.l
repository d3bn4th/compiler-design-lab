/* Code for Lexical Analyzer Generator */
/* Declaration section */
%{
    #include<stdio.h>
    #include <math.h>
    #include <stdlib.h>
%}

DIGIT   [0-9]
ID      [a-zA-Z][a-zA-Z0-9]*
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
    return 1; // Tell scanner to stop scanning (return 0 to tell scanner to continue scanning )
}

int main() {
    FILE *fp;
    char filename[50];
    printf("Enter the filename: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("Error while opening the file\n");
        return 1;
    }
    // predefined file pointer that specifies the input source for the lexical analyzer(default: stdin)
    yyin = fp; // Tells flex to read from this file
    yylex(); // start scanning
    fclose(fp);
    return 0;
}