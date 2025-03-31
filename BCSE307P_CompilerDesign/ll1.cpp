#include <iostream>
#include <unordered_set>
#include <set>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Grammar structure
struct Grammar {
    unordered_set<string> N; // Non-terminals (HashSet equivalent)
    unordered_set<string> T; // Terminals
    set<pair<string, vector<string>>> P; // Productions
    string S; // Start symbol
};

// Function to compute FIRST set for a given symbol
set<string> findFirst(const string &symbol, const map<string, set<vector<string>>> &productions, const map<string, set<string>> &FIRST) {
    if(FIRST.find(symbol) != FIRST.end()){
        return FIRST.at(symbol);
    }

    set<vector<string>> delayed_productions {}; // Task: Implement as pointers or references

    set<string> firstSet;
    
    lambda void _process_body(string symbol, vector<string> &body, set<vector<string>> &delayed_productions, const map<string, set<vector<string>>> &productions, const map<string, set<string>> &FIRST, set<string> &firstSet, bool break_flag){
        for(const auto &body_symbol : body){
            if(body_symbol == symbol){
                if(!break_flag){
                    continue;
                }
                delayed_productions.insert(body);
                break;
            }
            set<string> body_first = findFirst(body_symbol, productions, FIRST);
            firstSet.insert(body_first.begin(), body_first.end());
            if(body_first.find("#") == body_first.end()){
                break;
            }
        }
        else{
            firstSet.insert("#");
        }
    }

    for(const auto &body : productions.at(symbol)){
        _process_body(symbol, body, true);
    }

    if(firstSet.find("#") == firstSet.end()){
        return firstSet;
    }

    for(const auto &body : productions.at(symbol)){
        _process_body(symbol, body, false);
    }

    return firstSet;
}

// Function to compute FIRST set
map<string, set<string>> computeFirsts(const Grammar &grammar) {
    map<string, set<string>> FIRST;

    // Initialize FIRST sets for terminals
    for (const string &terminal : grammar.T) {
        FIRST[terminal].insert(terminal);
    }

    // Use std::map instead of HashMap
    map<string, set<vector<string>>> productions;
    for (const auto &[head, body] : grammar.P) {
        productions[head].insert(body);
    }

    for(const auto &[head, bodies] : productions){
        FIRST[head] = findFirst(head, productions, FIRST);
    }

    return FIRST;
}

// Helper function to print FIRST sets
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
    // Define the grammar
    Grammar grammar;
    grammar.N = {"E", "E'", "T", "T'", "F"};
    grammar.T = {"+", "*", "(", ")", "i", "d", "#"}; // '#' represents epsilon
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

    // Compute FIRST sets
    map<string, set<string>> FIRST = computeFirsts(grammar);

    // Print FIRST sets
    printFirst(FIRST);

    return 0;
}