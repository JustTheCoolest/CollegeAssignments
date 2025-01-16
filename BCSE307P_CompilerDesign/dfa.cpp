#include <iostream>
#include <string>
using namespace std;

void solve(string s){
    cout << s << " ";
    int state = 0;
    for(char c: s){
        if(state == 0){
            if(c=='y'){
                state = 1;
            }
            else{
                state = 0;
            }
        }
        else if(state == 1 || state == 2){
            if(c=='y'){
                state = 2;
            }
            else{
                state = 0;
            }
        }
    }
    cout << (state == 2 ? "true" : "false");
    cout << endl;
}

int main(){
    solve("yyyy");
    solve("xxyy");
    solve("xxyyxy");
    solve("xyyy");
    solve("yyxx");
    solve("xyxyyy");
}