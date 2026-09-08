// dsa-lab1-task3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

// Function to find all indices of a key in an array
vector<int> findAllIndices(int arr[], int size, int key) {
    vector<int> indices;

    // Iterate through the array
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            indices.push_back(i);
        }
    }

    return indices;
}

// Helper function to print the result
void printResult(const vector<int>& indices, int key) {
    if (indices.empty()) {
        cout << "Key " << key << " not found in the array." << endl;
    }
    else {
        cout << "Key " << key << " found at indices: ";
        for (int idx : indices) {
            cout << idx << " ";
        }
        cout << endl;
    }
}

int main() {
    // Test Case 1: Multiple occurrences
    cout << "Test Case 1: Multiple occurrences" << endl;
    int arr1[] = { 1, 2, 3, 2, 4, 2, 5 };
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    vector<int> result1 = findAllIndices(arr1, size1, 2);
    printResult(result1, 2);

    // Test Case 2: Key not present
    cout << "\nTest Case 2: Key not present" << endl;
    int arr2[] = { 1, 3, 5, 7, 9 };
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    vector<int> result2 = findAllIndices(arr2, size2, 2);
    printResult(result2, 2);

    // Test Case 3: Empty array - FIXED
    cout << "\nTest Case 3: Empty array" << endl;
    // Instead of int arr3[] = {}, use nullptr or create an empty vector
    int* arr3 = nullptr;  // Pointer to represent empty array
    int size3 = 0;        // Size is 0
    vector<int> result3 = findAllIndices(arr3, size3, 5);
    printResult(result3, 5);

    // Additional Test Case: Single occurrence
    cout << "\nTest Case 4: Single occurrence" << endl;
    int arr4[] = { 10, 20, 30, 40, 50 };
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    vector<int> result4 = findAllIndices(arr4, size4, 30);
    printResult(result4, 30);

    // Additional Test Case: All elements same
    cout << "\nTest Case 5: All elements same" << endl;
    int arr5[] = { 7, 7, 7, 7, 7 };
    int size5 = sizeof(arr5) / sizeof(arr5[0]);
    vector<int> result5 = findAllIndices(arr5, size5, 7);
    printResult(result5, 7);

    return 0;
}