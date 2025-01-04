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

void solve(string s){
    Solution sol;
    cout << s << " " << (sol.isMatch(s, "a.*bb") ? "true" : "false") << endl;
}

int main(){
    solve("abababbababb");
    solve("ababbababbabba");
}