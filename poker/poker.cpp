//Card game rule: the hand is drawn from a pack of cards (no jokers). 
//Play cards ONLY when they are 
//1. 3 of a kind ('AAA' ) or 4 of a kind('AAAA’). 
//2. a straight flush of 3 or more cards('JQK' or 'A23456...' in the same suit). 
//Find out whether the player is able to play the whole hand given. 
//e.g. [Spade A, Spade K, Spade Q, Diamond Q, Heart Q] return false. 
//[Spade A, Spade K, Spade Q, Diamond Q, Heart Q, Club Q] return true.


#include <bits/stdc++.h>
using namespace std;
const int nn = 15, ss = 4;
bool a[nn][ss];

inline bool good(int l) { return l== 0 || l == 3; }
inline bool f(int l, bool x) { if (!x) return 0; return (1+l) > 3 ? 3 : 1 + l; }

vector<vector<string>> tests;
unordered_map<char, int> mp;

bool run(vector<string> cards) {
    memset(a,0,sizeof(a));
    for (auto card:cards)
        a[mp[card[0]]][mp[card[1]]] = true;
    for (int st = 0; st < 16; ++st) {
        for (int j = 0; j <4; ++j) if (((1<<j) & st) && (a[1][j] ^ a[14][j]))
            a[1][j] = 0, a[14][j] = 1;
        bool dp[nn][ss][ss][ss][ss] = {};
        for (int i = 0; i < nn; ++i) {
            vector<int> l(4), nl(4);
            for (; l[0] < ss; ++l[0])
            for (; l[1] < ss; ++l[1])
            for (; l[2] < ss; ++l[2])
            for (; l[3] < ss; ++l[3])
            if (i == 0)
                dp[i][l[0]][l[1]][l[2]][l[3]] = good(l[0]) && good(l[1]) && good(l[2]) && good(l[3]);
            else {
                bool ans = false;
                vector<vector<int>> ways = {{0,0,0,0}, {1,1,1,0}, {1,1,0,1}, {1,0,1,1}, {0,1,1,1}, {1,1,1,1}};
                for (auto &way:ways) {
                    bool can = true;
                    for (int j = 0; j < ss; ++j) if (way[j] && (!a[i][j] || !good(l[j]))) can = false; else nl[j] = f(l[j], way[j] ? 0 : a[i][j]);
                    if (can) ans |= dp[i-1][nl[0]][nl[1]][nl[2]][nl[3]];
                }
                dp[i][l[0]][l[1]][l[2]][l[3]] = ans;
            }
        }
        if (dp[nn-1][0][0][0][0]) return true;
        for (int j = 0; j <4; ++j) if (a[1][j] ^ a[14][j])
            a[1][j] = 1, a[14][j] = 0;
    }
    return false;
}

void initTests() {
    tests = vector<vector<string>>({
        {"AS", "KS", "QS"}
        ,{"QS", "QD", "QH","QC"}
        ,{"AS", "KS", "QS", "QD", "QH"}
        ,{"AS", "KS", "QS", "QD", "QH","QC"}
        ,{"AC", "2D", "3D"}
    
    });
    string k = "A23456789TJQKCDHS";
    vector<int> v({1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3});
    for (int i = 0; i < k.size(); ++i) mp[k[i]] = v[i];
}

int main() {
    initTests();
    for (auto test:tests)
        cout << (run(test) ? "true" : "false") << endl;
    return 0;
}
