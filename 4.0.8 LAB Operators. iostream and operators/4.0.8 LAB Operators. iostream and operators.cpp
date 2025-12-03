#include <iostream>

class Mattrix
{
private:
    int values[2][2];

public:

    Mattrix() {

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                values[i][j] = 0;
            }
        }
    }

    friend std::istream& operator>>(std::istream& is, Mattrix& m)
    {

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {

                is >> m.values[i][j];

            }
        }

        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Mattrix& m)
    {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {

                os << m.values[i][j];
                if (j < 1) {
                    os << " ";
                }
            }
            os << std::endl;
        }

        return os;
    }
};

int main()
{
    Mattrix matrix;


    std::cin >> matrix;

    std::cout << matrix;

    return 0;

}