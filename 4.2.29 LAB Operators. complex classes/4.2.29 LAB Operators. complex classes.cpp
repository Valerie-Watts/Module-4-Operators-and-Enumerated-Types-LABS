#include <iostream>
#include <vector>
#include <string>

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
protected:
    Node* root;

    Node* insertNode(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insertNode(node->left, value);
        }
        else {
            node->right = insertNode(node->right, value);
        }

        return node;
    }

    void deleteTree(Node* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        root = insertNode(root, value);
    }

    virtual ~BinaryTree() {
        deleteTree(root);
    }
};

class Inorder : public BinaryTree {
private:
    void inorderTraversal(Node* node, std::vector<int>& elements) const {
        if (node == nullptr) return;

        inorderTraversal(node->left, elements);
        elements.push_back(node->data);
        inorderTraversal(node->right, elements);
    }

    void inorderPrint(std::ostream& os, Node* node) const {
        if (node == nullptr) return;

        inorderPrint(os, node->left);
        os << node->data << " ";
        inorderPrint(os, node->right);
    }

public:
    friend std::ostream& operator<<(std::ostream& os, const Inorder& tree) {
        os << "Inorder: ";
        tree.inorderPrint(os, tree.root);
        return os;
    }

    int operator[](int index) {
        std::vector<int> elements;
        inorderTraversal(root, elements);
        return elements[index];
    }
};

class Postorder : public BinaryTree {
private:
    void postorderTraversal(Node* node, std::vector<int>& elements) const {
        if (node == nullptr) return;

        postorderTraversal(node->left, elements);
        postorderTraversal(node->right, elements);
        elements.push_back(node->data);
    }

    void postorderPrint(std::ostream& os, Node* node) const {
        if (node == nullptr) return;

        postorderPrint(os, node->left);
        postorderPrint(os, node->right);
        os << node->data << " ";
    }

public:
    friend std::ostream& operator<<(std::ostream& os, const Postorder& tree) {
        os << "Postorder: ";
        tree.postorderPrint(os, tree.root);
        return os;
    }

    int operator[](int index) {
        std::vector<int> elements;
        postorderTraversal(root, elements);
        return elements[index];
    }
};

class Preorder : public BinaryTree {
private:
    void preorderTraversal(Node* node, std::vector<int>& elements) const {
        if (node == nullptr) return;

        elements.push_back(node->data);
        preorderTraversal(node->left, elements);
        preorderTraversal(node->right, elements);
    }

    void preorderPrint(std::ostream& os, Node* node) const {
        if (node == nullptr) return;

        os << node->data << " ";
        preorderPrint(os, node->left);
        preorderPrint(os, node->right);
    }

public:
    friend std::ostream& operator<<(std::ostream& os, const Preorder& tree) {
        os << "Preorder: ";
        tree.preorderPrint(os, tree.root);
        return os;
    }

    int operator[](int index) {
        std::vector<int> elements;
        preorderTraversal(root, elements);
        return elements[index];
    }
};

int main() {
    Inorder inorderTree;
    Postorder postorderTree;
    Preorder preorderTree;

    std::string input;
    while (std::cin >> input && input != "end") {
        int value = std::stoi(input);
        inorderTree.insert(value);
        postorderTree.insert(value);
        preorderTree.insert(value);
    }

    std::cout << inorderTree << std::endl;
    std::cout << postorderTree << std::endl;
    std::cout << preorderTree << std::endl;

    return 0;
}