/* Declaration Section */
%{
int no_of_lines = 0;
int no_of_chars = 0;
%}

/* Rules Section */
%% 
\n ++no_of_lines;
. ++no_of_chars;
end return 0;
%%

/* C code section */
int yywrap(){return 0;}
int main() {
    yylex();
    printf("number of lines = %d, and number of chars = %d\n", no_of_lines, no_of_chars);
    return 0;
}