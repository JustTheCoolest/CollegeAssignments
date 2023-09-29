#include "ReallyUseful/Cpp/IOStreamOperations.cpp"
using namespace std;

class Akhilesh{
    public:
    int *a;
    Akhilesh(){
        *a = 5;
        cout << "Regular construcotor is called" << endl;
    }
};

int main(){
    Akhilesh A;
    Akhilesh B = A;
    *B.a = 42;
    cout << *A.a << endl;
}