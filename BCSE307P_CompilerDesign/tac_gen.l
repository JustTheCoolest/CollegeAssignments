%{
/*
To impliment:
- Unary minus
- Brackets
*/
%}

var [a-z]
op [+*/-]

%{
float var_stack[100];
char op_stack[100];
unsigned int var_top = 0;
unsigned int op_top = 0;

int var_flag = 0;
int inst_counter = 0;

char start_char = 'A';

void var_push(char var){
    var_stack[var_top++] = var;
    var_flag = 1;
}

struct tac_record{
    char res;
    char arg1;
    char op;
    char var;
};

struct tac_record tac[100];
int tac_top = 0;

void op_push(char op){
    if(!var_flag){
        if(op == '-'){
            op_stack[op_top++] = '#';
        }
        else{
            fprintf(stderr, "unary operator detected but not recognised: %c\n", op);
        }
    }
    else{
        op_stack[op_top++] = op;
    }
    var_flag = 0;
}

int precedence(int op_pos){
    if(op_pos<0){
        fprintf(stderr, "op_pos not in stack bounds: %d", op_pos);
    }
    char op = op_stack[op_pos];
    if(op == '#'){
        return -5;
    }
    else if(op=='/'){
        return -10;
    }
    else if(op=='*'){
        return -10;
    }
    else if(op=='+'){
        return -15;
    }
    else if(op=='-'){
        return -15;
    }
    else{
        fprintf(stderr, "operator not recognised: %c", op);
    }
}

void execute(){
    char op = op_stack[--op_top];
    char arg2 = var_stack[--var_top];
    if(op=='#'){
        struct tac_record trec = {
            start_char + inst_counter,
            '\0',
            '-',
            arg2
        };
        tac[tac_top++] = trec;
    }
    else{
        char arg1 = var_stack[--var_top];
        struct tac_record trec = {
            start_char + inst_counter,
            arg1,
            op,
            arg2
        };
        tac[tac_top++] = trec;
    }
    ++inst_counter;
}

void eval(){
    while(op_top >= 2 && precedence(op_top-1) <= precedence(op_top-2)){
        char op = op_stack[--op_top];
        char var = var_stack[--var_top];
        execute();
        op_stack[op_top++] = op;
        var_stack[var_top++] = op;
    }
}

void clean_up(){
    while(op_top > 0){
        execute();
    }
}

void print_tac(){
    printf("Total instructions: %d\n", inst_counter);
    printf("TAC Top: %d\n", tac_top);
    printf("Quadruples:\n");
    printf("res\targ1\top\targ2\n");
    for(int i=0; i<tac_top; ++i){
        struct tac_record trec = tac[i];
        printf("%c\t%c\t%c\t%c\n", trec.res, trec.arg1, trec.op, trec.var);
    }
}

%}

%%
[ ] {}
{var} {var_push(yytext[0]); eval();}
{op} {op_push(yytext[0]);}
\n {clean_up();}
%%

int main(){
    yylex();
    print_tac();
}