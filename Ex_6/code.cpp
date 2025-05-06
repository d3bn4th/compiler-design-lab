#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct ProductionRule { 
    string left;
    string right;
};

class ShiftReduceParser {
private:
    vector<ProductionRule> rules;
    string stack;
    string input;

    void printState(int inputPos) {
        cout << stack << "\t";
        for(size_t k = inputPos; k < input.size(); k++) {
            cout << input[k];
        } 
        cout << "\t";
    }

public:
    // Intialize parser with production rules
    void initializeRules() {
        int ruleCount;
        cout << "\nEnter the number of Production Rules: ";
        cin >> ruleCount;
        cin.ignore();

        cout << "\n Enter the Production Rules : \n";
        for(int i = 0; i < ruleCount; i++) {
            string temp;
            getline(cin ,temp);

            // Split the rules into left and right
            size_t arrowPos = temp.find("->");
            if(arrowPos != string::npos){
                ProductionRule rule;
                rule.left = temp.substr(0, arrowPos);
                rule.right = temp.substr(arrowPos + 2);
                rules.push_back(rule);
            }
        } 
    }

    bool parse() {
        cout << "\nEnter input stirng : ";
        getline(cin, input);

        size_t i = 0;
        stack.clear();

        while(true) {
            // Shift Operation
            if(i < input.length()){
                stack += input[i];
                printState(i + 1);
                cout << "Shift " << input[i] << endl;
                i++; 
            }

            // Reduce Operation
            bool reduced = false;
            for(auto& rule : rules) {
                size_t pos = stack.find(rule.right);
                if(pos != string::npos) {
                    stack.replace(pos,rule.right.length(), rule.left);
                    printState(i);
                    cout << "Reduce " << rule.left << "->" << rule.right << endl;
                    reduced = true;
                    break;
                }
            }

            // Check for Acceptance
            if(stack == rules[0].left && i == input.length()) {
                cout << "\nAccepted" << endl;
                return true;
            }

            // Check for Rejection
            if(i == input.length() && !reduced){
                cout << "\nNot Accepted" << endl;
                return false;
            }
        }
    }
};

int main() {
    ShiftReduceParser parser;
    parser.initializeRules();
    parser.parse();
    return 0;
}
