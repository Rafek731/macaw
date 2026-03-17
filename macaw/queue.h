#pragma once

#define MAX_LETTERS 12

namespace macaw {

template<typename T>
class queue {
    char q[MAX_LETTERS];
    char front, back;
    
    public:
    
    queue(): q({0}), front(0), back(-1) {}
    
    inline void push_back(char x) {
        q[++back] = x;
    }

    inline char pop_front() {
        return q[front++]; 
    }

    bool empty() {
        return front == back + 1;
    }
};

}