#include <bits/stdc++.h>
using namespace std;

struct Node{
    char val;
    Node* child;
};

int main(){
    auto stk = stack<reference_wrapper<Node*>>{};
    auto *a = new Node{'a', nullptr};
    stk.push(ref(a));
    cout << (Node*)stk.top().get() << endl;
    cout << (Node*)stk.top().get() << endl;
}