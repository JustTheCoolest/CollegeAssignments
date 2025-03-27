#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// struct node{
//     node *left, *right;
// };

// node* convert_to_dag(node* root){
//     unordered_set<node> nodes = unordered_set<node>();
//     // vector<node*> path = vector<node*>();
//     // path.push_back(root);
//     // while(root->left && root->right){

//     // }
//     auto queue = vector<pair<node*, node*>>();
//     queue.push_back({nullptr, root});
//     auto it = queue.begin();
//     while(it != queue.end()){
//         queue.push_back({it->first, it->second->left});
//         queue.push_back({it->first, it->second->right});
//         ++it;
//     }

//     auto rit = queue.rbegin();
//     while(rit != queue.rend()){
//         // if(*(*iterator->second) in nodes){
//         const auto match = nodes.find(it->second);
//         if(match == queue.rend()){
//             nodes.insert(it->second);
//             continue;
//         }
//         delete it->second;
//         it->first
//     }
// }

struct Node{
    Node* left;
    Node* right;
};

// Custom post-order iterator
class PostOrderIterator {
    std::stack<Node*&> stack;
    Node* last_processed = nullptr;

public:
    explicit PostOrderIterator(Node* root) {
        if (root) {
            stack.push(root);
        }
    }

    bool is_not_end() const {
        return !stack.empty();
    }

    Node* operator*() const {
        return stack.top();
    }
    
    PostOrderIterator& operator++() {
        stack.pop();
        if(stack.empty()){
            return *this;
        }
        while(stack.top()->left || stack.top()->right){
            if(stack.top()->right){
                stack.push(stack.top()->right);
            }
            if(stack.top()->left){
                stack.push(stack.top()->left);
            }
        }
        return *this;
    }

    Node*& get_ref() {
        return stack.top();
    }
};

// Function to convert a tree to a DAG
Node* convert_to_dag(Node* root) {
    PostOrderIterator it(root);
    std::unordered_set<Node*> nodes;

    while (it.is_not_end()) {
        auto match = nodes.find(*it);
        if (match == nodes.end()) {
            nodes.insert(*it);
            ++it;
            continue;
        }
        Node*& ref_node = it.get_ref();
        delete *it;
        ref_node = *match;
    }

    return root;
}

int main(){
    "a= (b+-c) * (b+-c) +d";
    Node* n1 = new Node("b");
    Node* n2 = new Node("c");
    Node* n3 = new Node("-", n2);
    Node* n4 = new Node("+", n1, n3);
    Node* n5 = new Node("b");
    Node* n6 = new Node("c");
    Node* n7 = new Node("-", n6);
    Node* n8 = new Node("+", n5, n7);
    Node* n9 = new Node("*", n4, n8);
    Node* n10 = new Node("d");
    Node* n11 = new Node("+", n9, n10);
    Node* n12 = new Node("a");
    Node* n13 = new Node("=", n12, n11);

    Node* n13 = convert_to_dag(n13);
    display(n13);

    
}