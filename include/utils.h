// utils.h
#ifndef UTILS_H
#define UTILS_H

#include "matrix.h"

// Prints the matrix to the console
void printMatrix(const Matrix &M);

// Pretty prints the determinant of a matrix
void prettyDeterminant(Matrix &M);

// Converts a matrix to Row Echelon Form (RREF)
Matrix toRREF(Matrix &M);

#endif // UTILS_H
