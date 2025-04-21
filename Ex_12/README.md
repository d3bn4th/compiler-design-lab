# Backpatching Implementation in C++

This project demonstrates the backpatching technique used in compiler design for generating code with control flow statements.

## Backpatching Process

For control flow statements like if-else:
1. Generate conditional jumps, leaving targets as placeholders
2. Keep track of these jumps in lists
3. When targets are known, use backpatch() to fill in the placeholders

For loops:
1. Generate the loop condition with placeholder jump targets
2. Create labels for the loop body and exit points
3. Backpatch jumps to the appropriate locations

## Step-by-Step Procedure

### Core Concept
1. Backpatching resolves unknown jump targets in compiler code generation
2. First, emit jump instructions with placeholder targets
3. Keep track of these instructions in lists
4. When targets become known, fill in the placeholders

### If-Then-Else Example
1. Emit conditional jump for `if (a < b)` with unknown target
2. Emit unconditional jump for else path with unknown target
3. Store both jumps in lists (trueList and falseList)
4. Generate label for "then" part
5. Backpatch trueList to point to this label
6. Generate code for "then" part (`c = 1`)
7. Emit jump to end
8. Generate label for "else" part
9. Backpatch falseList to point to this label
10. Generate code for "else" part (`c = 2`)
11. Generate end label
12. Backpatch final jump to end label

### While Loop Example
1. Generate label for loop start
2. Emit conditional jump for `if (a < b)` with unknown target
3. Emit unconditional jump for loop exit with unknown target
4. Generate label for loop body
5. Backpatch conditional jump to body label
6. Generate code for loop body (`c = c + 1`)
7. Emit jump back to loop start
8. Generate exit label
9. Backpatch exit jump to exit label

## Usage

Compile and run the example:

```bash
g++ -std=c++11 backpatching.cpp -o backpatching && ./backpatching
```

The example demonstrates backpatching for both if-else statements and while loops.

## Output

The program shows the intermediate code generated for:

1. `if (a < b) c = 1; else c = 2;`
2. `while (a < b) { c = c + 1; }`

With all jump targets properly backpatched. 