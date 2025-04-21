#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

// Simplified instruction structure
struct Instruction {
    string op, arg1, arg2, result;
    
    Instruction(string op, string arg1 = "", string arg2 = "", string result = "?")
        : op(op), arg1(arg1), arg2(arg2), result(result) {}
    
    string toString(int idx) const {
        if (op == "goto") return to_string(idx) + ": goto " + result;
        if (op == "if") return to_string(idx) + ": if " + arg1 + " " + arg2 + " " + result;
        if (op == "label") return to_string(idx) + ": label " + result;
        return to_string(idx) + ": " + result + " = " + arg1 + " " + op + " " + arg2;
    }
};

// Core backpatching class
class CodeGen {
private:
    vector<Instruction> code;
    int tempCount = 0;
    
public:
    // Core backpatching function: Fill placeholder jump targets
    void backpatch(const list<int>& instrs, string target) {
        for (int idx : instrs) {
            if (idx >= 0 && idx < code.size()) {
                code[idx].result = target;
            }
        }
    }
    
    // Add instruction and return its index
    int emit(const Instruction& instr) {
        code.push_back(instr);
        return code.size() - 1;
    }
    
    // Utility methods
    string newTemp() { return "t" + to_string(tempCount++); }
    string newLabel() { return to_string(code.size()); }
    int emitGoto(string target = "?") { return emit(Instruction("goto", "", "", target)); }
    int emitCond(string op, string arg1, string arg2) { return emit(Instruction("if", arg1, op, "?")); }
    list<int> makeList(int idx) { return list<int>{idx}; }
    
    // Combine two lists
    static list<int> merge(const list<int>& list1, const list<int>& list2) {
        list<int> result = list1;
        result.insert(result.end(), list2.begin(), list2.end());
        return result;
    }
    
    // Print all instructions
    void print() const {
        for (size_t i = 0; i < code.size(); i++) {
            cout << code[i].toString(i) << endl;
        }
    }
};

// Main demonstration
int main() {
    // Example 1: if-then-else
    CodeGen gen;
    cout << "Backpatching Example for if-then-else:\n" << endl;
    
    // Variables
    string a = "a", b = "b", c = "c";
    
    // Generate code for: if (a < b) c = 1; else c = 2;
    
    // Condition
    int condJmp = gen.emitCond("<", a, b);
    int falseJmp = gen.emitGoto();
    list<int> trueList = gen.makeList(condJmp);
    list<int> falseList = gen.makeList(falseJmp);
    
    // Then part
    string thenLabel = gen.newLabel();
    gen.backpatch(trueList, thenLabel);
    gen.emit(Instruction("label", "", "", thenLabel));
    
    string t1 = gen.newTemp();
    gen.emit(Instruction("=", "1", "", t1));
    gen.emit(Instruction("=", t1, "", c));
    
    int endJmp = gen.emitGoto();
    list<int> endList = gen.makeList(endJmp);
    
    // Else part
    string elseLabel = gen.newLabel();
    gen.backpatch(falseList, elseLabel);
    gen.emit(Instruction("label", "", "", elseLabel));
    
    string t2 = gen.newTemp();
    gen.emit(Instruction("=", "2", "", t2));
    gen.emit(Instruction("=", t2, "", c));
    
    // End
    string endLabel = gen.newLabel();
    gen.backpatch(endList, endLabel);
    gen.emit(Instruction("label", "", "", endLabel));
    
    gen.print();
    
    // Example 2: while loop
    cout << "\nBackpatching Example for while loop:\n" << endl;
    CodeGen loop;
    
    // Generate code for: while (a < b) { c = c + 1; }
    
    // Loop start
    string loopStart = loop.newLabel();
    loop.emit(Instruction("label", "", "", loopStart));
    
    // Condition
    int loopCond = loop.emitCond("<", a, b);
    int exitJmp = loop.emitGoto();
    list<int> bodyList = loop.makeList(loopCond);
    list<int> exitList = loop.makeList(exitJmp);
    
    // Body
    string bodyLabel = loop.newLabel();
    loop.backpatch(bodyList, bodyLabel);
    loop.emit(Instruction("label", "", "", bodyLabel));
    
    string t3 = loop.newTemp();
    loop.emit(Instruction("+", c, "1", t3));
    loop.emit(Instruction("=", t3, "", c));
    loop.emitGoto(loopStart);
    
    // Exit
    string exitLabel = loop.newLabel();
    loop.backpatch(exitList, exitLabel);
    loop.emit(Instruction("label", "", "", exitLabel));
    
    loop.print();
    
    return 0;
} 