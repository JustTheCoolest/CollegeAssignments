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

Node* convert_to_dag(Node* root){
    iterator it = post_order_iterator(root);
    auto nodes = unordered_set<Node*>();
    while(it.is_not_end()){
        auto match = nodes.find(*it);
        if(match == nodes.end()){
            nodes.insert(*it);
            ++it;
            continue;
        }
        auto& ref_node = it.get_ref();
        delete **it;
        ref_node = *match;
    }
}

int main(){
    "a= (b+-c) * (b+-c) +d";
    node* n1 = new node("b");
    node* n2 = new node("c");
    node* n3 = new node("-", n2);
    node* n4 = new node("+", n1, n3);
    node* n5 = new node("b");
    node* n6 = new node("c");
    node* n7 = new node("-", n6);
    node* n8 = new node("+", n5, n7);
    node* n9 = new node("*", n4, n8);
    node* n10 = new node("d");
    node* n11 = new node("+", n9, n10);
    node* n12 = new node("a");
    node* n13 = new node("=", n12, n11);

    node* n13 = convert_to_dag(n13);
    display(n13);

    
}