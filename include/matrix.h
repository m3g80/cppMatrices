#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <tuple>

class Matrix {
public:
    int rows;
    int columns;
    std::vector<std::vector<double>> values;

    // Constructors
    Matrix(int rs, int cs, std::vector<std::vector<double>> &vals);
    Matrix(int rs, int cs);

    // Core Functions
    void generateRandomValues();
    Matrix add(double lambda, const Matrix &M);
    Matrix sMultiply(double lambda);
    Matrix multiply(const Matrix &M);
    Matrix transpose();
    std::tuple<std::vector<double>, char, int, int> findLeast();
    int calcDet();
    Matrix removeij(int ri, int rj);

    // Row Operations
    void divideRow(double lambda, int rowId);
    void addRow(double lambda, int rowA, int rowB);
    void swapRows(int rowA, int rowB);

};

#endif // MATRIX_H
