//
// Created by Mateusz on 23/10/2023.
//

#ifndef PEA_PROJECT_EPISODE_1_STACK_H
#define PEA_PROJECT_EPISODE_1_STACK_H

using namespace std;

class Stack {
private:
    int *base = nullptr; // Pointer to the base of the stack (dynamic array).
    int size = 0;        // Current number of elements in the stack.

public:
    void push(int element);
    // Function to push (add) an element onto the stack.

    int pop();
    // Function to pop (remove and return) the top element from the stack.

    string showResults();
    // Function to display the stack contents as a string.

    int getSize();
    // Function to get the current size of the stack.

    void copy(Stack *destination);
    // Function to copy the contents of this stack to another stack.

    Stack();
    // Constructor for initializing a Stack object.

    ~Stack();
    // Destructor for cleaning up allocated memory, if needed.

    void clear();
    // Function to remove all elements from the stack (clear the stack).
};


#endif //PEA_PROJECT_EPISODE_1_STACK_H
