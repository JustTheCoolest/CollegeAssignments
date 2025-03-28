identifier [[:alpha:]_][[:alnum:]_]*
number [0-9]+
if if
op " "[^a-zA-Z0-9_]" "

%{
int fact(int n) {
    if (n == 0) return 1;
    return n * fact(n - 1);
}
%}

%%
{if} {printf("if\n");}
{op} {printf("op %s\n", yytext);}
{identifier} {printf("identifier %s\n", yytext);}
{number} {printf("number %s (fact: %d)\n", yytext, fact(atoi(yytext)));}
" " {;}
. {printf("Invalid!\n");}
%%

