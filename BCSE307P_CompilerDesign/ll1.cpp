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

// Function to compute FIRST set
map<string, set<string>> computeFirst(const Grammar &grammar) {
    map<string, set<string>> FIRST;

    // Initialize FIRST sets for terminals
    for (const string &terminal : grammar.T) {
        FIRST[terminal].insert(terminal);
    }

    bool changed = true;
    while (changed) {
        changed = false;

        // Iterate over all productions
        for (const auto &[nonTerminal, production] : grammar.P) {
            bool epsilonInPrevious = true;

            for (const string &symbol : production) {
                if (!epsilonInPrevious) break;

                // Add FIRST(symbol) to FIRST(nonTerminal)
                for (const string &terminal : FIRST[symbol]) {
                    if (terminal != "#" && FIRST[nonTerminal].insert(terminal).second) {
                        changed = true;
                    }
                }

                // Check if epsilon is in FIRST(symbol)
                epsilonInPrevious = FIRST[symbol].count("#") > 0;
            }

            // If all symbols in production can derive epsilon, add epsilon to FIRST(nonTerminal)
            if (epsilonInPrevious && FIRST[nonTerminal].insert("#").second) {
                changed = true;
            }
        }
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
    map<string, set<string>> FIRST = computeFirst(grammar);

    // Print FIRST sets
    printFirst(FIRST);

    return 0;
}