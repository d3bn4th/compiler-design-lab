/* Definitions Section */
%{

int no_of_lines = 0;
int no_of_chars = 0;
%}

/* Rules Section */
%%
\n ++no_of_lines;    /* Count newlines */
. ++no_of_chars;     /* Count all other characters */
end return 0;        /* Return when 'end' is encountered */
%%

/* C Code Section */
int yywrap(){return 1;}
int main(){ 
    yylex();
    printf("number of lines = %d, number of chars = %d\n",no_of_lines, no_of_chars );
    return 0;
}