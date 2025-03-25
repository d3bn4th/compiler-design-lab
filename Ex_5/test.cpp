#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

class FirstFollowCalculator {
private:
    map<string, vector<string>> productions;  // Stores productions for each non-terminal
    map<string, set<string>> firstSets;
    map<string, set<string>> followSets;
    string startSymbol;

    // Helper function to check if a symbol is non-terminal
    bool isNonTerminal(const string& symbol) {
        return isupper(symbol[0]);  // Assuming non-terminals are uppercase
    }

    // Helper function to split production right-hand side
    vector<string> splitRHS(const string& rhs) {
        vector<string> result;
        stringstream ss(rhs);
        string symbol;
        while (ss >> symbol) {
            result.push_back(symbol);
        }
        return result;
    }

public:
    // Add a production to the grammar
    void addProduction(const string& lhs, const string& rhs) {
        if (productions.empty()) {
            startSymbol = lhs;  // First production's LHS is start symbol
        }
        productions[lhs].push_back(rhs);
    }

    // Calculate FIRST set for a symbol or string of symbols
    set<string> calculateFirst(const string& symbol) {
        // If FIRST set already calculated, return it
        if (firstSets.count(symbol) > 0) {
            return firstSets[symbol];
        }

        set<string> first;

        // If symbol is terminal or epsilon
        if (!isNonTerminal(symbol) || symbol == "e") {
            first.insert(symbol);
            return first;
        }

        // For non-terminals
        for (const string& rhs : productions[symbol]) {
            vector<string> symbols = splitRHS(rhs);
            
            if (symbols[0] == "e") {  // If production is X → ε
                first.insert("e");
            } else {
                // For each symbol in RHS
                for (const string& sym : symbols) {
                    set<string> symbolFirst = calculateFirst(sym);
                    first.insert(symbolFirst.begin(), symbolFirst.end());
                    
                    // If symbol cannot derive epsilon, break
                    if (symbolFirst.find("e") == symbolFirst.end()) {
                        break;
                    }
                }
            }
        }

        firstSets[symbol] = first;
        return first;
    }

    // Calculate FOLLOW sets for all non-terminals
    void calculateFollow() {
        // Add $ to FOLLOW(S) where S is start symbol
        followSets[startSymbol].insert("$");

        // Repeat until no changes are made
        bool changed;
        do {
            changed = false;
            
            // For each production
            for (const auto& production : productions) {
                string lhs = production.first;
                
                // For each RHS alternative
                for (const string& rhs : production.second) {
                    vector<string> symbols = splitRHS(rhs);
                    
                    // For each symbol in RHS
                    for (size_t i = 0; i < symbols.size(); i++) {
                        if (isNonTerminal(symbols[i])) {
                            set<string> toAdd;
                            
                            // If it's not the last symbol
                            if (i < symbols.size() - 1) {
                                set<string> firstNext = calculateFirst(symbols[i + 1]);
                                toAdd.insert(firstNext.begin(), firstNext.end());
                                toAdd.erase("e");  // Remove epsilon
                            }
                            
                            // If it's the last symbol or next can derive epsilon
                            if (i == symbols.size() - 1 || 
                                calculateFirst(symbols[i + 1]).find("e") != calculateFirst(symbols[i + 1]).end()) {
                                set<string>& lhsFollow = followSets[lhs];
                                toAdd.insert(lhsFollow.begin(), lhsFollow.end());
                            }
                            
                            // Add calculated symbols to FOLLOW set
                            set<string>& currentFollow = followSets[symbols[i]];
                            size_t previousSize = currentFollow.size();
                            currentFollow.insert(toAdd.begin(), toAdd.end());
                            
                            if (currentFollow.size() != previousSize) {
                                changed = true;
                            }
                        }
                    }
                }
            }
        } while (changed);
    }

    // Print FIRST and FOLLOW sets
    void printSets() {
        // Print FIRST sets
        cout << "\nFIRST Sets:" << endl;
        for (const auto& entry : productions) {
            string nonTerminal = entry.first;
            set<string> first = calculateFirst(nonTerminal);
            cout << "FIRST(" << nonTerminal << ") = { ";
            for (const string& symbol : first) {
                cout << symbol << " ";
            }
            cout << "}" << endl;
        }

        // Print FOLLOW sets
        cout << "\nFOLLOW Sets:" << endl;
        for (const auto& entry : followSets) {
            cout << "FOLLOW(" << entry.first << ") = { ";
            for (const string& symbol : entry.second) {
                cout << symbol << " ";
            }
            cout << "}" << endl;
        }
    }
};

int main() {
    FirstFollowCalculator calculator;
    string input;
    
    cout << "Enter productions (one per line, 'done' to finish)" << endl;
    cout << "Format: A B C D (space-separated, use 'e' for epsilon)" << endl;
    cout << "Example: E T E'" << endl;
    
    string lhs;
    string rhs;
    
    while (true) {
        cout << "Enter non-terminal (or 'done'): ";
        getline(cin, lhs);
        if (lhs == "done") break;
        
        cout << "Enter production (space-separated): ";
        getline(cin, rhs);
        
        calculator.addProduction(lhs, rhs);
    }

    // Calculate FOLLOW sets (this will also calculate FIRST sets)
    calculator.calculateFollow();
    
    // Print results
    calculator.printSets();

    return 0;
}