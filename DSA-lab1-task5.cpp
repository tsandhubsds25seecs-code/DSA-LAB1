#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

// Function to find the mode (most frequent element) using HashMap
vector<int> findMode(const vector<int>& arr) {
    vector<int> modes;

    // Edge case: Empty array
    if (arr.empty()) {
        return modes;
    }

    // Count frequencies using unordered_map
    unordered_map<int, int> frequency;
    int maxFreq = 0;

    for (int num : arr) {
        frequency[num]++;
        maxFreq = max(maxFreq, frequency[num]);
    }

    // Find all elements with maximum frequency
    for (const auto& pair : frequency) {
        if (pair.second == maxFreq) {
            modes.push_back(pair.first);
        }
    }

    return modes;
}

// Alternative implementation using sorting
vector<int> findModeSorting(vector<int> arr) {
    vector<int> modes;

    if (arr.empty()) {
        return modes;
    }

    sort(arr.begin(), arr.end());

    int maxFreq = 0;
    int currentFreq = 1;

    for (size_t i = 1; i <= arr.size(); i++) {
        if (i < arr.size() && arr[i] == arr[i - 1]) {
            currentFreq++;
        }
        else {
            if (currentFreq > maxFreq) {
                maxFreq = currentFreq;
                modes.clear();
                modes.push_back(arr[i - 1]);
            }
            else if (currentFreq == maxFreq) {
                modes.push_back(arr[i - 1]);
            }
            currentFreq = 1;
        }
    }

    return modes;
}

// Function to print array
void printArray(const vector<int>& arr) {
    cout << "[";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << "]";
}

// Function to print mode results
void printModeResult(const vector<int>& arr, const vector<int>& modes) {
    cout << "Array: ";
    printArray(arr);
    cout << endl;

    if (modes.empty()) {
        cout << "Mode: Array is empty" << endl;
    }
    else if (modes.size() == 1) {
        cout << "Mode: " << modes[0] << " (unique mode)" << endl;
        cout << "Frequency: " << count(arr.begin(), arr.end(), modes[0]) << " times" << endl;
    }
    else {
        cout << "Modes: ";
        printArray(modes);
        cout << " (multiple modes)" << endl;
        cout << "Frequency: " << count(arr.begin(), arr.end(), modes[0]) << " times each" << endl;
    }
    cout << "------------------------" << endl;
}

int main() {
    cout << "=== TASK 6: Histogram Analysis (Mode of Array) ===" << endl << endl;

    // Test Case 1: Array with unique mode
    cout << "Test Case 1: Array with unique mode" << endl;
    vector<int> arr1 = { 1, 2, 3, 2, 4, 2, 5 };
    vector<int> modes1 = findMode(arr1);
    printModeResult(arr1, modes1);

    // Test Case 2: Array with multiple modes
    cout << "Test Case 2: Array with multiple modes" << endl;
    vector<int> arr2 = { 1, 2, 2, 3, 3, 4 };
    vector<int> modes2 = findMode(arr2);
    printModeResult(arr2, modes2);

    // Test Case 3: Empty array
    cout << "Test Case 3: Empty array" << endl;
    vector<int> arr3 = {};
    vector<int> modes3 = findMode(arr3);
    printModeResult(arr3, modes3);

    // Additional Test Cases
    cout << "\n=== Additional Test Cases ===" << endl;

    // Test Case 4: All elements same
    cout << "\nTest Case 4: All elements same" << endl;
    vector<int> arr4 = { 5, 5, 5, 5, 5 };
    vector<int> modes4 = findMode(arr4);
    printModeResult(arr4, modes4);

    // Test Case 5: Single element
    cout << "\nTest Case 5: Single element" << endl;
    vector<int> arr5 = { 42 };
    vector<int> modes5 = findMode(arr5);
    printModeResult(arr5, modes5);

    // Test Case 6: Large frequency difference
    cout << "\nTest Case 6: Large frequency difference" << endl;
    vector<int> arr6 = { 1, 1, 1, 1, 2, 3, 4, 5, 6, 7 };
    vector<int> modes6 = findMode(arr6);
    printModeResult(arr6, modes6);

    // Test Case 7: Multiple modes with equal frequency
    cout << "\nTest Case 7: Multiple modes with equal frequency" << endl;
    vector<int> arr7 = { 1, 1, 2, 2, 3, 3, 4, 5 };
    vector<int> modes7 = findMode(arr7);
    printModeResult(arr7, modes7);

    // Test Case 8: Negative numbers
    cout << "\nTest Case 8: Array with negative numbers" << endl;
    vector<int> arr8 = { -1, -2, -1, -3, -2, -2, 0 };
    vector<int> modes8 = findMode(arr8);
    printModeResult(arr8, modes8);

    // Test Case 9: Large array
    cout << "\nTest Case 9: Large array with random values" << endl;
    vector<int> arr9 = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 1, 2, 3, 1, 2, 1 };
    vector<int> modes9 = findMode(arr9);
    printModeResult(arr9, modes9);

    // Compare both implementations
    cout << "\n=== Comparing Both Implementations ===" << endl;
    vector<int> testArr = { 4, 2, 4, 3, 2, 2, 5, 4 };

    cout << "Test Array: ";
    printArray(testArr);
    cout << endl;

    vector<int> hashResult = findMode(testArr);
    vector<int> sortResult = findModeSorting(testArr);

    cout << "Hashmap method result: ";
    printArray(hashResult);
    cout << endl;

    cout << "Sorting method result: ";
    printArray(sortResult);
    cout << endl;

    bool match = (hashResult.size() == sortResult.size());
    if (match) {
        sort(hashResult.begin(), hashResult.end());
        sort(sortResult.begin(), sortResult.end());
        for (size_t i = 0; i < hashResult.size(); i++) {
            if (hashResult[i] != sortResult[i]) {
                match = false;
                break;
            }
        }
    }
    cout << "Results match: " << (match ? "YES" : "NO") << endl;

    return 0;
}