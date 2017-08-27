//You are in charge of a classroom which has n seats in a single row, numbered 0 through n-1. 
//During the day students enter and leave the classroom for the exam. 
//In order to minimize the cheating, your task is to efficiently seat all incoming students. 

//You're given 2 types of queries: add_student(student_id) -> seat index, and remove_student(student_id) -> void. 

//The rules for seating the student is the following: 
//1) The seat must be unoccupied 
//2) The closest student must be as far away as possible 
//3) Ties can be resolved by choosing the lowest-numbered seat.
#include <bits/stdc++.h>
using namespace std;

int n;

inline int len(const pair<int,int> &a) {
    int diff = a.second - a.first;
    return a.first == -1 || a.second == n ? diff - 1: diff/2; 
}

struct Cmp {
    bool operator() (const pair<int,int> &a, const pair<int,int> &b) {
        int la = len(a), lb = len(b);
        if (la != lb) return la > lb;
        return a.first < b.first;
    }
};

struct Seating {
    set<int> seat;
    map<int,int> id2s;
    set<pair<int,int>, Cmp> gap;
    
    Seating(int ttl) {
        n = ttl;
        seat.insert(-1);
        seat.insert(n);
        gap.insert({-1,n});
    }
    
    inline int getSeat(const pair<int,int> &a) {
        if (a.first == -1) return 0;
        if (a.second == n) return n-1;
        return (a.first + a.second)/2;
    }
    
    int add(int id) {
        if (id2s.count(id)) return -1;
        auto gp = *gap.begin();
        int new_seat = getSeat(gp);
        seat.insert(id2s[id] = new_seat);
        gap.erase(gp);
        if (new_seat > gp.first + 1) gap.insert({gp.first, new_seat});
        if (new_seat < gp.second - 1) gap.insert({new_seat, gp.second});
        return new_seat;
    }
    
    void erase(int id) {
        if (!id2s.count(id)) return;
        int old_seat = id2s[id];
        id2s.erase(id);
        auto it = seat.find(old_seat), ip = next(it,-1), in = next(it,1);
        gap.erase({*ip,*it});
        gap.erase({*it,*in});
        gap.insert({*ip, *in});
        seat.erase(it);
    }
};

vector<vector<string>> tests;
vector<int> ns;


void initTest() {
    ns = vector<int>({10,10});
    tests = vector<vector<string>>({
        {"add 1", "add 7", "add 3", "add 5", "erase 7", "add 8", "erase 3", "add 4", "erase 1", "add 9", "add 6"},
        {"add 4", "add 3", "add 9", "erase 4", "add 12", "add 5", "add 7", "erase 3", "erase 9", "add 8", "add 6"}
    
    });
}


void run(vector<string> &ins, int num) {
    Seating st(num);
    for(auto &s:ins) {
        string in; int id; istringstream iss(s);
        iss >> in >> id;
        if (in == "add") st.add(id);
        else st.erase(id);
        for (auto t:st.seat) if (t >= 0 && t < n) cout << t << " "; cout << endl;
    }
    cout << endl;
}

int main() {
    initTest();
    for (int i = 0; i < tests.size(); ++i) run(tests[i], ns[i]);
}
