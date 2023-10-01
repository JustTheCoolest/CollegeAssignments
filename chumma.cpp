#include <iostream>
using namespace std;

void func2(auto f){
    int a = 20, b = 90;
    f();
}

int main(){
    int a=5, b=7;
    auto func = [=, &a](){cout << a << " " << b << endl;};
    a = 10;
    b = 42;
    func2(func);
}