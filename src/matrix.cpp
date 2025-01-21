#include "../include/matrix.h"
#include <random>
#include <thread>
#include <stdexcept>
#include <cmath>
#include <omp.h> 

using namespace std;

// Constructors
Matrix::Matrix(int rs, int cs, vector<vector<int>> &vals) : rows(rs), columns(cs) {
    if (vals.size() != rs || rs < 0 || cs < 0 || (!vals.empty() && vals[0].size() != cs)) {
        throw invalid_argument("Dimensions of the provided values do not match the specified rows and columns.");
    } else {
        values = vals;
    }
}

Matrix::Matrix(int rs, int cs) : rows(rs), columns(cs), values(vector<vector<int>>(rs, vector<int>(cs, 0))) {}

// Core Functions
void Matrix::generateRandomValues() {
 random_device rd;
 mt19937 gen(rd());
 uniform_int_distribution<> dis(1, 100);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            values[i][j] = dis(gen);
        }
    }
}

Matrix Matrix::add(int lambda, const Matrix &M) {
    if (M.columns != columns || M.rows != rows) {
        throw invalid_argument("Incorrect Dimensions");
    }
    Matrix result(rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result.values[i][j] = values[i][j] + lambda * M.values[i][j];
        }
    }
    return result;
}

Matrix Matrix::sMultiply(int lambda) {
    Matrix result(rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result.values[i][j] = lambda * values[i][j];
        }
    }
    return result;
}

Matrix Matrix::multiply(const Matrix &M) {
    if (columns != M.rows) {
        throw invalid_argument("Incorrect Dimensions");
    }
    Matrix result(rows, M.columns);

#pragma omp parallel for collapse(2)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < M.columns; j++) {
            int cij = 0;
            for (int k = 0; k < columns; k++) {
                cij += values[i][k] * M.values[k][j];
            }
            result.values[i][j] = cij;
        }
    }
    return result;
}

Matrix Matrix::transpose() {
    Matrix result(columns, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result.values[j][i] = values[i][j];
        }
    }
    return result;
}
 tuple<vector<int>, char, int, int> Matrix::findLeast() {
 vector<vector<int>> transposed = transpose().values;
    int initialCount = count(transposed[0].begin(), transposed[0].end(), 0);
    auto least = make_tuple(transposed[0], 'c', 0, initialCount);

    for (int i = 0; i < transposed.size(); i++) {
        int zeroCount = count(transposed[i].begin(), transposed[i].end(), 0);
        if (zeroCount > get<3>(least)) {
         get<0>(least) = transposed[i];
         get<2>(least) = i;
         get<3>(least) = zeroCount;
        }
    }

    return least;
}

int Matrix::calcDet() {
    if (rows != columns) {
        throw invalid_argument("Not a Square Matrix");
    }
    if (rows == 2) {
        return values[0][0] * values[1][1] - values[0][1] * values[1][0];
    }

    auto least = findLeast();
    char tag = get<1>(least);
    int det = 0;

    if (tag == 'r') {
        int i = get<2>(least);
        for (int j = 0; j < columns; j++) {
            det += pow(-1, i + j) * values[i][j] * removeij(i, j).calcDet();
        }
    } else {
        int j = get<2>(least);
        for (int i = 0; i < rows; i++) {
            det += pow(-1, i + j) * values[i][j] * removeij(i, j).calcDet();
        }
    }

    return det;
}

Matrix Matrix::removeij(int ri, int rj) {
    Matrix result(rows - 1, columns - 1);
    int newRow = 0;
    for (int i = 0; i < rows; i++) {
        if (i == ri) continue;
        int newCol = 0;
        for (int j = 0; j < columns; j++) {
            if (j == rj) continue;
            result.values[newRow][newCol++] = values[i][j];
        }
        newRow++;
    }
    return result;
}

// Row Operations
void Matrix::divideRow(double lambda, int rowId) {
    for (int i = 0; i < columns; i++) {
        values[rowId][i] /= lambda;
    }
}

void Matrix::addRow(double lambda, int rowA, int rowB) {
    for (int i = 0; i < columns; i++) {
        values[rowB][i] += lambda * values[rowA][i];
    }
}

void Matrix::swapRows(int rowA, int rowB) {
 swap(values[rowA], values[rowB]);
}
