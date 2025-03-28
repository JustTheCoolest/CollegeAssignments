%{
#include<stdio.h>
%}

%%
. {printf("It's a dot!");}
%%

int main(){
    yylex();
}