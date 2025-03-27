#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Node{
    char val; // Task: Reimplement using string
    Node* left;
    Node* right;
    Node(char v, Node* l = nullptr, Node* r = nullptr): val(v), left(l), right(r){}

    bool operator==(const Node& other) const{
        return val == other.val && left == other.left && right == other.right;
    }
};

namespace std{
    template<>
    struct hash<Node>{
        size_t operator()(const Node n) const{
            return hash<char>{}(n.val) ^ hash<Node*>{}(n.left) ^ hash<Node*>{}(n.right);
        }
    };
};

class PostOrderIterator {
    std::stack<std::reference_wrapper<Node*>> stack;

    void expand(){
        while (stack.top().get()->left || stack.top().get()->right) {
            if (stack.top().get()->right) {
                stack.push(std::ref(stack.top().get()->right));
            }
            if (stack.top().get()->left) {
                stack.push(std::ref(stack.top().get()->left));
            }
        }
    }

public:
    explicit PostOrderIterator(Node* &root) {
        if (root) {
            stack.push(std::ref(root));
            expand();
        }
    }

    bool is_not_end() const {
        return !stack.empty();
    }

    Node* operator*() const {
        auto gotten_node = stack.top().get();
        return gotten_node;
    }
    
    PostOrderIterator& operator++() {
        stack.pop();
        if(stack.empty()){
            return *this;
        }
        expand();
        return *this;
    }

    Node*& get_ref() {
        return stack.top().get();
    }
};

struct HashWrapper {
    size_t operator()(const Node* n) const {
        return hash<Node>{}(*n);
    }
};

struct EqualityWrapper {
    bool operator()(const Node* n1, const Node* n2) const {
        return *n1 == *n2;
    }
};

// Function to convert a tree to a DAG
Node* convert_to_dag(Node* root) {
    PostOrderIterator it(root);
    std::unordered_set<Node*, HashWrapper, EqualityWrapper> nodes;

    while (it.is_not_end()) {
        auto match = nodes.find(*it);
        if (match == nodes.end()) {
            nodes.insert(*it);
            ++it;
            continue;
        }
        Node* ref_node = it.get_ref();
        delete *it;
        ref_node = *match;
        ++it;
    }

    return root;
}

class DAG_LevelOrderIterator{
    queue<Node*> q;

public:
    DAG_LevelOrderIterator(Node* root){
        q = queue<Node*>{};
        q.push(root);
    }

    DAG_LevelOrderIterator& operator++(){
        auto popped = q.front();
        q.pop();
        if(popped->left != nullptr){
            q.push(popped->left);
        }
        if(popped->right != nullptr){
            q.push(popped->right);
        }
        return *this;
    }

    Node* operator*(){
        return q.front();
    }

    bool is_not_end(){
        return !q.empty();
    }
};

void display(Node* root){
    auto it = DAG_LevelOrderIterator(root);
    while(it.is_not_end()){
        std::cout << (*it)->val << " " << *it << " -> ";
        
        if ((*it)->left) {
            std::cout << (*it)->left->val << " " << (*it)->left;
        } else {
            std::cout << "null";
        }
        
        std::cout << " , ";
        
        if ((*it)->right) {
            std::cout << (*it)->right->val << " " << (*it)->right;
        } else {
            std::cout << "null";
        }
        
        std::cout << "\n";
        ++it;
    }
}

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

    cout << (hash<Node>{}(*n1) == hash<Node>{}(*n5)) << endl;
    cout << (hash<Node>{}(*n1) == hash<Node>{}(*n10)) << endl;
    cout << (*n1 == *n5) << endl;
    cout << (*n1 == *n10) << endl;

    auto it = PostOrderIterator(n13);
    while(it.is_not_end()){
        cout << (*it)->val << " ";
        ++it;
    }
    cout << endl;

    // n13 = convert_to_dag(n13);
    // display(n13);
    
}