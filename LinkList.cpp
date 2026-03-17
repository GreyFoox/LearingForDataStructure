#include <iostream>
using namespace std;

#define ElemType int

class Node {
public:
    ElemType info;
    Node* next;
    
    Node(ElemType val = 0) : info(val), next(nullptr) {}
};

class LinkList {
private:
    Node* head;
    int len;

public:
    LinkList();
    ~LinkList();
    
    bool insert(int idx, ElemType n);
    bool erase(int idx);
    bool alter(int idx, ElemType n);
    int search(ElemType n) const;
    
    int size() const;
    bool empty() const;
    void print() const;
};

LinkList::LinkList() {
    head = nullptr;
    len = 0;
}

LinkList::~LinkList() {
    Node* p = head;
    while (p != nullptr) {
        Node* temp = p;
        p = p->next;
        delete temp;
    }
}

bool LinkList::insert(int idx, ElemType n) {
    if (idx < 1 || idx > len + 1) {
        cerr << "Insert error: index " << idx << " out of range\n";
        return false;
    }
    
    Node* newNode = new Node(n);
    
    if (idx == 1) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* p = head;
        for (int i = 1; i < idx - 1; i++) {
            p = p->next;
        }
        newNode->next = p->next;
        p->next = newNode;
    }
    
    len++;
    return true;
}

bool LinkList::erase(int idx) {
    if (empty()) {
        cerr << "Erase error: list is empty\n";
        return false;
    }
    
    if (idx < 1 || idx > len) {
        cerr << "Erase error: index " << idx << " out of range\n";
        return false;
    }
    
    Node* deleteNode;
    if (idx == 1) {
        deleteNode = head;
        head = head->next;
    } else {
        Node* p = head;
        for (int i = 1; i < idx - 1; i++) {
            p = p->next;
        }
        deleteNode = p->next;
        p->next = deleteNode->next;
    }
    
    cout << deleteNode->info << " is deleted!\n";
    delete deleteNode;
    
    len--;
    return true;
}

bool LinkList::alter(int idx, ElemType n) {
    if (empty()) {
        cerr << "Alter error: list is empty\n";
        return false;
    }
    
    if (idx < 1 || idx > len) {
        cerr << "Alter error: index " << idx << " out of range\n";
        return false;
    }
    
    Node* p = head;
    for (int i = 1; i < idx; i++) {
        p = p->next;
    }
    
    p->info = n;
    return true;
}

int LinkList::search(ElemType n) const {
    Node* p = head;
    int pos = 1;
    
    while (p != nullptr) {
        if (p->info == n) {
            return pos;
        }
        p = p->next;
        pos++;
    }
    
    return -1;
}

int LinkList::size() const {
    return len;
}

bool LinkList::empty() const {
    return len == 0;
}

void LinkList::print() const {
    if (empty()) {
        cout << "empty\n";
        return;
    }
    
    Node* p = head;
    bool notFirst = false;
    
    while (p != nullptr) {
        if (notFirst) {
            cout << " ";
        }
        cout << p->info;
        notFirst = true;
        p = p->next;
    }
    
    cout << "\n";
}