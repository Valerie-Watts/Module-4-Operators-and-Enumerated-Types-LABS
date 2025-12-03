# Stack Implementation with Operator Overloading & Exceptions

Este documento detalla el funcionamiento del programa C++ que implementa una estructura de datos tipo Pila (`Stack`) utilizando listas enlazadas, sobrecarga de operadores para las operaciones de `push` y `pop`, y manejo de excepciones para el control de errores.

## Captura de pantalla del código

```cpp
#include <iostream>
#include <exception>

class EmptyError : public std::exception {
public:
    const char* what() const noexcept override {
        return "Exception: stack is empty.";
    }
};

class Node {
public:
    int dato;      
    Node* next;    

    Node(int value, Node* nextNode = nullptr) {
        dato = value;
        next = nextNode;
    }
};

class Stack {
private:
    Node* top;  

public:
    Stack() {
        this->top = nullptr;
    }

    ~Stack() {
        while (top != nullptr) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(int block) {
        Node* newNode = new Node(block, top);
        top = newNode;
    }

    int pop() {
        if (top == nullptr) {
            throw EmptyError();
        }
        else {
            int block = top->dato;
            Node* temp = top;
            top = top->next;
            delete temp;  
            return block;
        }
    }

    int topValue() {
        if (top == nullptr) {
            throw EmptyError();
        }
        else {
            return top->dato;
        }
    }

    bool empty() {
        return top == nullptr;
    }

    friend Stack& operator<<(Stack& s, int value) {
        s.push(value);
        return s;  
    }


    friend Stack& operator>>(Stack& s, int& value) {
        value = s.pop();
        return s;
    }
};

int main() {
    Stack stack;
    int numPush, numPop;

	std::cout << "Enter number of elements to push: ";
    std::cin >> numPush;


	std::cout << "Enter elements to push: ";
    for (int i = 0; i < numPush; i++) {
        int value;
        std::cin >> value;
        stack << value;  
    }

	std::cout << "Enter number of elements to pop: ";
    std::cin >> numPop;

    for (int i = 0; i < numPop; i++) {
        try {
            int value;
            stack >> value; 
            std::cout << value << std::endl;
        }
        catch (const EmptyError& e) {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}
````

## Captura de pantalla de la ejecución

**Ejecución 1 (Operaciones exitosas):**

```
Enter number of elements to push: 3
Enter elements to push: 10 20 30
Enter number of elements to pop: 3
30
20
10
```

*(Nota: Como es una pila LIFO -Last In, First Out-, el último en entrar, 30, es el primero en salir)*

**Ejecución 2 (Error de "stack underflow"):**

```
Enter number of elements to push: 1
Enter elements to push: 50
Enter number of elements to pop: 2
50
Exception: stack is empty.
```

*(Se intenta sacar 2 elementos habiendo solo 1. La segunda operación lanza la excepción)*

## Explicación del ejercicio

El objetivo de este ejercicio es crear una clase `Stack` (Pila) dinámica que utilice una sintaxis avanzada y segura. Para la sintaxis, se aplica la **sobrecarga de operadores**: el operador `<<` se redefine para empujar (`push`) elementos a la pila, y el operador `>>` se redefine para extraer (`pop`) elementos, permitiendo un código en `main` muy intuitivo (ej. `stack << value`).

Para la seguridad, se implementa el **manejo de excepciones**. Se define una clase personalizada `EmptyError` que hereda de `std::exception`. El método `pop` (y por extensión el operador `>>`) verifica si la pila está vacía (`top == nullptr`). Si lo está, lanza (`throw`) una instancia de `EmptyError`. En el bucle de extracción del `main`, cada intento de sacar un dato se protege dentro de un bloque `try`. Si la pila se vacía y se intenta extraer otro elemento, el bloque `catch` captura la excepción `EmptyError` e imprime "Exception: stack is empty.", demostrando cómo controlar errores de estructura de datos sin detener la ejecución del programa.
