// Implement Ring Buffer with read and write pointers. 
// For example if the Ring buffer is implemented in the form of array of integers , one should be able to read / write more than one integer at a time. In short the data read / written should be in a chunk .


#include <bits/stdc++.h>
#include <thread>
#include <mutex>

using namespace std;

vector<int> string2VI(string s);
void initTest();
vector<string> inputStr;
vector<int> chunks;
vector<int> caps;

struct RingBuffer {
    mutex mtx;
    int cap;
    int read_pointer;
    int write_pointer;
    int input_pointer;
    vector<int> buffer;
    vector<int> input;
    int diff;
    int chunk;

    RingBuffer(int cap, vector<int> input, int chunk) {
        this->cap = cap;
        buffer.resize(cap);
        read_pointer = write_pointer = input_pointer = 0;
        this->input = input;
        this->chunk = chunk;
        diff = 0;
    }
    
    void write() {
        while (input_pointer < input.size()) {
            mtx.lock();
            int to_write = min(min(chunk, cap-diff), (int)input.size() - input_pointer);
            diff += to_write;
            for (int i = 0; i < to_write; ++i) {
                buffer[write_pointer++] = input[input_pointer++];
                if (write_pointer >= cap) write_pointer -= cap;
            }
            mtx.unlock();
        }
    }
    
    void read() {
        while (input_pointer < input.size() || diff) {
            mtx.lock();
            int to_read = min(chunk, diff);
            diff -= to_read;
            for (int i = 0; i < to_read;++i) {
                cout << buffer[read_pointer++] << " ";
                if (read_pointer >= cap) read_pointer -= cap;
            }
            if (to_read) printf("\n");
            mtx.unlock();
        }
    }
};

void run(int cap, vector<int> input, int chunk) {
    RingBuffer rb(cap, input, chunk);
    thread first(&RingBuffer::read, &rb);
    thread second(&RingBuffer::write, &rb);
    first.join();
    second.join();
}

int main() {
    std::cout << "Ring Buffer\n";
    initTest();
    for (int i =0; i < caps.size(); ++i) {
        run(caps[i], string2VI(inputStr[i]), chunks[i]);
        cout << endl;
    }
}

void initTest() {
    caps = vector<int>({4,5,2,3,1});
    inputStr = vector<string>(
        {
            "9,12,8,23,7",
            "9,12,8,23,7,56,23,12,34,20,14",
            "4,6,8,7",
            "6,21,1,3,9,12",
            "13,23,23,45,32,23,4,5,1,7,6,0,2,3,4,5,6"
        });
    chunks = vector<int>({2,4,5,7,100});
}

vector<int> string2VI(string s) {
	for (char&c:s) if (c == ',') c = ' ';
    istringstream iss(s);
    vector<int> v;
    int x;
    while (iss >> x) v.push_back(x);
    return v;
}
