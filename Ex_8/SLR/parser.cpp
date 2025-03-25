#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

struct Item { string lhs, rhs; int dot; };

bool isEqual(const vector<Item>& a, const vector<Item>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++)
        if (a[i].lhs != b[i].lhs || a[i].rhs != b[i].rhs || a[i].dot != b[i].dot)
            return false;
    return true;
}

vector<Item> closure(vector<Item> items, map<string, vector<string>> &g) {
    set<string> added;
    for (size_t i = 0; i < items.size(); i++) {
        Item it = items[i];
        if (it.dot < it.rhs.size()) {
            string s(1, it.rhs[it.dot]);
            if (g.count(s) && !added.count(s)) {
                for (auto &p : g[s]) items.push_back({s, p, 0});
                added.insert(s);
            }
        }
    }
    return items;
}

vector<Item> goTo(vector<Item> items, char sym, map<string, vector<string>> &g) {
    vector<Item> moved;
    for (auto &it : items)
        if (it.dot < it.rhs.size() && it.rhs[it.dot] == sym)
            moved.push_back({it.lhs, it.rhs, it.dot + 1});
    return closure(moved, g);
}

void computeLR0Items(map<string, vector<string>> &g) {
    vector<vector<Item>> states = {closure({{"S'", "S", 0}}, g)};
    map<pair<int, char>, int> trans;
    
    for (size_t i = 0; i < states.size(); i++) {
        set<char> symbols;
        for (auto &it : states[i]) if (it.dot < it.rhs.size()) symbols.insert(it.rhs[it.dot]);
        for (char s : symbols) {
            vector<Item> next = goTo(states[i], s, g);
            int index = -1;
            for (size_t j = 0; j < states.size(); j++) {
                if (isEqual(states[j], next)) { index = j; break; }
            }
            if (index == -1) { states.push_back(next); trans[{i, s}] = states.size() - 1; }
            else trans[{i, s}] = index;
        }
    }
    
    for (size_t i = 0; i < states.size(); i++) {
        cout << "State " << i << ":\n";
        for (auto &it : states[i]) cout << it.lhs << " -> " << it.rhs.substr(0, it.dot) << "." << it.rhs.substr(it.dot) << "\n";
    }
}

int main() {
    map<string, vector<string>> g; int n;
    cout << "Enter number of productions: "; cin >> n;
    for (int i = 0; i < n; i++) {
        string lhs, rhs; cin >> lhs >> rhs;
        g[lhs].push_back(rhs);
    }
    computeLR0Items(g);
}