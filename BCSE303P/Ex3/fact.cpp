#include <cmath>
#include <iostream>
using namespace std;
int main(){
    int n=10;
    int prod=1;
    for(int i=1; i<=n; prod*=i, ++i){}
    cout << "Factorial: " << prod << endl;
}