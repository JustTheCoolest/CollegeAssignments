%{
#include<vector> 
#include<string> 
#include<iostream> 
using namespace std; 
 
constexpr vector<char> elements = {'c', 'd', '$', 'S', 'C'}; 
constexpr vector<int> terminals = {0, 1, 2}; 
constexpr vector<int> non_terminals = {3, 4}; 
constexpr vector<int> heads = {3, 4, 4}; 
constexpr vector<int> sizes = {2, 2, 1};

constexpr vector<vector<char>> action_table = { 
    {'s', 's', 'e', 't', 't'}, 
    {'e', 'e', 'a', 'e', 'e'}, 
    {'s', 's', 'e', 'e', 't'}, 
    {'s', 's', 'e', 'e', 't'}, 
    {'r', 'r', 'r', 'e', 'e'}, 
    {'e', 'e', 'r', 'e', 'e'}, 
    {'r', 'r', 'r', 'e', 'e'},
    {'e', 'e', 'e', 'e', 'e'}
}; 

constexpr vector<vector<int>> transition_table = { 
    {3, 4, -1, 1, 2}, 
    {-1, -1, -1, -1, -1}, 
    {3, 4, -1, -1, 5}, 
    {3, 3, 3, -1, -1}, 
    {-1, -1, 1, -1, -1}, 
    {2, 2, 2, -1, -1},
    {-1, -1, -1, -1, -1}
}; 

stack<int> state_stack {0};
stack<char> symbol_stack {};

void handle(char input){
    int inp_index = elements.
}

%}

%%
[ ] {}
[cd] {handle(yytext[0]);} 
'\n' {state_stack.top() != action_table.size() - 1 ? printf("Not accepted\n") : printf("Accepted\n");}
. {printf("Invalid character: %s\n", yytext);}
%%

int main(){
    yylex();
    return 0;
}
