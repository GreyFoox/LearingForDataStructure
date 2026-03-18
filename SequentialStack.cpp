#include <iostream>
using namespace std;

template <typename T>
class SequentialStack {
private:
    T* data;         
    int capacity;     
    int len;          
public:
    SequentialStack();
    ~SequentialStack();
    
    bool push(T n);
    bool pop();
    bool getTop(T& n) const;
    
    int size() const;
    bool empty() const;
};

template <typename T>
SequentialStack<T>::SequentialStack() {
    capacity = 100;           
    data = new T[capacity];   
    len = 0;
}

template <typename T>
SequentialStack<T>::~SequentialStack() {
    delete[] data;            
    data = nullptr;           
}

template <typename T>
bool SequentialStack<T>::push(T n) {
    if (len == capacity) {
        cerr << "Push error: stack is full\n";
        return false;
    }
    
    data[len] = n;
    len++;
    return true;
}

template <typename T>
bool SequentialStack<T>::pop() {
    if (empty()) {
        cerr << "Pop error: stack is empty\n";
        return false;
    }
    
    cout << data[len - 1] << " is popped!\n";
    len--;
    return true;
}

template <typename T>
bool SequentialStack<T>::getTop(T& n) const {
    if (empty()) {
        cerr << "GetTop error: stack is empty\n";
        return false;
    }
    
    n = data[len - 1];
    return true;
}

template <typename T>
int SequentialStack<T>::size() const {
    return len;
}

template <typename T>
bool SequentialStack<T>::empty() const {
    return len == 0;
}