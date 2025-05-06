#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Structure to represent a production rule
struct ProductionRule {
    string left;
    string right;
};

class ShiftReduceParser {
private:
    vector<ProductionRule> rules;
    string input;
    string stack;

    // Print current state of parsing
    void printState(int inputPos) {
        cout << stack << "\t";
        // Print remaining input
        for (size_t k = inputPos; k < input.length(); k++) {
            cout << input[k];
        }
        cout << "\t";
    }

public:
    // Initialize parser with production rules
    void initializeRules() {
        int ruleCount;
        cout << "\nEnter the number of production rules: ";
        cin >> ruleCount;
        cin.ignore(); // Clear the newline character

        cout << "\nEnter the production rules (in the form 'left->right'): \n";
        for (int i = 0; i < ruleCount; i++) {
            string temp;
            getline(cin, temp);
            
            // Split the rule into left and right parts
            size_t arrowPos = temp.find("->");
            if (arrowPos != string::npos) {
                ProductionRule rule;
                rule.left = temp.substr(0, arrowPos);
                rule.right = temp.substr(arrowPos + 2);
                rules.push_back(rule);
            }
        }
    }

    // Parse the input string
    bool parse() {
        cout << "\nEnter the input string: ";
        getline(cin, input);

        size_t i = 0;
        stack.clear();

        while (true) {
            // Shift operation
            if (i < input.length()) {
                stack += input[i];
                printState(i + 1);
                cout << "Shift " << input[i] << endl;
                i++;
            }

            // Reduce operation
            bool reduced = false;
            for (const auto& rule : rules) {
                size_t pos = stack.find(rule.right);
                if (pos != string::npos) {
                    // Replace the matched substring with the left-hand side
                    stack.replace(pos, rule.right.length(), rule.left);
                    printState(i);
                    cout << "Reduce " << rule.left << "->" << rule.right << endl;
                    reduced = true;
                    break;
                }
            }

            // Check for acceptance
            if (stack == rules[0].left && i == input.length()) {
                cout << "\nAccepted" << endl;
                return true;
            }

            // Check for rejection
            if (i == input.length() && !reduced) {
                cout << "\nNot Accepted" << endl;
                return false;
            }
        }
    }
};

int main() {
    ShiftReduceParser parser;
    
    // Initialize the parser with production rules
    parser.initializeRules();
    
    // Parse the input string
    parser.parse();

    return 0;
}
