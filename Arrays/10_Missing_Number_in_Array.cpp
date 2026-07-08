#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : Missing Number in Array
// Link     : https://www.geeksforgeeks.org/find-the-missing-number/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Array of size n-1 contains distinct integers from 1 to n.
// Find the missing element.
//
// Example:
// arr = [1,2,3,5], n=5
// Expected sum = 5*6/2 = 15
// Actual sum   = 1+2+3+5 = 11
// Missing      = 15-11 = 4 ✅
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Brute Force — Linear Search
    // Time Complexity  : O(n^2) - for each number linear search
    // Space Complexity : O(1)
    // ============================================================
    int missingNumBrute(vector<int>& arr) {
        for (int i = 1; i <= arr.size() + 1; i++) {
            bool flag = false;
            for (int j = 0; j < arr.size(); j++) {
                if (arr[j] == i) {
                    flag = true;
                    break;
                }
            }
            if (!flag) return i;
        }
        return -1;
    }

    // ============================================================
    // Approach 2: Hashing — Boolean Array
    // Time Complexity  : O(n) - two passes
    // Space Complexity : O(n) - temp array
    // ============================================================
    int missingNumHash(vector<int>& arr) {
        vector<int> temp(arr.size() + 2, 0);
        for (auto i : arr) temp[i] = 1;
        for (int i = 1; i < temp.size(); i++) {
            if (temp[i] == 0) return i;
        }
        return -1;
    }

    // ============================================================
    // Approach 3: Sum Formula (Optimal)
    // Time Complexity  : O(n) - single pass
    // Space Complexity : O(1) - no extra space
    //
    // Key Trick:
    // Sum of 1 to n = n*(n+1)/2
    // Missing = Expected Sum - Actual Sum
    //
    // Why long long?
    // n can be 10^6 → n*(n+1)/2 can overflow int!
    //
    // Example:
    // arr=[1,2,3,5], n=5
    // Expected = 5*6/2 = 15
    // Actual   = 1+2+3+5 = 11
    // Missing  = 15-11 = 4 ✅
    // ============================================================
    int missingNum(vector<int>& arr) {
        long long n = arr.size() + 1;
        long long sum = n * (n + 1) / 2;  // expected sum
        for (auto i : arr) sum -= i;       // subtract actual
        return sum;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> arr1 = {1, 2, 3, 5};
    cout << "Test 1: " << sol.missingNum(arr1) << endl;
    // Expected: 4

    vector<int> arr2 = {8, 2, 4, 5, 3, 7, 1};
    cout << "Test 2: " << sol.missingNum(arr2) << endl;
    // Expected: 6

    vector<int> arr3 = {1};
    cout << "Test 3: " << sol.missingNum(arr3) << endl;
    // Expected: 2

    return 0;
}