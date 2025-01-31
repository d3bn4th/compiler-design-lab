%{
#include "calc.tab.h"
#include <stdio.h>
#include <stdlib.h>
%}

%%
[0-9]+    { yylval.num = atoi(yytext); return NUMBER; }
"+"       { return '+'; }
"-"       { return '-'; }
"*"       { return '*'; }
"/"       { return '/'; }
"("       { return '('; }
")"       { return ')'; }
\n        { return '\n'; }
[ \t]     { /* Ignore whitespace */ }
.         { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() { return 1; }
