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

    bool is_not_end() const {
        return !stack.empty();
    }

    Node* operator*() const {
        auto gotten_node = stack.top().get();
        cout << "gotten_node: " << gotten_node << endl;
        auto gotten_node2 = stack.top().get();
        cout << "gotten_node2: " << gotten_node2 << endl;
        return gotten_node;
    }
    
    PostOrderIterator& operator++() {
        stack.pop();
        if(stack.empty()){
            return *this;
        }
        while (stack.top().get()->left || stack.top().get()->right) {
            if (stack.top().get()->right) {
                stack.push(std::ref(stack.top().get()->right));
            }
            if (stack.top().get()->left) {
                stack.push(std::ref(stack.top().get()->left));
            }
        }
        return *this;
    }
};

int main(){
    "a= (b+-c) * (b+-c) +d";
    Node* n1 = new Node('b');
    Node* n2 = new Node('c');
    Node* n3 = new Node('-', n2);
    Node* n4 = new Node('+', n1, n3);
    Node* n5 = new Node('b');
    Node* n6 = new Node('c');
    Node* n7 = new Node('-', n6);
    Node* n8 = new Node('+', n5, n7);
    Node* n9 = new Node('*', n4, n8);
    Node* n10 = new Node('d');
    Node* n11 = new Node('+', n9, n10);
    Node* n12 = new Node('a');
    Node* n13 = new Node('=', n12, n11);

    auto it = PostOrderIterator(n13);
    while(it.is_not_end()){
        cout << (*it)->val << " ";
        ++it;
    }
    cout << endl;
}