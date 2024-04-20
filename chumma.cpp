#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
   int data;
   struct Node *left;
   struct Node *right;
} Node;

Node* getNode(int data){
   Node* newNode = (Node*)malloc(sizeof(Node));
   newNode->data = data;
   newNode->left = NULL;
   newNode->right = NULL;
   return newNode;
}

Node* insertTree(Node *dataNode, Node *tree){
   Node *traverser = tree;
   if(traverser == NULL){
      return dataNode;
   }
   if(dataNode->data < traverser->data){
      traverser->left = insertTree(dataNode, traverser->left);
   }
   else{
      traverser->right = insertTree(dataNode, traverser->right);
   }
   return traverser;
}
   

// Better for exam as it uses the insert function itself
Node* createTree(int n){
   Node *tree = NULL; // Important to define as NULL
   for(int i=0;i<n;++i){
      int data;
      scanf("%d",&data);
      Node* dataNode = getNode(data);
      tree = insertTree(dataNode, tree);
   }
   return tree;
}

void printTree(Node *tree){
   if(tree == NULL) return;
   Node *traverser = tree;
   printTree(traverser->left);
   printf("%d ",traverser->data);
   printTree(traverser->right);
}

int main(){
   int n;
   scanf("%d",&n);
   Node *tree = createTree(n);
   printTree(tree);
}