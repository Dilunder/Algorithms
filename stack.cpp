#include <iostream>
using namespace std;

struct StackNode {
    int value;
    StackNode* next;
};

class CustomStack {
private:
    StackNode* top_node;
    int element_count;

public:
    CustomStack() : top_node(nullptr), element_count(0) {}

    ~CustomStack() {
        while (!isEmpty()) {
            popFront();
        }
    }

    bool isEmpty() const {
        return top_node == nullptr;
    }

    int size() const {
        return element_count;
    }

    void display() const {
        StackNode* current = top_node;
        cout << "Stack contents: ";
        while (current != nullptr) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }

    void pushFront(int value) {
        StackNode* new_node = new StackNode{value, top_node};
        top_node = new_node;
        element_count++;
        display();
    }

    void insertAtPosition(int value, int position) {
        if (position < 1 || position > element_count + 1) {
            cout << "Invalid position! Position should be between 1 and " << element_count + 1 << endl;
            return;
        }

        if (position == 1) {
            pushFront(value);
            return;
        }

        StackNode* current = top_node;
        for (int i = 1; i < position - 1; i++) {
            current = current->next;
        }

        StackNode* new_node = new StackNode{value, current->next};
        current->next = new_node;
        element_count++;
        display();
    }

    int popFront() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return -1; // Or throw an exception
        }

        StackNode* node_to_remove = top_node;
        int removed_value = node_to_remove->value;
        top_node = top_node->next;
        delete node_to_remove;
        element_count--;

        cout << "Removed element: " << removed_value << endl;
        return removed_value;
    }

    int removeAtPosition(int position) {
        if (position < 1 || position > element_count) {
            cout << "Invalid position! Position should be between 1 and " << element_count << endl;
            return -1;
        }

        if (position == 1) {
            return popFront();
        }

        StackNode* current = top_node;
        for (int i = 1; i < position - 1; i++) {
            current = current->next;
        }

        StackNode* node_to_remove = current->next;
        int removed_value = node_to_remove->value;
        current->next = node_to_remove->next;
        delete node_to_remove;
        element_count--;

        cout << "Removed element: " << removed_value << endl;
        return removed_value;
    }
};

int main() {
    CustomStack stack;
    int initial_size, value, choice;

    cout << "Enter the number of elements to add initially: ";
    cin >> initial_size;

    for (int i = 0; i < initial_size; i++) {
        cout << "Enter value for element " << i << ": ";
        cin >> value;
        stack.pushFront(value);
    }

    stack.display();

    cout << "Do you want to remove elements? (1 - Yes, 0 - No): ";
    cin >> choice;

    if (choice == 1) {
        int remove_count;
        cout << "How many elements to remove? (Current size: " << stack.size() << "): ";
        cin >> remove_count;

        if (remove_count > stack.size()) {
            cout << "Cannot remove more elements than exist in stack!" << endl;
        } else {
            for (int i = 0; i < remove_count; i++) {
                int position;
                cout << "Enter position to remove (1-" << stack.size() << "): ";
                cin >> position;
                stack.removeAtPosition(position);
            }
        }
    }

    stack.display();
    cout << "Final stack size: " << stack.size() << endl;

    return 0;
}