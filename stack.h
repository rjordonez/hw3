#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

template <typename T>
class Stack : private std::vector<T> {
public:
    Stack() = default;  // Default constructor
    ~Stack() = default; // Default destructor

    using std::vector<T>::empty;  // Inherit the empty method
    using std::vector<T>::size;   // Inherit the size method

    void push(const T& item) {
        this->push_back(item);  // Use push_back from std::vector
    }

    void pop() {
        if (this->empty()) {
            throw std::underflow_error("Stack underflow");
        }
        this->pop_back();  // Use pop_back from std::vector
    }

    const T& top() const {
        if (this->empty()) {
            throw std::underflow_error("Stack underflow");
        }
        return this->back();  // Use back from std::vector
    }
};

#endif // STACK_H

// #ifndef STACK_H
// #define STACK_H

// #include <vector>
// #include <stdexcept>

// // Use inheritance from std::vector (choose public/private) as appropriate
// template <typename T>
// class Stack 
// {
// public:
//     Stack();
//     ~Stack();
//     bool empty() const;
//     size_t size() const;
//     void push(const T& item);
//     void pop();  // throws std::underflow_error if empty
//     const T& top() const; // throws std::underflow_error if empty
//     // Add other members only if necessary
// };


// #endif