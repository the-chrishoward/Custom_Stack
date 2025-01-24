#include "catch.hpp"
#include "Stack.hpp"

// Test: Peek at empty stack
TEST_CASE("Peek at empty stack", "[Stack]") {
    Stack<int> s;

    REQUIRE_THROWS_AS(s.peek(), std::range_error);     // Peek should throw an exception when the stack is empty
    REQUIRE_THROWS_AS(s.peekPop(), std::range_error);  // PeekPop should throw an exception when the stack is empty
}

// Test: Default constructor
TEST_CASE("Default Constructor", "[Stack]") {
    Stack<int> s;
    REQUIRE(s.isEmpty() == true);   // Stack should be empty after default construction
    REQUIRE(s.size() == 0);         // Stack size should be 0
}

// Test: Destructor
TEST_CASE("Destructor", "[Stack]") {
    Stack<int>* s = new Stack<int>();
    s->push(1);
    s->push(2);
    delete s;  // Destructor should clean up memory (no memory leak expected)
    // If no memory leak occurs, the test passes
}

// Test: Copy Constructor
TEST_CASE("Copy Constructor", "[Stack]") {
    Stack<int> s1;
    s1.push(10);
    s1.push(20);
    s1.push(30);

    Stack<int> s2(s1);  // Copy constructor

    REQUIRE(s2.size() == 3);
    REQUIRE(s2.peek() == 30);
    s2.pop();
    REQUIRE(s2.peek() == 20);
    s2.pop();
    REQUIRE(s2.peek() == 10);

    // Ensure original stack (s1) is intact
    REQUIRE(s1.size() == 3);
    REQUIRE(s1.peek() == 30);
}

// Test: Assignment Operator using copy-swap idiom
TEST_CASE("Assignment Operator", "[Stack]") {
    Stack<int> s1;
    s1.push(100);
    s1.push(200);

    Stack<int> s2;
    s2 = s1;  // Assignment

    REQUIRE(s2.size() == 2);
    REQUIRE(s2.peek() == 200);
    s2.pop();
    REQUIRE(s2.peek() == 100);

    // Ensure original stack (s1) is intact
    REQUIRE(s1.size() == 2);
    REQUIRE(s1.peek() == 200);

    // Test self-assignment
    s1 = s1;  // Self-assignment should not cause issues
    REQUIRE(s1.size() == 2);
    REQUIRE(s1.peek() == 200);
}

// Test: Clear method
TEST_CASE("Clear Method", "[Stack]") {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    REQUIRE(s.size() == 3);

    s.clear();  // Clear all elements

    REQUIRE(s.isEmpty() == true);
    REQUIRE(s.size() == 0);
    REQUIRE_THROWS_AS(s.peek(), std::range_error);  // Should throw exception after clearing
}

// Test: Push and Pop functionality
TEST_CASE("Push and Pop", "[Stack]") {
    Stack<int> s;
    REQUIRE(s.isEmpty() == true);

    s.push(10);
    REQUIRE(s.size() == 1);
    REQUIRE(s.peek() == 10);

    s.push(20);
    REQUIRE(s.size() == 2);
    REQUIRE(s.peek() == 20);

    s.pop();  // Remove top element
    REQUIRE(s.size() == 1);
    REQUIRE(s.peek() == 10);

    s.pop();  // Remove the last element
    REQUIRE(s.isEmpty() == true);  // Stack should be empty now
   // REQUIRE_THROWS_AS(s.pop(), std::range_error);  // Popping from an empty stack should throw an error
}

// Test: PeekPop method
TEST_CASE("Peek and Pop", "[Stack]") {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    // PeekPop should return 3 and then remove it
    REQUIRE(s.peekPop() == 3);
    REQUIRE(s.size() == 2);

    // PeekPop should return 2 and then remove it
    REQUIRE(s.peekPop() == 2);
    REQUIRE(s.size() == 1);

    // PeekPop should return 1 and then remove it
    REQUIRE(s.peekPop() == 1);
    REQUIRE(s.size() == 0);

    // PeekPop should throw an exception when stack is empty
    REQUIRE_THROWS_AS(s.peekPop(), std::range_error);
}

// Test: Size method
TEST_CASE("Size Method", "[Stack]") {
    Stack<int> s;
    REQUIRE(s.size() == 0);  // Size should be 0 for an empty stack

    s.push(10);
    REQUIRE(s.size() == 1);  // After pushing one item, size should be 1

    s.push(20);
    REQUIRE(s.size() == 2);  // After pushing another item, size should be 2

    s.pop();
    REQUIRE(s.size() == 1);  // After popping, size should be back to 1

    s.clear();
    REQUIRE(s.size() == 0);  // After clearing the stack, size should be 0 again
}

// Test: Swap method
TEST_CASE("Swap Method", "[Stack]") {
    Stack<int> s1;
    s1.push(1);
    s1.push(2);

    Stack<int> s2;
    s2.push(100);
    s2.push(200);

    s1.swap(s1, s2);  // Swap contents of s1 and s2

    REQUIRE(s1.peek() == 200);  // s1 should now contain s2's elements
    REQUIRE(s2.peek() == 2);    // s2 should now contain s1's elements

    s1.pop();
    REQUIRE(s1.peek() == 100);

    s2.pop();
    REQUIRE(s2.peek() == 1);
}
