#include <string>
#include <iostream>
using namespace std;

// Flag: Solutions with better time complexities seem to exist
// https://leetcode.com/problems/regular-expression-matching/submissions/1494934195/

class Solution {
public:
    bool isMatchChar(char s, char p){
        return s == p || p == '.';
    }
    bool isMatch(string s, string p) {
        // cout << s << " " << p << endl;
        if(p.empty()){
            return s.empty();
        }
        if(p.length()>1 && p[1]=='*'){
            for(int i=0; i<=s.length(); ++i){
                if(isMatch(s.substr(i), p.substr(2))){
                    return true;
                }
                if(!isMatchChar(s[i], p[0])){
                    return false;
                }
            }
        }
        if(s.empty()){
            return false;
        }
        if(!isMatchChar(s[0], p[0])){
            return false;
        }
        return isMatch(s.substr(1), p.substr(1));
    }
};

void solve(string s, string p){
    Solution sol;
    cout << s << " " << (sol.isMatch(s, p) ? "true" : "false") << endl;
}

void solveNeither(string s, string p1, string p2){
    Solution sol;
    cout << s << " " << (sol.isMatch(s, p1) || sol.isMatch(s, p2) ? "false" : "true") << endl;
}

int main(){
    cout << "Q1:" << endl;
    solve("xyxx", "x.*yy");
    solve("xyxyyy", "x.*yy");

    cout << endl;

    cout << "Q2:" << endl;
    // Flag: "y?(xy)*x?", but groups are not implemented in my code
    string p1 = ".*xx.*";
    string p2 = ".*yy.*";
    solveNeither("xyxx", p1, p2);
    solveNeither("xyxyyy", p1, p2);
    solveNeither("xyxyx", p1, p2);
    solveNeither("y", p1, p2);
}