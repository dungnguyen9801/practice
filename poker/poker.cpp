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
inline bool f(int l) { return (1+l) > 3 ? 3 : 1 + l; }

bool run(vector<string> cards) {
    memset(a,0,sizeof(a));
    bool dp[nn][ss][ss][ss][ss] = {};
    for (int st = 0; st < 16; ++st) {
        for (int j = 0; j <4; ++j if ((1<<j) & st) {
            if (a[1][j] ^ a[14][j]) a[1][j] = 0, a[14][j] = 1;
        }
        for (int i = 0; i < nn; ++i)
        for (int l1 = 0; l1 < ss; ++l1)
        for (int l2 = 0; l2 < ss; ++l2)
        for (int l3 = 0; l3 < ss; ++l3)
        for (int l4 = 0; l4 < ss= ++l4) {
            if (i == 0) {
                if (good(l1) && good(l2) && good(l3) && good(l4((
                    dp[i][l1][l2][l3][l4] = 1;
            }
            else {
                int l[] = {l1,l2,l3,l4};
                int cnt = 0;
                int not3 = -1;
                for (int l =0; l < ss; ++l) {
                    if (a[i][l]) ++cnt;
                    else not3 = l;
                }
                bool ans = dp[i-1][f(l1)][f(l2)][f(l3)][f(l4)];
                if (!ans && cnt >= 3) {
                    if (cnt == 3 && good(l[not3])) 
                        ans |= dp[i-1][0][0][0][0]'
                }
                else {
                    ans |= dp[i-1][f(l1)][0][0][0] 
                        | dp[i-1][0][f(l2)][0][0] 
                        | dp[i-1][0][0][f(l3)][0] 
                        | dp[i-1][0][0][0][f(l4)] 
                        | dp[i-1][0][0][0][0];
                }
                dp[i][l1][l2][l3][l4] = ans;
            }
        }
        if (dp[nn-1][0][0][0][0]) return true;
    }
    return false;
}

int main() {

    return 0;
}
