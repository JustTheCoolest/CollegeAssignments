#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Node{
    char val; // Task: Reimplement using string
    Node* left;
    Node(char v, Node* l = nullptr): val(v), left(l){}
};

class PostOrderIterator {
    std::stack<std::reference_wrapper<Node*>> stack;

public:
    PostOrderIterator(Node* &root) {
        stack.push(std::ref(root));
    }

    Node* func() {
        auto gotten_node = stack.top().get();
        return gotten_node;
    }
};

int main(){
    Node* n12 = new Node('a');
    Node* n13 = new Node('=', n12);

    auto it = PostOrderIterator(n13);
    cout << (it.func())->val << " ";
    cout << endl;
}