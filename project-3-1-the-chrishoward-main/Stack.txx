#ifndef STACK_TXX
#define STACK_TXX

#include "Stack.hpp"

// Constructor: Initializes the stack to be empty
template<typename T>
Stack<T>::Stack() : n(0), topPtr(nullptr) {
    // empty stack initialized
}

// Destructor: Cleans up dynamically allocated memory
template<typename T>
Stack<T>::~Stack() {
    clear();  // Ensure all nodes are deleted
}

// Copy Constructor: Creates a deep copy of another stack
template<typename T>
Stack<T>::Stack(const Stack<T>& rhs) : n(0), topPtr(nullptr) {
    if (rhs.topPtr != nullptr) {
        Node<T>* current = rhs.topPtr;
        Node<T>* newTop = nullptr;
        Node<T>* prev = nullptr;

        while (current != nullptr) {
            Node<T>* newNode = new Node<T>(current->getItem());
            if (prev == nullptr) {
                newTop = newNode; // Set newTop for the first node
            }
            else {
                prev->setNext(newNode);
            }
            prev = newNode;
            current = current->getNext();
        }
        topPtr = newTop;
        n = rhs.n;  // Update size variable
    }
}

// Assignment Operator: Uses the copy-swap idiom to assign rhs to this
template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T> rhs) noexcept {
    if (this != &rhs) {
        swap(*this, rhs);  // Use the swap function to assign rhs to this
    }
    return *this;
}


// Returns the number of items on the stack
template<typename T>
std::size_t Stack<T>::size() const {
    return n;
}

// Checks if the stack is empty
template<typename T>
bool Stack<T>::isEmpty() const {
    return n == 0;
}

// Pushes an item onto the top of the stack
template<typename T>
bool Stack<T>::push(const T& newItem) {
    // Create a new node with the newItem and link it to the current top
    Node<T>* newNode = new Node<T>(newItem, topPtr);  // New node points to the current top
    topPtr = newNode;  // The new node becomes the new top
    ++n;  // Increase the stack size
    return true;  // Push was successful
}

// Pops the top item off of the stack
template<typename T>
bool Stack<T>::pop() {
    if (isEmpty()) {
        return false;  // Return false if the stack is empty
    }

    Node<T>* nodeToDelete = topPtr;  // Store the top node
    topPtr = topPtr->getNext();  // Move the top pointer to the next node
    delete nodeToDelete;  // Delete the old top node
    --n;  // Decrease the size of the stack
    return true;  // Pop was successful
}

// Peeks at the top item of the stack without removing it
template<typename T>
const T& Stack<T>::peek() const throw(std::range_error) {
    if (isEmpty()) {
        throw std::range_error("Stack is empty");
    }
    return topPtr->getItem();  // Return top item if not empty
}

// Removes and returns the top item from the stack
template<typename T>
T Stack<T>::peekPop() throw(std::range_error) {
    if (isEmpty()) {
        throw std::range_error("Stack is empty");
    }
    T topItem = topPtr->getItem();  // Store the top item
    pop();  // Remove the top item using pop()
    return topItem;  // Return the stored item
}


// Clears the stack
template<typename T>
void Stack<T>::clear() {
    while (!isEmpty()) {
        pop();  // Pop each element to delete it
    }
    n = 0;  // Set size to 0 after clearing (just in case)
}

// Swaps the contents of two stacks
template<typename T>
void Stack<T>::swap(Stack& lhs, Stack& rhs) {
    std::swap(lhs.topPtr, rhs.topPtr);
    std::swap(lhs.n, rhs.n);
}

#endif
