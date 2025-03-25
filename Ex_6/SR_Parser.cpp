#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct ProductionRule {
    std::string left;
    std::string right;
};

class ShiftReduceParser {
private:
    std::vector<ProductionRule> rules;
    std::string stack;
    std::string input;

public:
    void addRule(const std::string& left, const std::string& right) {
        rules.push_back({left, right});
    }

    void setInput(const std::string& str) {
        input = str;
    }

    void parse() {
        stack = "";
        size_t i = 0;

        while (true) {
            if (i < input.length()) {
                stack += input[i];
                std::cout << stack << "\t" << input.substr(i + 1) << "\tShift " << input[i] << std::endl;
                i++;
            }

            bool reduced = false;
            for (const auto& rule : rules) {
                auto pos = stack.rfind(rule.right);
                if (pos != std::string::npos) {
                    stack.replace(pos, rule.right.length(), rule.left);
                    std::cout << stack << "\t" << input.substr(i) << "\tReduce " << rule.left << "->" << rule.right << std::endl;
                    reduced = true;
                    break;
                }
            }

            if (!reduced) {
                if (stack == rules[0].left && i == input.length()) {
                    std::cout << "Accepted" << std::endl;
                    break;
                }
                if (i == input.length()) {
                    std::cout << "Not Accepted" << std::endl;
                    break;
                }
            }
        }
    }
};

int main() {
    ShiftReduceParser parser;
    int ruleCount;

    std::cout << "Enter the number of production rules: ";
    std::cin >> ruleCount;

    std::cout << "Enter the production rules (in the form 'left->right'):" << std::endl;
    for (int i = 0; i < ruleCount; i++) {
        std::string rule;
        std::cin >> rule;
        size_t pos = rule.find("->");
        if (pos != std::string::npos) {
            parser.addRule(rule.substr(0, pos), rule.substr(pos + 2));
        }
    }

    std::string input;
    std::cout << "Enter the input string: ";
    std::cin >> input;
    parser.setInput(input);

    parser.parse();

    return 0;
}
