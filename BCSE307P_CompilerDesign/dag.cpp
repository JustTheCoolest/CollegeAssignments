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
    std::stack<std::pair<std::reference_wrapper<Node*>, bool>> stack;

    void expand() {
        while (!stack.top().second) {
            auto [node_ref, visited] = stack.top();
            stack.pop();
            stack.push({node_ref, true}); // Mark the current node as visited

            Node* node = node_ref.get();
            // Push right and left children onto the stack (if they exist)
            if (node->right) {
                stack.push({std::ref(node->right), false});
            }
            if (node->left) {
                stack.push({std::ref(node->left), false});
            }
        }
    }

public:
    explicit PostOrderIterator(Node* &root) {
        if (root) {
            stack.push({std::ref(root), false}); // Push the root node with visited = false
            expand();
        }
    }

    bool is_not_end() const {
        return !stack.empty();
    }

    Node* operator*() const {
        return stack.top().first.get(); // Return the current node
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
        return stack.top().first; // Return a reference to the current node
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
        delete *it;
        it.get_ref() = *match;
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

    // cout << (hash<Node>{}(*n1) == hash<Node>{}(*n5)) << endl;
    // cout << (hash<Node>{}(*n1) == hash<Node>{}(*n10)) << endl;
    // cout << (*n1 == *n5) << endl;
    // cout << (*n1 == *n10) << endl;

    // auto it = PostOrderIterator(n13);
    // while(it.is_not_end()){
    //     cout << (*it)->val << " ";
    //     ++it;
    // }
    // cout << endl;

    n13 = convert_to_dag(n13);
    display(n13);
    
}