# 4.2.28 LAB Representing values and values order

Este documento detalla el funcionamiento del programa C++ que implementa una Máquina de Estados Finitos (FSM) simple, utilizando enumeraciones para definir los estados y la sobrecarga de operadores para gestionar las transiciones y la impresión del historial.

## Captura de pantalla del código

```cpp
#include <iostream>
#include <vector>

enum FSMStates {
    StateStart = 1,
    State1,
    State2,
    State3,
    State4,
    StateStop
};

class FiniteStateMachine {
private:
    FSMStates currentState;
    std::vector<int> history;
    bool stopReached;

public:
    FiniteStateMachine() : currentState(StateStart), stopReached(false) {
        history.push_back(currentState);
    }

    void operator<<(int value) {
        if (stopReached) {
            return;
        }

        if (currentState == StateStart) {
            currentState = (value > 5) ? State1 : State2;
        }
        else if (currentState == State1 || currentState == State2) {
            currentState = (value > 5) ? State3 : State4;
        }
        else if (currentState == State3 || currentState == State4) {
            currentState = StateStop;
            stopReached = true;
            std::cout << "Stop state reached" << std::endl;
        }

        history.push_back(currentState);
    }

    friend std::ostream& operator<<(std::ostream& os, const FiniteStateMachine& fsm) {
        os << "States visited:" << std::endl;
        for (size_t i = 0; i < fsm.history.size(); i++) {
            os << fsm.history[i];

            if (fsm.history[i] == StateStart) {
                os << "(Start)";
            }
            else if (fsm.history[i] == StateStop) {
                os << "(Stop)";
            }

            if (i < fsm.history.size() - 1) {
                os << ", ";
            }
        }
        os << std::endl;
        return os;
    }
};

int main() {
    FiniteStateMachine fsm;

    fsm << 3;
    fsm << 6;
    fsm << 4;

    std::cout << fsm;

    return 0;
}
````

## Captura de pantalla de la ejecución

**Ejecución definida en el main (Entradas: 3, 6, 4):**

1.  **Entrada 3:** Estando en `Start` (1), como 3 ≤ 5, pasa a `State2` (3).
2.  **Entrada 6:** Estando en `State2` (3), como 6 \> 5, pasa a `State3` (4).
3.  **Entrada 4:** Estando en `State3` (4), pasa incondicionalmente a `StateStop` (6).

Salida en consola:

```
Stop state reached
States visited:
1(Start), 3, 4, 6(Stop)
```

## Explicación del ejercicio

El objetivo de este ejercicio es modelar un sistema de estados (Máquina de Estados Finitos) utilizando herramientas de C++ para representar valores y secuencias. Se utiliza un `enum` (`FSMStates`) para asignar nombres legibles y valores enteros secuenciales a cada estado (Start=1, etc.). La clase `FiniteStateMachine` encapsula la lógica de transición.

La característica destacada es la **sobrecarga del operador `<<`** con dos propósitos distintos:

1.  **Como método miembro (`void operator<<(int value)`):** Se usa para "inyectar" datos a la máquina (`fsm << 3`). Este operador actúa como el motor de transición, cambiando el estado actual basándose en si el valor de entrada es mayor o menor a 5.
2.  **Como función amiga (`friend std::ostream& ...`):** Se usa para imprimir el objeto completo (`std::cout << fsm`). Esto permite visualizar la secuencia completa de estados visitados (`history`), etiquetando claramente el inicio y el final de la ejecución.

<!-- end list -->
