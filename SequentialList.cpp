#include <iostream>
using namespace std;

#define N 1000
#define ElemType int

class SeqList {
private:
    ElemType list[N + 1];
    int len = 0;

public:
    bool insert(int idx, ElemType n) {
        if (empty() && idx != 1) {
            cerr << "Insert error: first element must be at index 1\n";
            return false;
        }
        if (!empty() && (idx < 1 || idx > len + 1)) {
            cerr << "Insert error: index " << idx << " out of range\n";
            return false;
        }
        if (len >= N) {
            cerr << "Insert error: list is full\n";
            return false;
        }
        for (int i = len; i >= idx; i--) {
            list[i + 1] = list[i];
        }
        list[idx] = n;
        len++;
        return true;
    }

    bool erase(int idx) {
        if (empty()) {
            cerr << "Erase error: list is empty\n";
            return false;
        }
        if (idx < 1 || idx > len) {
            cerr << "Erase error: index " << idx << " out of range\n";
            return false;
        }
        ElemType temp = list[idx];
        for (int i = idx + 1; i <= len; i++) {
            list[i - 1] = list[i];
        }
        len--;
        cout << temp << " is deleted!\n";
        return true;
    }

    bool alter(int idx, ElemType n) {
        if (empty()) {
            cerr << "Alter error: list is empty\n";
            return false;
        }
        if (idx < 1 || idx > len) {
            cerr << "Alter error: index " << idx << " out of range\n";
            return false;
        }
        list[idx] = n;
        return true;
    }

    int search(ElemType n) const {
        for (int i = 1; i <= len; i++) {
            if (list[i] == n) {
                return i;
            }
        }
        return -1;
    }

    int size() const { return len; }
    bool empty() const { return len == 0; }

    void print() const {
        if (empty()) { 
            cout << "empty\n";
            return;
        }
        bool notFirst = false;
        for (int i = 1; i <= len; i++) {
            if (notFirst) cout << " ";
            cout << list[i];
            notFirst = true;
        }
        cout << "\n";
    }
};