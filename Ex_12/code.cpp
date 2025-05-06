#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

// Structure to represent a three-address code instruction
struct Instruction {
    string op;      // Operation (if, goto, etc.)
    string arg1;    // First argument
    string arg2;    // Second argument
    string result;  // Result or target label
    int index;      // Instruction index
};

class BackpatchingImplementation {
private:
    vector<Instruction> code;
    int nextInstr;

public:
    BackpatchingImplementation() : nextInstr(0) {}

    // Create a new list containing only instruction i
    list<int> makeList(int i) {
        list<int> newList;
        newList.push_back(i);
        return newList;
    }

    // Merge two lists and return the concatenated list
    list<int> merge(list<int> list1, list<int> list2) {
        list1.splice(list1.end(), list2);
        return list1;
    }

    // Insert target label for each instruction in the list
    void backpatch(list<int> instrList, int targetLabel) {
        for (int instr : instrList) {
            if (instr < code.size()) {
                code[instr].result = to_string(targetLabel);
            }
        }
    }

    // Generate a new instruction and return its index
    int emit(string op, string arg1, string arg2, string result) {
        Instruction instr = {op, arg1, arg2, result, nextInstr};
        code.push_back(instr);
        return nextInstr++;
    }

    // Get the index of the next instruction
    int getNextInstr() {
        return nextInstr;
    }

    // Print the generated code
    void printCode() {
        cout << "Generated Three-Address Code:" << endl;
        for (int i = 0; i < code.size(); i++) {
            cout << i << ": ";
            
            if (code[i].op == "if") {
                cout << "if " << code[i].arg1 << " " << code[i].arg2 
                     << " goto " << code[i].result;
            } else if (code[i].op == "goto") {
                cout << "goto " << code[i].result;
            } else {
                cout << code[i].result << " = " << code[i].arg1;
                if (!code[i].arg2.empty()) {
                    cout << " " << code[i].op << " " << code[i].arg2;
                }
            }
            cout << endl;
        }
    }
};

// Example usage for a simple if-then-else statement
int main() {
    BackpatchingImplementation bp;
    
    // Generate code for: if (a < b) then x = y else x = z
    
    // Emit the conditional jump
    int condJump = bp.emit("if", "a", "< b", "_");
    list<int> trueList = bp.makeList(condJump);
    
    // Emit goto for the false branch
    int gotoFalse = bp.emit("goto", "", "", "_");
    list<int> falseList = bp.makeList(gotoFalse);
    
    // True branch: x = y
    int trueLabel = bp.getNextInstr();
    bp.emit("=", "y", "", "x");
    
    // Goto end
    int gotoEnd = bp.emit("goto", "", "", "_");
    list<int> nextList = bp.makeList(gotoEnd);
    
    // False branch: x = z
    int falseLabel = bp.getNextInstr();
    bp.emit("=", "z", "", "x");
    
    // End label
    int endLabel = bp.getNextInstr();
    
    // Backpatching
    bp.backpatch(trueList, trueLabel);
    bp.backpatch(falseList, falseLabel);
    bp.backpatch(nextList, endLabel);
    
    // Print the generated code
    bp.printCode();
    
    return 0;
}
