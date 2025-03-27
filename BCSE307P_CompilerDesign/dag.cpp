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
    cout << "a= (b+-c) * (b+-c) +d" << endl;
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
    n13 = convert_to_dag(n13);
    display(n13);
    cout << endl;
    
    cout << "b = a+d-e *a+b-(c/f)" << endl;
    Node* n21 = new Node('a');
    Node* n22 = new Node('d');
    Node* n23 = new Node('+', n21, n22);
    Node* n24 = new Node('e');
    Node* n25 = new Node('-', n23, n24);
    Node* n26 = new Node('a');
    Node* n27 = new Node('b');
    Node* n28 = new Node('+', n26, n27);
    Node* n29 = new Node('c');
    Node* n30 = new Node('f');
    Node* n31 = new Node('/', n29, n30);
    Node* n32 = new Node('-', n28, n31);
    Node* n33 = new Node('*', n25, n32);
    Node* n34 = new Node('b');
    Node* n35 = new Node('=', n34, n33);
    n35 = convert_to_dag(n35);
    display(n35);
    cout << endl;

    cout << "(n=(m+g)×(h−(i/j))+(k×m)*n" << endl;
    Node* n41 = new Node('m');
    Node* n42 = new Node('g');
    Node* n43 = new Node('+', n41, n42);
    Node* n44 = new Node('h');
    Node* n45 = new Node('i');
    Node* n46 = new Node('j');
    Node* n47 = new Node('/', n45, n46);
    Node* n48 = new Node('-', n44, n47);
    Node* n49 = new Node('*', n43, n48);
    Node* n50 = new Node('k');
    Node* n51 = new Node('m');
    Node* n52 = new Node('*', n50, n51);
    Node* n53 = new Node('n');
    Node* n54 = new Node('+', n49, n52);
    Node* n55 = new Node('n');
    Node* n56 = new Node('=', n53, n54);
    n56 = convert_to_dag(n56);
    display(n56);
    cout << endl;
}