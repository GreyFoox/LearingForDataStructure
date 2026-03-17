#include <iostream>
using namespace std;

#define ElemType int

// ========== Node Definition ==========
class Node {
public:
    ElemType info;   // Data field: stores actual value
    Node* next;      // Pointer field: points to next node
    
    // Constructor: initialize with default value
    Node(ElemType val = 0) : info(val), next(nullptr) {}
};

// ========== Linked List Definition ==========
class LinkList {
private:
    Node* head;      // Head pointer: points to first node, nullptr if empty
    int len;         // List length: current number of nodes

public:
    // Constructor: initialize empty list
    LinkList();
    
    // Destructor: release all node memory
    ~LinkList();
    
    // ========== Core Operations ==========
    
    // Insert: insert n at position idx (1-based, 1 ≤ idx ≤ len+1)
    // Example: [10, 20] -> insert(2, 15) -> [10, 15, 20]
    bool insert(int idx, ElemType n);
    
    // Erase: delete node at position idx (1 ≤ idx ≤ len)
    // Example: [10, 15, 20] -> erase(2) -> [10, 20]
    bool erase(int idx);
    
    // Alter: change value at position idx to n
    // Example: [10, 20, 30] -> alter(2, 99) -> [10, 99, 30]
    bool alter(int idx, ElemType n);
    
    // Search: return position of value n (1-based), -1 if not found
    // Example: [10, 20, 30] -> search(20) -> 2
    int search(ElemType n) const;
    
    // ========== Helper Operations ==========
    
    // Get list length
    int size() const;
    
    // Check if list is empty
    bool empty() const;
    
    // Print: space-separated, no brackets
    // Example: [10, 15, 20] -> print() -> "10 15 20"
    void print() const;
};

// ========== Function Implementations ==========

// Constructor
LinkList::LinkList() {
    head = nullptr;  // Initialize head pointer to null
    len = 0;         // Initialize length to 0
}

// Destructor
LinkList::~LinkList() {
    Node* p = head;
    while (p != nullptr) {
        Node* temp = p;      // Save current node
        p = p->next;         // Move to next first
        delete temp;         // Then delete current node
    }
    // head and len are automatically destroyed
}

// Insert
bool LinkList::insert(int idx, ElemType n) {
    // 1. Boundary check
    if (idx < 1 || idx > len + 1) {
        cerr << "Insert error: index " << idx << " out of range\n";
        return false;
    }
    
    // 2. Create new node
    Node* newNode = new Node(n);
    
    // 3. Handle cases
    if (idx == 1) {
        // Insert at head: new node becomes new head
        newNode->next = head;
        head = newNode;
    } else {
        // Insert at middle/tail: find predecessor at position idx-1
        Node* p = head;
        for (int i = 1; i < idx - 1; i++) {  // Move idx-2 steps
            p = p->next;
        }
        newNode->next = p->next;
        p->next = newNode;
    }
    
    // 4. Update length
    len++;
    return true;
}

// Erase
bool LinkList::erase(int idx) {
    // 1. Check empty list
    if (empty()) {
        cerr << "Erase error: list is empty\n";
        return false;
    }
    
    // 2. Boundary check
    if (idx < 1 || idx > len) {
        cerr << "Erase error: index " << idx << " out of range\n";
        return false;
    }
    
    // 3. Handle cases
    Node* deleteNode;
    if (idx == 1) {
        // Erase head: save old head, update head to next
        deleteNode = head;
        head = head->next;
    } else {
        // Erase middle/tail: find predecessor at position idx-1
        Node* p = head;
        for (int i = 1; i < idx - 1; i++) {  // Move idx-2 steps
            p = p->next;
        }
        deleteNode = p->next;
        p->next = deleteNode->next;
    }
    
    // 4. Output and free memory
    cout << deleteNode->info << " is deleted!\n";
    delete deleteNode;
    
    // 5. Update length
    len--;
    return true;  // Don't forget return value!
}

// Alter
bool LinkList::alter(int idx, ElemType n) {
    // 1. Check empty list
    if (empty()) {
        cerr << "Alter error: list is empty\n";
        return false;
    }
    
    // 2. Boundary check
    if (idx < 1 || idx > len) {  // Valid range: 1 to len (inclusive)
        cerr << "Alter error: index " << idx << " out of range\n";
        return false;
    }
    
    // 3. Traverse to position idx
    Node* p = head;
    for (int i = 1; i < idx; i++) {  // Move idx-1 steps
        p = p->next;
    }
    
    // 4. Modify value
    p->info = n;
    return true;
}

// Search
int LinkList::search(ElemType n) const {
    Node* p = head;
    int pos = 1;  // 1-based position counter
    
    // Traverse and compare
    while (p != nullptr) {
        if (p->info == n) {
            return pos;  // Found: return position
        }
        p = p->next;
        pos++;
    }
    
    // Not found
    return -1;
}

// Get length
int LinkList::size() const {
    return len;
}

// Check if empty
bool LinkList::empty() const {
    return len == 0;
}

// Print: space-separated, no brackets
void LinkList::print() const {
    if (empty()) {
        cout << "empty\n";  // Simple output for empty list
        return;
    }
    
    Node* p = head;
    bool notFirst = false;  // Control space: no space before first element
    
    while (p != nullptr) {
        if (notFirst) {
            cout << " ";  // Add space before subsequent elements
        }
        cout << p->info;
        notFirst = true;
        p = p->next;  // Don't forget to move pointer!
    }
    
    cout << "\n";  // Newline at end
}

// ========== Test Cases ==========
int main() {
    LinkList list;  // Automatically calls constructor
    
    cout << "=== Test Insert ===\n";
    list.insert(1, 10);        // [] -> [10]
    list.insert(2, 20);        // [10] -> [10 20]
    list.insert(2, 15);        // [10 20] -> [10 15 20]
    list.insert(1, 5);         // [10 15 20] -> [5 10 15 20]
    list.print();              // Expected: 5 10 15 20
    
    cout << "\n=== Test Search ===\n";
    int pos = list.search(15);
    cout << "Found 15 at position " << pos << "\n";  // Expected: 3
    
    cout << "\n=== Test Alter ===\n";
    list.alter(2, 99);         // [5 10 15 20] -> [5 99 15 20]
    list.print();              // Expected: 5 99 15 20
    
    cout << "\n=== Test Erase ===\n";
    list.erase(2);             // Delete 99
    list.print();              // Expected: 5 15 20
    list.erase(1);             // Delete head 5
    list.print();              // Expected: 15 20
    
    cout << "\n=== Test Boundary ===\n";
    list.insert(0, 100);       // Expected: Error
    list.insert(100, 100);     // Expected: Error
    list.erase(0);             // Expected: Error
    
    cout << "\n=== Test Status ===\n";
    cout << "Size: " << list.size() << "\n";
    cout << "Empty? " << (list.empty() ? "Yes" : "No") << "\n";
    
    cout << "\n=== Test Clear ===\n";
    while (!list.empty()) {
        list.erase(1);
    }
    list.print();              // Expected: empty
    
    cout << "\nProgram end, destructor auto-frees memory.\n";
    
    return 0;
}