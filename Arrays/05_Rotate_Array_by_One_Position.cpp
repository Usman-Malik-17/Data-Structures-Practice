#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : Rotate Array by One Position (Clockwise)
// Link     : https://www.geeksforgeeks.org/array-rotation/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Rotate array by one position clockwise — last element comes
// to front, all others shift one position to the right.
//
// Example:
// arr = [1, 2, 3, 4, 5]
// temp = 5 (save last element)
// Shift right: [1, 1, 2, 3, 4]
// Place temp:  [5, 1, 2, 3, 4] ✅
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Brute Force — Extra Array
    // Time Complexity  : O(n)
    // Space Complexity : O(n) - extra array
    // ============================================================
    void rotateBrute(vector<int>& arr) {
        int n = arr.size();
        vector<int> temp(n);
        temp[0] = arr[n - 1];
        for (int i = 1; i < n; i++) {
            temp[i] = arr[i - 1];
        }
        arr = temp;
    }

    // ============================================================
    // Approach 2: Single Pass (Optimal)
    // Time Complexity  : O(n) - single pass
    // Space Complexity : O(1) - only one temp variable
    //
    // Key Trick:
    // Save last element in temp.
    // Shift all elements one position to the right (right to left).
    // Place temp at index 0.
    //
    // Example:
    // arr = [1, 2, 3, 4, 5]
    // temp = 5
    // i=3: arr[4] = arr[3] → [1,2,3,4,4]
    // i=2: arr[3] = arr[2] → [1,2,3,3,4]
    // i=1: arr[2] = arr[1] → [1,2,2,3,4]
    // i=0: arr[1] = arr[0] → [1,1,2,3,4]
    // arr[0] = 5           → [5,1,2,3,4] ✅
    // ============================================================
    void rotate(vector<int>& arr) {
        int n = arr.size();
        int temp = arr[n - 1];  // save last element
        for (int i = n - 2; i >= 0; i--) {
            arr[i + 1] = arr[i];  // shift right
        }
        arr[0] = temp;  // place last at front
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> arr1 = {1, 2, 3, 4, 5};
    sol.rotate(arr1);
    cout << "Test 1: ";
    for (int x : arr1) cout << x << " ";
    cout << endl;
    // Expected: 5 1 2 3 4

    vector<int> arr2 = {9, 8, 7, 6, 4, 2, 1, 3};
    sol.rotate(arr2);
    cout << "Test 2: ";
    for (int x : arr2) cout << x << " ";
    cout << endl;
    // Expected: 3 9 8 7 6 4 2 1

    vector<int> arr3 = {1};
    sol.rotate(arr3);
    cout << "Test 3: ";
    for (int x : arr3) cout << x << " ";
    cout << endl;
    // Expected: 1

    return 0;
}