#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

int stack[100], top=-1;

void push(int element, int stack[], int top){
    stack[++top] = element;
}

int pop(int stack[], int top){
    return stack[top--];
}

int peek(int const stack[], int const top){
    return stack[top];
}

int getRank(char op){
    static char ops[] = {'(', '^', '/', '*', '-', '+', ')'};
    for(int i=0; i<7; ++i){
        if(ops[i]==op){
            return i;
        }
    }
}

// int stacks are compatible with chars too

int main(){
    char *in;
    size_t n=0;
    getline(&in, &n, stdin);
    printf("%s", in);
    char *traverser = in;
    while(*traverser != '\0' && *traverser != '\n'){
        if(isdigit(*traverser)){
            printf("%c", *traverser);
        }
        else{
            // Entering one is higher : Retain
            int traverser_priority = getRank(*traverser);
            while(traverser_priority <= getRank(peek(stack, top))){
                printf("%c", pop(stack, top));
            }
            if(traverser_priority==6){
                pop(stack, top);
            }
            else{
                push(*traverser, stack, top);
            }
        }
        ++traverser;
    }
}