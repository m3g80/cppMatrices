#include "../include/matrix.h"
#include "../include/utils.h"
#include <iostream>
#include <chrono>
#include <ctime> 


using namespace std;
using namespace std::chrono;


int main(){ 
    vector<vector<int> > vals = {{-9, 21, 15, 10, 2}, 
                                 {4, 1, 2, 12, -424}, 
                                 {10, -34, 1, 11, 10}, 
                                 {1, 2, 3, 4, 5},
                                 {0, 112, -64, 11, 3}}; 
    Matrix test5x5 = Matrix(5, 5, vals);// Generate a 5 x 5 Matrix using the first constructor.
    printMatrix(test5x5);
    Matrix randomMatrix = Matrix(45, 45); 
    randomMatrix.generateRandomValues(); // Generate a 50 x 50 Matrix intialised with 0s then populate with random values
    auto start = high_resolution_clock::now(); 
    printMatrix(randomMatrix.multiply(randomMatrix));
    auto end = high_resolution_clock::now(); // 3507 microseconds to multiply 2 50 x 50 matrices
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken for computation: " << duration.count() << " microseconds." << endl;

    // TODO Parallelise Determinants and RREF

}