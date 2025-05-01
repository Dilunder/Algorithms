#include <iostream>
using namespace std;

struct StackNode {
    int value;
    StackNode* next;
};

class Stack {
private:
    StackNode* top_;

public:
    Stack() : top_(nullptr) {}

    void push(int value) {
        StackNode* new_node = new StackNode;
        new_node->value = value;
        new_node->next = top_;
        top_ = new_node;
    }

    int pop() {
        if (isEmpty()) {
            cerr << "Error: Stack underflow\n";
            exit(1);
        }

        StackNode* node_to_remove = top_;
        int popped_value = node_to_remove->value;
        top_ = node_to_remove->next;

        delete node_to_remove;
        return popped_value;
    }

    bool isEmpty() const {
        return top_ == nullptr;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Stack stack;
    int operation_count;
    cin >> operation_count;

    for (int i = 0; i < operation_count; ++i) {
        char operation_type;
        cin >> operation_type;

        if (operation_type == '+') {
            int value;
            cin >> value;
            stack.push(value);
        }
        else if (operation_type == '-') {
            cout << stack.pop() << '\n';
        }
    }

    return 0;
}