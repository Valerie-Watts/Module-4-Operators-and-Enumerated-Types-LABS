# 4.2.29 LAB Operators. complex classes

Este documento detalla el funcionamiento del programa C++ que implementa un Árbol Binario de Búsqueda y utiliza la herencia para crear tres versiones distintas del árbol, cada una con su propia lógica de recorrido (Inorder, Postorder, Preorder) implementada a través de la sobrecarga de operadores.

## Captura de pantalla del código

```cpp
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
````

## Captura de pantalla de la ejecución

**Ejecución 1 (Insertando valores para formar un árbol):**

Entrada:

```
10 5 15 2 7 12 20 end
```

*(Estructura del árbol: 10 en la raíz; 5 y 15 hijos; etc.)*

Salida:

```
Inorder: 2 5 7 10 12 15 20 
Postorder: 2 7 5 12 20 15 10 
Preorder: 10 5 2 7 15 12 20 
```

**Ejecución 2 (Árbol simple):**

Entrada:

```
2 1 3 end
```

Salida:

```
Inorder: 1 2 3 
Postorder: 1 3 2 
Preorder: 2 1 3 
```

## Explicación del ejercicio

El objetivo de este ejercicio es combinar la **herencia** de clases con la **sobrecarga de operadores** para gestionar diferentes formas de recorrer una estructura de datos compleja. Se define una clase base `BinaryTree` que maneja la lógica fundamental (inserción de nodos y gestión de memoria). Luego, se derivan tres clases específicas: `Inorder`, `Postorder` y `Preorder`.

Cada clase derivada personaliza el comportamiento del operador de salida (`<<`). Aunque todas contienen los mismos datos (el mismo árbol), al hacer `std::cout << inorderTree`, el operador sobrecargado ejecuta un algoritmo de recorrido específico (Izquierda-Raíz-Derecha para Inorder, etc.). Además, cada clase sobrecarga el operador de subíndice (`[]`), permitiendo acceder a los elementos del árbol como si fueran un array lineal ordenado según el criterio de recorrido de esa clase específica. Esto demuestra cómo la programación orientada a objetos permite reutilizar código base (`BinaryTree`) mientras se alteran drásticamente las interfaces de uso (`operator<<`, `operator[]`) en las clases hijas.
