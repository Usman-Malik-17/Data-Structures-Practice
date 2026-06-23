#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 907. Sum of Subarray Minimums
// Link     : https://leetcode.com/problems/sum-of-subarray-minimums/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Find sum of minimums of all contiguous subarrays.
//
// Key Trick — Contribution Technique:
// Instead of finding min of every subarray (O(n²) or worse),
// calculate how many subarrays each element is the minimum of.
//
// For element at index i:
//   - Find Previous Minimum Element (PME) index — first smaller to left
//   - Find Next Minimum Equal Element (NMEE) index — first smaller/equal to right
//   - Subarrays where arr[i] is minimum = (i - pme[i]) * (nmee[i] - i)
//   - Contribution = arr[i] * left_count * right_count
//
// Why <= on right side?
// To avoid double counting when equal elements exist.
// Left uses strict <, Right uses <= 
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Helper: Previous Minimum Element Index (strict less than)
    // ============================================================
    int prevMinHelper(stack<int>& st, vector<int>& arr, int index) {
        while (!st.empty() && arr[st.top()] >= arr[index]) {
            st.pop();
        }
        int ans = st.empty() ? -1 : st.top();
        st.push(index);
        return ans;
    }

    void prevMinElementIndex(vector<int>& pme, vector<int>& arr) {
        stack<int> st;
        for (int i = 0; i < arr.size(); i++) {
            pme[i] = prevMinHelper(st, arr, i);
        }
    }

    // ============================================================
    // Helper: Next Minimum Equal Element Index (less than or equal)
    // ============================================================
    int nextMinEqualHelper(stack<int>& st, vector<int>& arr, int index) {
        while (!st.empty() && arr[st.top()] > arr[index]) {
            st.pop();
        }
        int ans = st.empty() ? arr.size() : st.top();
        st.push(index);
        return ans;
    }

    void nextMinEqualElementIndex(vector<int>& nmee, vector<int>& arr) {
        stack<int> st;
        for (int i = arr.size() - 1; i >= 0; i--) {
            nmee[i] = nextMinEqualHelper(st, arr, i);
        }
    }

    // ============================================================
    // Approach: Contribution Technique (Monotonic Stack)
    // Time Complexity  : O(n) - each element pushed/popped once
    // Space Complexity : O(n) - pme, nmee arrays + stack
    // ============================================================
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        vector<int> pme(n);
        vector<int> nmee(n);
        const int MOD = 1e9 + 7;

        prevMinElementIndex(pme, arr);
        nextMinEqualElementIndex(nmee, arr);

        long long sum = 0;
        for (int i = 0; i < n; i++) {
            long long left  = i - pme[i];
            long long right = nmee[i] - i;
            sum = (sum + (long long)arr[i] * left * right) % MOD;
        }
        return sum;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> arr1 = {3, 1, 2, 4};
    cout << "Test 1: " << sol.sumSubarrayMins(arr1) << endl;
    // Expected: 17

    vector<int> arr2 = {11, 81, 94, 43, 3};
    cout << "Test 2: " << sol.sumSubarrayMins(arr2) << endl;
    // Expected: 444

    return 0;
}