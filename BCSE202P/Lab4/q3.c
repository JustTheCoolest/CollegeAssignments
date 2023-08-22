#include "twoStacks.c"

int main(){
    init();
    push1(1);
    push1(2);
    push1(3);
    push1(4);
    push2(-1);
    push2(-2);
    display1();
    display2();
    printf("Popped from stack 1: %d\n", pop1());
    display1();
    printf("Popped from stack 2: %d\n", pop2());
    display2();
}