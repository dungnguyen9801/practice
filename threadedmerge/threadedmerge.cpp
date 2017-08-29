#include <bits/stdc++.h>
#include <thread>
using namespace std;

int count(const vector<int> &a, const vector<int>&b, int xa, int ya, int xb, int yb) {
    int ans = 0;
    while (xa < ya && xb < yb) {
        if (a[xa] < b[xb]) ++xa;
        else if (a[xa] > b[xb]) ++xb;
        else ++xa, ++xb;
        ++ans;
    }
    return ans + ya -xa + yb - xb;
}

void getUnion(const vector<int> &a, const vector<int>&b, int xa, int ya, int xb, int yb, int *dest) {
    while (xa < ya && xb < yb) {
        if (a[xa] < b[xb]) *dest = a[xa++];
        else if (a[xa] > b[xb]) *dest = b[xb++];
        else *dest = a[xa++], ++xb;
        ++dest;
    }
    while (xa < ya) *dest = a[xa++], ++dest; 
    while (xb < yb) *dest = b[xb++], ++dest;
}


void prep(const vector<int>&a, const vector<int>&b, int numParts, int part, vector<int> &param) {
    int na = a.size();
    int xa = na/numParts*part;
    int ya = (part < numParts - 1) ? na/numParts*(part+1) : na;
    int mn = (xa == 0) ? min(a[0],b[0]) : a[xa];
    int mx = (ya == na) ? max(a.back(), b.back()) : a[ya] - 1;
    int yb = -1, xb = (int)b.size();
    int lo = 0, hi = (int)b.size() -1;
    while (lo <= hi) {
        int mid = (lo + hi)/2;
        if (b[mid] <= mx) {
            yb = mid;
            lo = mid + 1;
        }
        else hi = mid - 1;
    }
    lo = 0, hi = (int)b.size() -1;
        while (lo <= hi) {
        int mid = (lo + hi)/2;
        if (b[mid] >= mn) {
            xb = mid;
            hi = mid - 1;
        }
        else lo = mid + 1;
    }
    param = {count(a,b,xa,ya,xb,yb+1), xa, ya, xb, yb+1};
}

vector<int> run1(vector<int> &a, vector<int>&b) {
    vector<int> ans;
    int xa = 0, ya = a.size(), xb = 0, yb =b.size();
    while (xa < ya && xb < yb) {
        if (a[xa] < b[xb]) ans.push_back(a[xa++]);
        else if (a[xa] > b[xb]) ans.push_back(b[xb++]);
        else ans.push_back(a[xa++]),++xb;
    }
    while (xa < ya) ans.push_back(a[xa++]); 
    while (xb < yb) ans.push_back(b[xb++]);
    return ans;
}

vector<int> run(vector<int> &a, vector<int>&b, int numThreads) {
    if (a.size() < b.size()) a.swap(b);
    vector<vector<int>> params(numThreads);
    thread threads[numThreads];
    int sz = 0;
    for (int i = 0; i < numThreads; ++i)
        threads[i] = thread(prep,ref(a),ref(b),numThreads,i, ref(params[i]));
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
        sz += params[i][0];
        if (i) params[i][0] += params[i-1][0];
    }
    auto ans = new int[sz];
    for (int i = 0; i < numThreads; ++i)
        threads[i] = thread(getUnion, ref(a),ref(b),params[i][1], params[i][2], params[i][3], params[i][4], ans + (i ? params[i-1][0] : 0));
    for (int i = 0; i < numThreads; ++i)
        threads[i].join();
        
    vector<int> v(ans, ans + sz);
    delete[] ans;
    return v;
}

vector<vector<int>> as, bs;

void initTests() {
    as = vector<vector<int>>({
        {1,2,5,6,7,10}
        ,{2,4,5,7}
        ,{1}
        ,{2,4,7,9,12,15,17,19,20,33}
    });
    bs = vector<vector<int>>({
        {1,4,5,9}
        ,{3,6,8,9}
        ,{1}
        ,{1,2,4,9,13,14,15,16,17,18,20,25}
    });
    vector<int> big;
    const int size = 100000000;
    for (int i = 0; i < size; ++i) 
        big.push_back(rand()%5 + 1 + (big.empty() ? 0 : big.back()));
    as.push_back(big);
    bs.push_back(big);
}

int main() {
    initTests();
    for (int i = 0; i < as.size(); ++i) {
        vector<int> ans, ans1;
        {
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            ans = run(as[i],bs[i],4);
            std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
            std::cout << "Time difference with threads: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;
        }
        {
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            ans1 = run1(as[i],bs[i]);
            std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
            std::cout << "Time difference: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;
        }
        assert(ans == ans1);
        cout << endl;
    }
    return 0;
}
