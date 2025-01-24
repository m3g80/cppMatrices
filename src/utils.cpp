#include "../include/matrix.h"
#include "../include/utils.h"

#include <iostream>

// Prints the matrix to the console
void printMatrix(const Matrix &M) {
    for (const std::vector<double> &row : M.values) {
        for (const int &val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

// Pretty prints the determinant of a matrix
void prettyDeterminant(Matrix &M) {
    int det = M.calcDet();
    std::cout << "The determinant of the " << M.rows << "x" << M.columns << " matrix is:" << std::endl;
    printMatrix(M);
    std::cout << "\nDeterminant: " << det << std::endl;
}

Matrix toRREF(Matrix &M) {
    int i = 0;
    for (int j = 0; j < M.rows && i < M.columns;) {
        if (M.values[j][i] == 0) {
            int swapRow = j + 1;
            while (swapRow < M.rows && M.values[swapRow][i] == 0) {
                swapRow++;
            }
            if (swapRow == M.rows) {
                i++;
                continue;
            }
            M.swapRows(j, swapRow);
        }
        double lambda = M.values[j][i];
        M.divideRow(lambda, j);
        for (int k = 0; k < M.rows; k++) {
            if (k != j) {
                double lambda2 = M.values[k][i];
                M.addRow(-lambda2, j, k);
            }
        }
        j++;
        i++;
    }
    return M;
}
