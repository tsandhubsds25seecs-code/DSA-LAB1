#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Naive pattern matching with starting position
int findFirstOccurrence(const string& text, const string& pattern, int startPos = 0) {
    int textLen = text.length();
    int patternLen = pattern.length();

    // Edge case: Empty pattern
    if (patternLen == 0) {
        return startPos < textLen ? startPos : -1;
    }

    // Edge case: Pattern longer than text
    if (patternLen > textLen) {
        return -1;
    }

    // Edge case: Start position out of bounds
    if (startPos < 0 || startPos >= textLen) {
        return -1;
    }

    // Slide pattern over text starting from startPos
    for (int i = startPos; i <= textLen - patternLen; i++) {
        int j;
        // Check for pattern match at position i
        for (j = 0; j < patternLen; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        // If pattern matched completely
        if (j == patternLen) {
            return i;
        }
    }

    return -1;  // Pattern not found
}

// Find all occurrences
vector<int> findAllOccurrences(const string& text, const string& pattern) {
    vector<int> indices;
    int startPos = 0;

    while (true) {
        int index = findFirstOccurrence(text, pattern, startPos);
        if (index == -1) {
            break;
        }
        indices.push_back(index);
        startPos = index + 1;  // Move past the last found occurrence
    }

    return indices;
}

void printAllResults(const string& text, const string& pattern, const vector<int>& indices) {
    cout << "Text: \"" << text << "\"" << endl;
    cout << "Pattern: \"" << pattern << "\"" << endl;
    if (indices.empty()) {
        cout << "Result: Pattern not found" << endl;
    }
    else {
        cout << "Result: Pattern found at indices: ";
        for (int idx : indices) {
            cout << idx << " ";
        }
        cout << endl;
    }
    cout << "------------------------" << endl;
}

int main() {
    // Test all occurrences
    cout << "=== Finding All Occurrences ===" << endl;
    string text = "ababababa";
    string pattern = "aba";
    vector<int> allIndices = findAllOccurrences(text, pattern);
    printAllResults(text, pattern, allIndices);

    // Another example with overlapping patterns
    cout << "\n=== Overlapping Patterns ===" << endl;
    string text2 = "aaaaaa";
    string pattern2 = "aa";
    vector<int> indices2 = findAllOccurrences(text2, pattern2);
    printAllResults(text2, pattern2, indices2);

    return 0;
}