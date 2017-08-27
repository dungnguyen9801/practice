//Create a data structure that stores integers, let then add, delete. It also should be be able to return the minimum diff value of the current integers. 
//That is, 
//min_diff = minimum ( | x_i - x_j | ) 
//Example: 

//-1,3,4,10,11,11 
//min_diff = 0 

//-1,3,4,10,11,14 
//min_diff = 1

#include <bits/stdc++.h>
using namespace std;

vector<vector<string>> tests;

struct MinDiff {
    multiset<int> num, diff;
    
    void add(int a) {
        auto up = num.upper_bound(a);
        if (up != num.end()) diff.insert(*up - a);
        if (up != num.begin()) {
            auto dn = up; --dn;
            diff.insert(a - *dn);
            if (up != num.end()) diff.erase(diff.find(*up - *dn));
        }
        num.insert(a);
    }
    
    void erase(int a) {
        if (!num.count(a)) return;
        num.erase(num.find(a));
        auto up = num.upper_bound(a), dn = up; --dn;
        if (up != num.end()) diff.erase(diff.find(*up - a));
        if (up != num.begin()) {
            auto dn = up; --dn;
            diff.erase(diff.find(a - *dn));
            if (up != num.end()) diff.insert(*up - *dn);
        }
    }
    
    int minDiff() {
        if (diff.empty()) return -1;
        return *diff.begin();
    }
};

void run(vector<string> ins) {
    MinDiff md;
    for (int i = 0 ; i < ins.size(); ++i) {
        string s; int x; istringstream iss(ins[i]);
        iss >> s >> x;
        if (s == "add") iss >> x, md.add(x);
        else if (s == "erase") md.erase(x);
        cout << md.minDiff() << " ";
    }
    cout << endl;
}

void initTest() {
    tests = vector<vector<string>>({
        vector<string>({"add 2", "add 9", "add 5" , "erase 5", "add 2", "erase 2"}),
        vector<string>({"add 10", "add 1", "add 100", "erase 5", "add 99", "erase 10"}),
        vector<string>({"add 1", "add 1", "add 1", "erase 1", "add 99", "erase 1", "add 50"}),
        vector<string>({"add 2", "add 10", "add 5", "add 8", "erase 10", "add 4", "erase 5", "erase 4", "erase 8"})
    });
}

int main() {
    initTest();
    for (auto &ins:tests) run(ins);
    return 0;
}
