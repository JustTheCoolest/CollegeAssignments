var [a-z]
op [=()+*/-]

%{
char var_stack[100];
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
    else if(op=='='){
        return -100;
    }
    else{
        fprintf(stderr, "operator not recognised: %c", op);
    }
}

int precedence_less_than(int op1_pos, int op2_pos){
    char op1 = op_stack[op1_pos];
    char op2 = op_stack[op2_pos];
    if(op1 == '(' && op2 == ')'){
        return 0;
    }
    if(op1 == '(' && op2 == '('){
        return 0;
    }
    if(op1 == ')' && op2 == ')'){
        return 1;
    }
    if(op1 == ')' && op2 == '('){
        return 0;
    }
    if(op1 == '('){
        return 0;
    }
    if(op2 == '('){
        return 0;
    }
    if(op1 == ')'){
        return 1;
    }
    if(op2 == ')'){
        fprintf(stderr, "unevaluated inner brackets\n");
    }
    return precedence(op1_pos) <= precedence(op2_pos);
}

void print_var_stack(){
    printf("var_stack: ");
    for(int i=0; i<var_top; ++i){
        printf("%c ", var_stack[i]);
    }
    printf("\n");
}

void print_op_stack(){
    printf("op_stack: ");
    for(int i=0; i<op_top; ++i){
        printf("%c ", op_stack[i]);
    }
    printf("\n");
}

void eval(){
    /* 
    options:
    1. precedence as ordered pair function
    2. special if condition for brackets
    */
    while(op_top >= 2 && precedence_less_than(op_top-1, op_top-2)){
        char op = op_stack[--op_top];
        char var = var_stack[--var_top];
        execute();
        op_stack[op_top++] = op;
        var_stack[var_top++] = var;
    }
    if(op_top>0 && op_stack[op_top-1] == ')'){
        op_top -= 2;
    }
    // print_var_stack();
    // print_op_stack();
}

void op_push(char op){
    if(!var_flag){
        if(op == '-'){
            op_stack[op_top++] = '#';
        }
        else if(op == '('){
            op_stack[op_top++] = '(';
        }
        else if(op_top>0 && op_stack[op_top-1] == ')'){
            var_stack[var_top++] = '\0';
            eval();
            var_top--;
            op_stack[op_top++] = op;
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
void clean_up(){
    if(op_top>0 && op_stack[op_top-1] == ')'){
        var_stack[var_top++] = '\0';
        eval();
        var_top--;
    }
    while(op_top > 0){
        eval();
        execute();
    }
}

void print_tac(){
    printf("\n");
    printf("Quadruples\n");
    printf("addr\tres\targ1\top\targ2\n");
    for(int i=0; i<tac_top; ++i){
        struct tac_record trec = tac[i];
        printf("%d\t%c\t%c\t%c\t%c\n", i, trec.res, trec.arg1, trec.op, trec.var);
    }
    printf("\n");
    // Task: Implement Triples more Faithfully
    printf("Triples\n");
    printf("addr\targ1\top\targ2\n");
    for(int i=0; i<tac_top; ++i){
        struct tac_record trec = tac[i];
        // Task: Abstract the operation of converting a character to a number, to reduce redundancy
        char arg1 = trec.arg1 >= 'A' && trec.arg1 <= 'Z' ? trec.arg1 - 'A' + '0' : trec.arg1;
        char arg2 = trec.var >= 'A' && trec.var <= 'Z' ? trec.var - 'A' + '0' : trec.var;
        printf("%d\t%c\t%c\t%c\n", i, arg1, trec.op, arg2);
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
