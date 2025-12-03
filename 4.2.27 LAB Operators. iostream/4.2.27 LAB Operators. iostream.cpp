#include <iostream>

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BTS {
public:
    Node* root;

    BTS() {
        root = nullptr;
    }

    BTS(int data) {
        root = new Node(data);
    }

    ~BTS() {
        deleteTree(root);
    }


    void insert(int data) {
        if (root == nullptr) {
            root = new Node(data);
            return;
        }

        Node* temp = root;

        while (true) {
            if (data < temp->data) {
                if (temp->left == nullptr) {
                    temp->left = new Node(data);
                    break;
                }
                else {
                    temp = temp->left;
                }
            }
            else {
                if (temp->right == nullptr) {
                    temp->right = new Node(data);
                    break;
                }
                else {
                    temp = temp->right;
                }
            }
        }
    }

    void inorder(Node* currentNode) {
        if (currentNode == nullptr) return;

        if (currentNode->left != nullptr) {
            inorder(currentNode->left);
        }
        std::cout << currentNode->data << std::endl;
        if (currentNode->right != nullptr) {
            inorder(currentNode->right);
        }
    }

    void inorder() {
        inorder(root);
    }

    friend std::ostream& operator<<(std::ostream& os, BTS& tree) {
        tree.inorderPrint(os, tree.root);
        return os;
    }

private:
    void inorderPrint(std::ostream& os, Node* currentNode) 
    {
        if (currentNode == nullptr) return;

        if (currentNode->left != nullptr) {
            inorderPrint(os, currentNode->left);
        }
        os << currentNode->data << std::endl;
        if (currentNode->right != nullptr) {
            inorderPrint(os, currentNode->right);
        }
    }

    void deleteTree(Node* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    
};

int main() {
    BTS tree;
    int value;

    for (int i = 0; i < 3; i++) {
        std::cin >> value;
        tree.insert(value);
    }

    std::cout << tree;

    return 0;
}