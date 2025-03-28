%{
/*
To impliment:
- Unary minus
- Brackets
- Bug: Precedence conflicts with brackets because var_stack vs op_stack
*/
%}

var [a-z()]
op [=+*/-]

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
    if(var != '(' && var != ')'){
        var_flag = 1;
    }
    else{
        var_flag = 0; // Task: Verify logic in more detail
    }
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
    char res = start_char + inst_counter;
    if(op=='#'){
        struct tac_record trec = {
            res,
            '\0',
            '-',
            arg2
        };
        tac[tac_top++] = trec;
    }
    else{
        char arg1 = var_stack[--var_top];
        struct tac_record trec = {
            res,
            arg1,
            op,
            arg2
        };
        tac[tac_top++] = trec;
    }
    var_stack[var_top++] = res;
    ++inst_counter;
}

void validate_open_bracket(){
    if(var_top < 2){
        fprintf(stderr, "syntax error: open bracket not found\n");
        exit(1);
    }
}

void eval(){
    if(var_stack[var_top-1] == '('){
        return;
    }
    if(var_stack[var_top-1] == ')'){
        var_stack[--var_top];
        validate_open_bracket();
        while(op_stack[var_top-2] != '('){
            execute();
            validate_open_bracket();
        }
        var_stack[var_top-2] = var_stack[var_top-1];
        var_top--;
        return;
    }
    while(op_top >= 2 && precedence(op_top-1) <= precedence(op_top-2)){
        char op = op_stack[--op_top];
        char var = var_stack[--var_top];
        execute();
        op_stack[op_top++] = op;
        var_stack[var_top++] = var;
    }
}

void clean_up(){
    while(op_top > 0){
        execute();
    }
}

void print_tac(){
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