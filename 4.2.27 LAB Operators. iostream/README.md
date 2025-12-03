# 4.2.27 LAB Operators. iostream

Este documento detalla el funcionamiento del programa C++ que implementa un Árbol Binario de Búsqueda (BST) y sobrecarga el operador de inserción de flujo (`<<`) para permitir su impresión directa en la consola.

## Captura de pantalla del código

```cpp
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
````

## Captura de pantalla de la ejecución

**Ejecución 1 (Ordenando números desordenados):**

Entrada:

```
20 10 30
```

*(Se inserta 20 (raíz), luego 10 (izquierda), luego 30 (derecha))*

Salida:

```
10
20
30
```

*(El recorrido "inorder" imprime los valores ordenados de menor a mayor)*

**Ejecución 2 (Ordenando otra secuencia):**

Entrada:

```
5 1 8
```

Salida:

```
1
5
8
```

## Explicación del ejercicio

El objetivo de este ejercicio es implementar una estructura de datos personalizada, un Árbol Binario de Búsqueda (BTS), e integrarla perfectamente con el sistema de entrada/salida estándar de C++. La clase `BTS` gestiona la lógica del árbol, insertando nodos de manera que los valores menores queden a la izquierda y los mayores a la derecha. La característica clave de este ejercicio es la **sobrecarga del operador de inserción (`<<`)**. En lugar de obligar al usuario a llamar a una función específica como `tree.print()`, se define una función amiga `operator<<` que permite escribir `std::cout << tree`. Esta función invoca internamente un recorrido "inorder" (izquierda-raíz-derecha), lo que resulta en que los números almacenados en el árbol se impriman automáticamente en orden ascendente en la consola. Esto demuestra cómo extender la funcionalidad de `iostream` para soportar tipos de datos definidos por el usuario de una manera natural y legible.
