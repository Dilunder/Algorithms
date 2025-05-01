#include <iostream>
#include <string>

using namespace std;

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode* root;

    TreeNode* insertNode(TreeNode* node, int value) {
        if (!node) return new TreeNode(value);

        if (value < node->value) {
            node->left = insertNode(node->left, value);
        } else if (value > node->value) {
            node->right = insertNode(node->right, value);
        }
        return node;
    }

    TreeNode* findMinNode(TreeNode* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    TreeNode* deleteNode(TreeNode* node, int value) {
        if (!node) return nullptr;

        if (value < node->value) {
            node->left = deleteNode(node->left, value);
        } else if (value > node->value) {
            node->right = deleteNode(node->right, value);
        } else {
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode* temp = findMinNode(node->right);
            node->value = temp->value;
            node->right = deleteNode(node->right, temp->value);
        }
        return node;
    }

    bool contains(TreeNode* node, int value) {
        while (node) {
            if (value == node->value) return true;
            node = (value < node->value) ? node->left : node->right;
        }
        return false;
    }

    TreeNode* findNext(TreeNode* node, int value) {
        TreeNode* successor = nullptr;
        while (node) {
            if (node->value > value) {
                successor = node;
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return successor;
    }

    TreeNode* findPrevious(TreeNode* node, int value) {
        TreeNode* predecessor = nullptr;
        while (node) {
            if (node->value < value) {
                predecessor = node;
                node = node->right;
            } else {
                node = node->left;
            }
        }
        return predecessor;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int value) {
        if (!contains(value)) {
            root = insertNode(root, value);
        }
    }

    void remove(int value) {
        root = deleteNode(root, value);
    }

    bool contains(int value) {
        return contains(root, value);
    }

    int getNext(int value) {
        TreeNode* nextNode = findNext(root, value);
        return nextNode ? nextNode->value : INT_MIN;
    }

    int getPrevious(int value) {
        TreeNode* prevNode = findPrevious(root, value);
        return prevNode ? prevNode->value : INT_MIN;
    }
};

int main() {
    BinarySearchTree bst;
    string command;
    int number;

    while (cin >> command >> number) {
        if (command == "insert") {
            bst.insert(number);
        } else if (command == "delete") {
            bst.remove(number);
        } else if (command == "exists") {
            cout << (bst.contains(number) ? "true" : "false") << endl;
        } else if (command == "next") {
            int result = bst.getNext(number);
            if (result == INT_MIN) cout << "none" << endl;
            else cout << result << endl;
        } else if (command == "prev") {
            int result = bst.getPrevious(number);
            if (result == INT_MIN) cout << "none" << endl;
            else cout << result << endl;
        }
    }

    return 0;
}