#include<bits/stdc++.h>
using namespace std;

constexpr array<const char, 5> elements {'c', 'd', '$', 'S', 'C'};
constexpr array<const int, 3> terminals {0, 1, 2};
constexpr array<const int, 2> non_terminals {3, 4};
constexpr array<const int, 3> heads {3, 4, 4};
constexpr array<const int, 3> sizes {2, 2, 1};

bool error_flag = false;

constexpr array<array<char, 5>, 8> action_table = { 
    {
        {'s', 's', 'e', 't', 't'}, 
        {'e', 'e', 'a', 'e', 'e'}, 
        {'s', 's', 'e', 'e', 't'}, 
        {'s', 's', 'e', 'e', 't'}, 
        {'r', 'r', 'r', 'e', 'e'}, 
        {'e', 'e', 'r', 'e', 'e'}, 
        {'r', 'r', 'r', 'e', 'e'},
        {'e', 'e', 'e', 'e', 'e'}
    }
}; 

constexpr array<array<int, 5>, 7> transition_table = { 
    {
        {3, 4, -1, 1, 2}, 
        {-1, -1, -1, -1, -1}, 
        {3, 4, -1, -1, 5}, 
        {3, 3, 3, -1, -1}, 
        {-1, -1, 1, -1, -1}, 
        {2, 2, 2, -1, -1},
        {-1, -1, -1, -1, -1}
    }
};

stack<int> state_stack {};
stack<char> symbol_stack {};

void handle(char input){
    if(error_flag){
        return;
    }
    int inp_index = find(elements.begin(), elements.end(), input) - elements.begin();
    int state = state_stack.top();
    int action = action_table[state][inp_index];
    switch(action){
        // Caution: If there exists something like a theoretical possibility of a shift-goto conflict, this code does not handle it
        case 's':{
            symbol_stack.push(input);
            state_stack.push(transition_table[state][inp_index]);
            break;
        }
        case 't':{
            symbol_stack.push(input);
            state_stack.push(transition_table[state][inp_index]);
            break;
        }
        case 'r':{
            int rule = transition_table[state][inp_index];
            char head = elements[heads[rule]];
            int size = sizes[rule];
            if(state_stack.size() < size || symbol_stack.size() < size){
                fprintf(stderr, "RuntimeError: Reduce operation trying to remove more than available in the stacks");
                error_flag = 1;
            }
            while(size--){
                state_stack.pop();
                symbol_stack.pop();
            }
            handle(input);
            break;
        }
        case 'e':{
            error_flag = 1;
            break;
        }
        default:{
            fprintf(stderr, "RuntimeError: No such action exists! : %c", action);
            error_flag = 1;
        }
    }
}

bool find_acceptance(){
    return (state_stack.top() == transition_table.size()-1) && !error_flag;
}

int main(){
    string input;
    cout << "Enter the input string: ";
    cin >> input;
    input += '$';
    state_stack.push(0);
    for(int i = 0; i < input.size(); i++){
        handle(input[i]);
        assert(state_stack.size() == symbol_stack.size()+1);
    }
    bool acceptance = find_acceptance();
    printf(acceptance ? "Accepted\n" : "Not accepted\n");
}