#include <iostream>
#include <unordered_set>
#include <set>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Grammar {
    unordered_set<string> N;
    unordered_set<string> T;
    set<pair<string, vector<string>>> P;
    string S;
};

set<string> findFirst(const string &symbol, const map<string, set<vector<string>>> &productions, map<string, set<string>> &FIRST) {
    if(symbol == "#"){
        return {"#"}; // Task: Add validation to ensure that N -> t# does not get counted as an epsilon production (non standard grammar notation)
    }

    if(FIRST.find(symbol) != FIRST.end()){
        return FIRST.at(symbol);
    }

    set<vector<string>> delayed_productions {}; // Task: Implement as pointers or references

    set<string> firstSet;

    auto _process_body = [&](const string &symbol, const vector<string> &body, bool break_flag) {
        bool broken_flag = false;
        for (const auto &body_symbol : body) {
            if (body_symbol == symbol) {
                if (!break_flag) {
                    continue;
                }
                delayed_productions.insert(body);
                break;
            }
            set<string> body_first = findFirst(body_symbol, productions, FIRST);
            firstSet.insert(body_first.begin(), body_first.end());
            if (body_first.find("#") == body_first.end()) {
                broken_flag = true;
                break;
            }
        }
        if (!broken_flag) {
            firstSet.insert("#");
        }
    };

    for (const auto &body : productions.at(symbol)) {
        _process_body(symbol, body, true);
    }

    if (firstSet.find("#") == firstSet.end()) {
        FIRST[symbol] = firstSet;
        return firstSet;
    }

    for (const auto &body : delayed_productions) {
        _process_body(symbol, body, false);
    }

    FIRST[symbol] = firstSet;
    return firstSet;
}

map<string, set<string>> computeFirsts(const Grammar &grammar) {
    map<string, set<string>> FIRST;

    for (const string &terminal : grammar.T) {
        FIRST[terminal].insert(terminal);
    }

    map<string, set<vector<string>>> productions;
    for (const auto &[head, body] : grammar.P) {
        productions[head].insert(body);
    }

    for(const auto &[head, bodies] : productions){
        FIRST[head] = findFirst(head, productions, FIRST);
    }

    return FIRST;
}

void printFirst(const map<string, set<string>> &FIRST) {
    for (const auto &[symbol, firstSet] : FIRST) {
        cout << "FIRST(" << symbol << ") = { ";
        for (const string &terminal : firstSet) {
            cout << terminal << " ";
        }
        cout << "}" << endl;
    }
}

int main() {
    Grammar grammar;
    grammar.N = {"E", "E'", "T", "T'", "F"};
    grammar.T = {"+", "*", "(", ")", "id", "#"};
    grammar.S = "E";
    grammar.P = {
        {"E", {"T", "E'"}},
        {"E'", {"+", "T", "E'"}},
        {"E'", {"#"}},
        {"T", {"F", "T'"}},
        {"T'", {"*", "F", "T'"}},
        {"T'", {"#"}},
        {"F", {"(", "E", ")"}},
        {"F", {"id"}}
    };

    map<string, set<string>> FIRST = computeFirsts(grammar);

    printFirst(FIRST);

    return 0;
}