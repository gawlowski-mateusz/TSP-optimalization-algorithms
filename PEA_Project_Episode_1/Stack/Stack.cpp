//
// Created by Mateusz on 23/10/2023.
//

#include <string>
#include "Stack.h"

void Stack::push(int element) {
    if (!size) {
        size++;              // Increment the stack size.
        base = new int[1];   // Create a dynamic array to store the element.
        *base = element;     // Store the element in the array.
    } else {
        size++;                     // Increment the stack size.
        int *temporary = new int[size];  // Create a new larger dynamic array.
        int *base_buffer = base;      // Create a pointer to the current base.
        int *temporary_buffer = temporary;      // Create a pointer to the new array.

        for (int i = 0; i < size - 1; i++) {
            *temporary_buffer = *base_buffer;  // Copy elements from the old array to the new one.
            temporary_buffer++;
            base_buffer++;
        }

        *temporary_buffer = element;  // Add the new element to the end of the new array.

        delete[] base;         // Deallocate memory used by the old array.

        base = temporary;           // Update the base pointer to point to the new array.
    }
}

int Stack::pop() {
    int peak;

    if (size > 1) {
        size--;                 // Decrement the stack size.
        peak = *(base + size);  // Get the top element of the stack.

        int *temporary = new int[size];   // Create a new smaller dynamic array.
        int *base_buffer = base;       // Create a pointer to the current base.
        int *temporary_buffer = temporary;       // Create a pointer to the new array.

        for (int i = 0; i < size; i++) {
            *temporary_buffer = *base_buffer;  // Copy elements to the new array, excluding the top one.
            base_buffer++;
            temporary_buffer++;
        }

        delete[] base;          // Deallocate memory used by the old array.
        base = temporary;            // Update the base pointer to point to the new array.

        return peak;            // Return the removed element.
    } else if (size == 1) {
        peak = *base;           // Get the top element.
        size = 0;               // Reset the stack size.

        delete[] base;          // Deallocate memory used by the old array.
        base = nullptr;         // Set the base pointer to nullptr, indicating an empty stack.

        return peak;            // Return the removed element.
    } else {
        return -1;              // The stack is empty, return -1 as an error indicator.
    }
}

string Stack::showResults() {
    string output = "";
    int *base_buffer = base;

    if (!size) {
        output = "Stack is empty";  // If the stack is empty, indicate that.
    } else {
        for (int i = 0; i < size; i++) {
            output += to_string(*base_buffer) + " ";  // Build a string with stack elements.
            base_buffer++;
        }
    }

    return output;  // Return the string representation of the stack.
}

Stack::Stack() {
    // Constructor: Default constructor, no specific initialization.
}

Stack::~Stack() {
    if (base != nullptr) {
        delete[] base;  // Deallocate memory used by the stack if it exists.
    }
}

void Stack::clear() {
    delete[] base;   // Deallocate memory used by the stack.
    base = nullptr;  // Set the base pointer to nullptr to indicate an empty stack.
    size = 0;        // Reset the stack size to 0.
}

int Stack::getSize() {
    return size;  // Return the current size of the stack.
}

void Stack::copy(Stack *destination) {
    int *base_buffer = base;

    destination->clear();  // Clear the destination stack.

    if (size) {
        for (int i = 0; i < size; i++) {
            destination->push(*base_buffer);  // Copy elements from this stack to the destination stack.
            base_buffer++;
        }
    }
}
