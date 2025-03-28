%{
#include<stdio.h>
%}

%%
[aeiouAEIOU] {printf("%c", yytext[0]);}
[ \n] {printf("%c", yytext[0]);}
. {printf("%c", '-');}
%%

int main(){
    yylex();
}