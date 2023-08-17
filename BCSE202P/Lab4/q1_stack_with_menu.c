#include <stdlib.h>
#include "stack.c"

int main(){
    int n;
    printf("Size of stack to create: ");
    scanf("%d", &n);
    int stack[n];
    int top = 0;
    int choice = -1;
    while(choice != 0){
        printf("0. Exit\n1. Pop\n2.Push\n3. Peek\n 4.Display\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:
            printf("Element to push: ");
            int element;
            scanf("%d", &element);
            push(n, stack, &top, element);
            break;
            case 2:
            printf("Element popped: %d\n", pop(n, stack, &top, element));
            break;
            case 3:
            printf("Top element: %d", peek(n, stack, &top, element));
            break;
            case 4:
            display(n, stack, &top);
        }
        printf("Program ended\n");
    }
}