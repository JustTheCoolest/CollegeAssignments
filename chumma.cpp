#include <iostream>
using namespace std;

void mainX(int argc, char** argv){
    int b;
    cin >> b;
    b = b + 5;
    static int a = b;
    cout << a << endl;
}

int main(int argc, char** argv){
    mainX(argc, argv);
}