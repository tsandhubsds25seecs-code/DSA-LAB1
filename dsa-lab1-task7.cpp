// dsa-lab1-task7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <cmath>
using namespace std;

// ==================== MATRIX UTILITIES ====================

// Print matrix
void printMatrix(const vector<vector<int>>& matrix, const string& name = "") {
    if (!name.empty()) {
        cout << name << ":" << endl;
    }
    if (matrix.empty()) {
        cout << "Empty matrix" << endl;
        return;
    }
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << setw(6) << val << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Compare two matrices
bool compareMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    if (A.empty() && B.empty()) return true;
    if (A.size() != B.size() || A[0].size() != B[0].size()) {
        return false;
    }

    for (size_t i = 0; i < A.size(); i++) {
        for (size_t j = 0; j < A[0].size(); j++) {
            if (A[i][j] != B[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Generate random matrix
vector<vector<int>> generateRandomMatrix(int size, int minVal = 0, int maxVal = 9) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(minVal, maxVal);

    vector<vector<int>> matrix(size, vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = dis(gen);
        }
    }
    return matrix;
}

// ==================== STANDARD MATRIX MULTIPLICATION ====================
// Time Complexity: O(n³)

vector<vector<int>> standardMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    if (n == 0) return {};

    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// ==================== STRASSEN'S ALGORITHM ====================
// Time Complexity: O(n^log₂⁷) ≈ O(n².⁸⁰⁷)

// Matrix addition
vector<vector<int>> add(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Matrix subtraction
vector<vector<int>> subtract(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Strassen's recursive multiplication
vector<vector<int>> strassenMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();

    // Base case
    if (n == 1) {
        return { {A[0][0] * B[0][0]} };
    }

    // If n is odd, pad to even size
    if (n % 2 != 0) {
        int newSize = n + 1;
        vector<vector<int>> A_padded(newSize, vector<int>(newSize, 0));
        vector<vector<int>> B_padded(newSize, vector<int>(newSize, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A_padded[i][j] = A[i][j];
                B_padded[i][j] = B[i][j];
            }
        }

        vector<vector<int>> C_padded = strassenMultiply(A_padded, B_padded);
        vector<vector<int>> C(n, vector<int>(n));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = C_padded[i][j];
            }
        }
        return C;
    }

    int half = n / 2;

    // Partition matrices into 4 submatrices each
    vector<vector<int>> A11(half, vector<int>(half));
    vector<vector<int>> A12(half, vector<int>(half));
    vector<vector<int>> A21(half, vector<int>(half));
    vector<vector<int>> A22(half, vector<int>(half));
    vector<vector<int>> B11(half, vector<int>(half));
    vector<vector<int>> B12(half, vector<int>(half));
    vector<vector<int>> B21(half, vector<int>(half));
    vector<vector<int>> B22(half, vector<int>(half));

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    // Compute 7 products
    vector<vector<int>> P1 = strassenMultiply(A11, subtract(B12, B22));
    vector<vector<int>> P2 = strassenMultiply(add(A11, A12), B22);
    vector<vector<int>> P3 = strassenMultiply(add(A21, A22), B11);
    vector<vector<int>> P4 = strassenMultiply(A22, subtract(B21, B11));
    vector<vector<int>> P5 = strassenMultiply(add(A11, A22), add(B11, B22));
    vector<vector<int>> P6 = strassenMultiply(subtract(A12, A22), add(B21, B22));
    vector<vector<int>> P7 = strassenMultiply(subtract(A11, A21), add(B11, B12));

    // Compute result submatrices
    vector<vector<int>> C11 = add(subtract(add(P5, P4), P2), P6);
    vector<vector<int>> C12 = add(P1, P2);
    vector<vector<int>> C21 = add(P3, P4);
    vector<vector<int>> C22 = subtract(subtract(add(P5, P1), P3), P7);

    // Combine submatrices
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }

    return C;
}

// ==================== TIMING UTILITY ====================

template<typename Func>
long long measureTime(Func func) {
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

// ==================== MAIN FUNCTION ====================

int main() {
    cout << "\n=== STRASSEN'S MATRIX MULTIPLICATION ===" << endl;
    cout << "========================================\n" << endl;

    // ===== TEST CASE 1: 2x2 Matrix =====
    cout << "TEST CASE 1: 2x2 Matrix Multiplication" << endl;
    cout << "--------------------------------------" << endl;

    vector<vector<int>> A2 = { {1, 2}, {3, 4} };
    vector<vector<int>> B2 = { {5, 6}, {7, 8} };

    cout << "Matrix A:" << endl;
    printMatrix(A2);
    cout << "Matrix B:" << endl;
    printMatrix(B2);

    vector<vector<int>> standard2 = standardMultiply(A2, B2);
    vector<vector<int>> strassen2 = strassenMultiply(A2, B2);

    cout << "Standard Multiplication:" << endl;
    printMatrix(standard2);
    cout << "Strassen's Multiplication:" << endl;
    printMatrix(strassen2);

    cout << "Matrices Match: " << (compareMatrices(standard2, strassen2) ? "YES" : "NO") << endl << endl;

    // ===== TEST CASE 2: 4x4 Matrix =====
    cout << "TEST CASE 2: 4x4 Matrix Multiplication (Random)" << endl;
    cout << "-----------------------------------------------" << endl;

    vector<vector<int>> A4 = generateRandomMatrix(4);
    vector<vector<int>> B4 = generateRandomMatrix(4);

    cout << "Matrix A (4x4):" << endl;
    printMatrix(A4);
    cout << "Matrix B (4x4):" << endl;
    printMatrix(B4);

    vector<vector<int>> standard4 = standardMultiply(A4, B4);
    vector<vector<int>> strassen4 = strassenMultiply(A4, B4);

    cout << "Standard Result:" << endl;
    printMatrix(standard4);
    cout << "Strassen's Result:" << endl;
    printMatrix(strassen4);

    cout << "Matrices Match: " << (compareMatrices(standard4, strassen4) ? "✓ YES" : "✗ NO") << endl << endl;

    // ===== TEST CASE 3: 3x3 Matrix (Odd Size) =====
    cout << "TEST CASE 3: 3x3 Matrix Multiplication (Odd Size)" << endl;
    cout << "-----------------------------------------------" << endl;

    vector<vector<int>> A3 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    vector<vector<int>> B3 = { {9, 8, 7}, {6, 5, 4}, {3, 2, 1} };

    cout << "Matrix A (3x3):" << endl;
    printMatrix(A3);
    cout << "Matrix B (3x3):" << endl;
    printMatrix(B3);

    vector<vector<int>> standard3 = standardMultiply(A3, B3);
    vector<vector<int>> strassen3 = strassenMultiply(A3, B3);

    cout << "Standard Result:" << endl;
    printMatrix(standard3);
    cout << "Strassen's Result:" << endl;
    printMatrix(strassen3);

    cout << "Matrices Match: " << (compareMatrices(standard3, strassen3) ? " YES" : " NO") << endl << endl;

    // ===== TEST CASE 4: 1x1 Matrix =====
    cout << "TEST CASE 4: 1x1 Matrix Multiplication" << endl;
    cout << "--------------------------------------" << endl;

    vector<vector<int>> A1 = { {5} };
    vector<vector<int>> B1 = { {7} };
    vector<vector<int>> strassen1 = strassenMultiply(A1, B1);

    cout << "5 × 7 = " << strassen1[0][0] << endl << endl;

    // ===== PERFORMANCE COMPARISON =====
    cout << "PERFORMANCE COMPARISON" << endl;
    cout << "======================" << endl << endl;

    cout << left << setw(10) << "Size"
        << setw(18) << "Standard (μs)"
        << setw(18) << "Strassen (μs)"
        << setw(15) << "Speedup" << endl;
    cout << string(60, '-') << endl;

    vector<int> sizes = { 2, 4, 8, 16, 32, 64, 128 };

    for (int size : sizes) {
        // Skip large sizes for standard multiplication
        if (size > 32) {
            cout << left << setw(10) << size
                << setw(18) << "N/A"
                << setw(18) << "..."
                << setw(15) << "..." << endl;
            continue;
        }

        auto A = generateRandomMatrix(size, 0, 5);
        auto B = generateRandomMatrix(size, 0, 5);

        long long timeStandard = measureTime([&]() {
            auto result = standardMultiply(A, B);
            });

        long long timeStrassen = measureTime([&]() {
            auto result = strassenMultiply(A, B);
            });

        double speedup = (double)timeStandard / timeStrassen;

        cout << left << setw(10) << size
            << setw(18) << timeStandard
            << setw(18) << timeStrassen
            << setw(15) << fixed << setprecision(2) << speedup << "x" << endl;
    }

    cout << endl;

    // ===== VERIFICATION WITH MULTIPLE RANDOM TESTS =====
    cout << "VERIFICATION: Multiple Random Tests" << endl;
    cout << "===================================" << endl;

    srand(time(nullptr));
    int numTests = 10;
    bool allPassed = true;

    for (int test = 0; test < numTests; test++) {
        int size = rand() % 4 + 1; // 1x1 to 4x4
        auto A = generateRandomMatrix(size, 0, 9);
        auto B = generateRandomMatrix(size, 0, 9);

        auto standard = standardMultiply(A, B);
        auto strassen = strassenMultiply(A, B);

        bool match = compareMatrices(standard, strassen);
        allPassed = allPassed && match;

        cout << "Test " << setw(2) << (test + 1) << ": " << size << "x" << size
            << " - " << (match ? "✓ PASS" : "✗ FAIL") << endl;
    }

    cout << "\nAll Tests: " << (allPassed ? "PASSED" : "FAILED") << endl << endl;

    // ===== EDGE CASES =====
    cout << "EDGE CASES" << endl;
    cout << "==========" << endl << endl;

    // Empty matrix
    cout << "1. Empty Matrix:" << endl;
    vector<vector<int>> emptyA = {};
    vector<vector<int>> emptyB = {};
    auto emptyResult = strassenMultiply(emptyA, emptyB);
    cout << "   Size: " << emptyResult.size() << "x" << (emptyResult.empty() ? 0 : emptyResult[0].size()) << endl << endl;

    // Zero matrix
    cout << "2. Zero Matrix:" << endl;
    vector<vector<int>> zeroA = { {0, 0}, {0, 0} };
    vector<vector<int>> testB = { {1, 2}, {3, 4} };
    auto zeroResult = strassenMultiply(zeroA, testB);
    printMatrix(zeroResult, "   Zero × Matrix");

    // Identity matrix
    cout << "3. Identity Matrix:" << endl;
    vector<vector<int>> identity = { {1, 0}, {0, 1} };
    vector<vector<int>> testMat = { {2, 3}, {4, 5} };
    auto identityResult = strassenMultiply(identity, testMat);
    printMatrix(identityResult, "   Identity × Matrix");

    bool identityCorrect = compareMatrices(identityResult, testMat);
    cout << "   Identity property holds: " << (identityCorrect ? "YES" : " NO") << endl;

    return 0;
}