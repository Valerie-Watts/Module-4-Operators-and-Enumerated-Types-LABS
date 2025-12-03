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