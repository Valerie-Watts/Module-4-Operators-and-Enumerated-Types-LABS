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