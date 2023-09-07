#include <iostream>
using namespace std;

template <class ElementType>
class Node{
    public:
    ElementType data;
    Node<ElementType>* next;
    Node(ElementType data): data(data){};
};

template <class ElementType>
class LinkedCircle{
    Node<ElementType>* head = nullptr;
    Node<ElementType>* previous = nullptr;
    public:
    void addInFront(ElementType element){
        Node<ElementType>* newNode = new Node(element);
        if(head==nullptr){
            head = newNode;
            newNode->next = newNode;
        }
        else if(previous==nullptr){
            newNode->next = head;
            head->next = newNode;
            head = newNode;
        }
        else{
            newNode->next = head->next;
            head->next = newNode;
        }
    }
    ElementType current(){
        if(previous==nullptr){
            return NULL;
        }
        return head->data;
    }
    bool removeCurrentAndStep(){
        if(head==nullptr){
            return false;
        }
        if(head==previous){
            free(head);
            head = NULL;
            previous = NULL;
            return true;
        }
        previous->next = head->next;
        free(head);
        head = previous->next;
        return true;
    }
    ElementType stepNext(){
        if(head==nullptr){
            return NULL;
        }
        previous = head;
        head=head->next;
        return head->data;
    }
    void display(){
        if(head==nullptr){
            cout << "Empty" << endl;
            return;
        }
        Node<ElementType>* current = head;
        do{
            cout << current->data->id << " ";
            current = current->next;
        }while(current!=head);
        cout << endl;
    }
};

// void test(){
//     LinkedCircle<int> haey;
//     haey.display();
//     haey.addInFront(5);
//     haey.addInFront(7);
//     haey.display();
//     haey.stepNext();
//     haey.display();
//     haey.addInFront(8);
//     haey.display();
//     haey.removeCurrent();
//     haey.display();
//     haey.stepNext();
//     haey.removeCurrent();
//     haey.display();
// }