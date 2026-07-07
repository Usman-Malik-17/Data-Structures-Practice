#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : Linear Search
// Link     : https://www.geeksforgeeks.org/linear-search/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given array and element x, return index of first occurrence
// of x. If not found, return -1.
//
// Example:
// arr = [1,2,3,4], x = 3
// i=0: 1 != 3
// i=1: 2 != 3
// i=2: 3 == 3 → return 2 ✅
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach: Linear Search
    // Time Complexity  : O(n) - worst case traverse full array
    // Space Complexity : O(1) - no extra space
    // ============================================================
    int search(vector<int>& arr, int x) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == x) return i;
        }
        return -1;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> arr1 = {1, 2, 3, 4};
    cout << "Test 1: " << sol.search(arr1, 3) << endl;
    // Expected: 2

    vector<int> arr2 = {10, 8, 30, 4, 5};
    cout << "Test 2: " << sol.search(arr2, 5) << endl;
    // Expected: 4

    vector<int> arr3 = {10, 8, 30};
    cout << "Test 3: " << sol.search(arr3, 6) << endl;
    // Expected: -1

    vector<int> arr4 = {5, 5, 5};
    cout << "Test 4: " << sol.search(arr4, 5) << endl;
    // Expected: 0

    return 0;
}