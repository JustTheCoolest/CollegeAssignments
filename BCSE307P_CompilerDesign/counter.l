%option noyywrap

%{
#include <stdio.h>
int words = 0;
int chars = 0;
int lines = 0;
%}

delim [ \t]+

%%
\n {++chars; ++words; ++lines;}
^delim {chars += yyleng;}
delim {++words; chars+=yyleng;}
. {++chars;}
%%

int main(){
    yylex();
    printf("Characters: %d\nWords: %d\nLines: %d\n", chars-1, words, lines);
}