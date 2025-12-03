#include <iostream>
#include <vector>
#include <stdexcept>

class IncompatibleMatrixException : public std::exception {
private:
    std::string message;
public:
    IncompatibleMatrixException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class Matrix {
private:
    int rows;
    int cols;
    std::vector<std::vector<int>> data;

public:
    Matrix(int r, int c, int value = 0) : rows(r), cols(c) {
        data.resize(rows, std::vector<int>(cols, value));
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    void setValue(int r, int c, int value) {
        data[r][c] = value;
    }

    int getValue(int r, int c) const {
        return data[r][c];
    }

    Matrix operator+(int value) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + value;
            }
        }
        return result;
    }

    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw IncompatibleMatrixException("Exception: Matrix sizes do not match for addition");
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(int value) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - value;
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw IncompatibleMatrixException("Exception: Matrix sizes do not match for subtraction");
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(int value) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] * value;
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw IncompatibleMatrixException("Exception: Matrix dimensions do not match for multiplication");
        }

        Matrix result(rows, other.cols, 0);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        for (int i = 0; i < m.rows; i++) {
            for (int j = 0; j < m.cols; j++) {
                os << m.data[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }
};

int main() {
    std::string operation;
    std::cout << "Enter the operation you want to perform (add, subtract, multiply): ";
    std::cin >> operation;

    int rowsA, colsA;
    std::cout << "Enter the number of rows for Matrix A: ";
    std::cin >> rowsA;
    std::cout << "Enter the number of columns for Matrix A: ";
    std::cin >> colsA;

    Matrix matrixA(rowsA, colsA);
    std::cout << "Enter the values for Matrix A:" << std::endl;
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsA; j++) {
            int value;
            std::cout << "Enter value at position [" << i << "][" << j << "]: ";
            std::cin >> value;
            matrixA.setValue(i, j, value);
        }
    }

    int rowsB, colsB;
    std::cout << "Enter the number of rows for Matrix B: ";
    std::cin >> rowsB;
    std::cout << "Enter the number of columns for Matrix B: ";
    std::cin >> colsB;

    Matrix matrixB(rowsB, colsB);
    std::cout << "Enter the values for Matrix B:" << std::endl;
    for (int i = 0; i < rowsB; i++) {
        for (int j = 0; j < colsB; j++) {
            int value;
            std::cout << "Enter value at position [" << i << "][" << j << "]: ";
            std::cin >> value;
            matrixB.setValue(i, j, value);
        }
    }

    std::cout << "Matrix A:" << std::endl;
    std::cout << matrixA << std::endl;

    std::cout << "Matrix B:" << std::endl;
    std::cout << matrixB << std::endl;

    try {
        if (operation == "add") {
            Matrix result = matrixA + matrixB;
            std::cout << "After addition:" << std::endl;
            std::cout << result << std::endl;
        }
        else if (operation == "subtract") {
            Matrix result = matrixA - matrixB;
            std::cout << "After subtraction:" << std::endl;
            std::cout << result << std::endl;
        }
        else if (operation == "multiply") {
            Matrix result = matrixA * matrixB;
            std::cout << "After multiplication:" << std::endl;
            std::cout << result << std::endl;
        }
    }
    catch (const IncompatibleMatrixException& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}