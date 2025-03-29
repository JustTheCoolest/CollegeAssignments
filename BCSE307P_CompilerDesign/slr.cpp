#include<bits/stdc++.h>
using namespace std;

/*
E-> E+T / T
T -> T*F / F
F -> (E) / id
*/

constexpr array<const char, 9> elements {'+', '*', '(', ')', 'i', '$', 'E', 'T', 'F'};
constexpr auto terminals = std::array {0, 1, 2, 3, 4, 5};
constexpr auto non_terminals = std::array {6, 7, 8};
constexpr auto heads = std::array {6, 6, 7, 7, 8, 8};
constexpr auto sizes = std::array {3, 1, 3, 1, 3, 1};

bool error_flag = false;
bool acceptance_flag = false;

/*
e, e, s4, e, s5, e, t1, t2, t3
s5, e, e, e, e, a, e, e, e
r2, s6, e, r2, e, r2, e, e, e
r4, r4, e, r4, e, r4, e, e, e
e, e, s4, e, s5, e, t8, t2, t3
r6, r6, s4, r6, s5, r6, e, t9, t3
e, e, s4, e, s5, e, e, e, t10
s6, e, e, s11, e, e, e, e, e
r1, e, e, r1, e, r1, e, e, e
r3, r3, e, r3, e, r3, e, e, e
r5, r5, e, r5, e, r5, e, e, e
*/

constexpr auto action_table = std::array{
    std::array{'e', 'e', 's', 'e', 's', 'e', 't', 't', 't'},
    std::array{'s', 'e', 'e', 'e', 'e', 'a', 'e', 'e', 'e'},
    std::array{'r', 's', 'e', 'r', 'e', 'r', 'e', 'e', 'e'},
    std::array{'r', 'r', 'e', 'r', 'e', 'r', 'e', 'e', 'e'},
    std::array{'e', 'e', 's', 'e', 's', 'e', 't', 't', 't'},
    std::array{'r', 'r', 's', 'r', 's', 'r', 'e', 't', 't'},
    std::array{'e', 'e', 's', 'e', 's', 'e', 'e', 'e', 't'},
    std::array{'s', 'e', 'e', 's', 'e', 'e', 'e', 'e', 'e'},
    std::array{'r', 'e', 'e', 'r', 'e', 'r', 'e', 'e', 'e'},
    std::array{'r', 'r', 'e', 'r', 'e', 'r', 'e', 'e', 'e'},
    std::array{'r', 'r', 'e', 'r', 'e', 'r', 'e', 'e', 'e'}
};

constexpr auto transition_table = std::array{
    std::array{-1, -1, 4, -1, 5, -1, 1, 2, 3},
    std::array{5, -1, -1, -1, -1, -1, -1, -1, -1},
    std::array{2, 6, -1, 2, -1, 2, -1, -1, -1},
    std::array{4, 4, -1, 4, -1, 4, -1, -1, -1},
    std::array{-1, -1, 4, -1, 5, -1, 8, 2, 3},
    std::array{6, 6, 4, 6, 5, 6, -1, 9, 3},
    std::array{-1, -1, 4, -1, 5, -1, -1, -1, 10},
    std::array{6, -1, -1, 11, -1, -1, -1, -1, -1},
    std::array{1, -1, -1, 1, -1, 1, -1, -1, -1},
    std::array{3, 3, -1, 3, -1, 3, -1, -1, -1},
    std::array{5, 5, -1, 5, -1, 5, -1, -1, -1}
};

stack<int> state_stack {};
stack<char> symbol_stack {};

void handle(char input){
    if(acceptance_flag){
        acceptance_flag = false;
        error_flag = true;
        return;
    }
    if(error_flag){
        return;
    }
    int inp_index = find(elements.begin(), elements.end(), input) - elements.begin();
    int state = state_stack.top();
    char action = action_table[state][inp_index];
    cout << "State: " << state << " Input: " << input << " Action: " << action << endl;
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
        case 'a':{
            acceptance_flag = true;
            break;
        }
        default:{
            fprintf(stderr, "RuntimeError: No such action exists! : %c", action);
            error_flag = 1;
        }
    }
}

bool find_acceptance(){
    // return (state_stack.top() == transition_table.size()-1) && !error_flag;
    return acceptance_flag;
}

template<typename T>
void print_stack(stack<T> s){
    stack<T> temp = s;
    vector<T> v;
    while(!temp.empty()){
        v.push_back(temp.top());
        temp.pop();
    }
    reverse(v.begin(), v.end());
    for(auto i : v){
        cout << i << " ";
    }
    cout << endl;
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
        print_stack(state_stack);
        print_stack(symbol_stack);
    }
    bool acceptance = find_acceptance();
    printf(acceptance ? "Accepted\n" : "Not accepted\n");
}