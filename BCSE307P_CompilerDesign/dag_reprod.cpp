#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Node{
    char val; // Task: Reimplement using string
    Node* left;
    Node* right;
    Node(char v, Node* l = nullptr, Node* r = nullptr): val(v), left(l), right(r){}
};

class PostOrderIterator {
    std::stack<std::reference_wrapper<Node*>> stack;

public:
    explicit PostOrderIterator(Node* root) {
        if (root) {
            stack.push(std::ref(root));
        }
    }

    Node* func() {
        auto gotten_node = stack.top().get();
        cout << "gotten_node: " << gotten_node << endl;
        auto gotten_node2 = stack.top().get();
        cout << "gotten_node2: " << gotten_node2 << endl;
        return gotten_node;
    }
};

int main(){
    Node* n9 = new Node('*');
    Node* n10 = new Node('d');
    Node* n11 = new Node('+', n9, n10);
    Node* n12 = new Node('a');
    Node* n13 = new Node('=', n12, n11);

    std::stack<std::reference_wrapper<Node*>> stack;
    stack.push(std::ref(n13));
    stack.top().get();

    auto it = PostOrderIterator(n13);
    cout << (it.func())->val << " ";
    cout << endl;
}