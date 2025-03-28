digit [0-9]
number {digit}+\.?{digit}*

%{
// const unsigned int STACK_SIZE = 100;
float num_stack[100];
char op_stack[100];
unsigned int num_top = 0;
unsigned int op_top = 0;
%}

%{
void execute(){
    float num2 = num_stack[--num_top];
    float num1 = num_stack[--num_top];
    char op = op_stack[--op_top];
    float result;
    switch(op){
        case '*': result = num1 * num2; break;
        case '/': result = num1 / num2; break;
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        default: fprintf(stderr, "Operator not defined\n");
    }
    num_stack[num_top++] = result;
}

void eval(){
    if(op_top == 0){
        return;
    }
    if(op_stack[op_top-1] == '+' || op_stack[op_top-1] == '-'){
        return;
    }
    execute();
}

void empty(){
    while(op_top > 0){
        execute();
    }
    if(num_top != 1){
        fprintf(stderr, "Semantic error\n");
    }
    printf("Result: %f\n", num_stack[0]);
    num_top = 0;
}
%}

%%
{number} {num_stack[num_top++] = atof(yytext); eval();}
" "+ {}
[+\-*/] {op_stack[op_top++] = yytext[0];}
\n {empty();}
. {fprintf(stderr, "Invalid input\n");}
%%

int main(){
    yylex();
}