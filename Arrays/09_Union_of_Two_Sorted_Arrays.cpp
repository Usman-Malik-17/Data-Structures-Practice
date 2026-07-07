#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : Union of Two Sorted Arrays
// Link     : https://www.geeksforgeeks.org/union-and-intersection-of-two-sorted-arrays-2/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given two sorted arrays, return union — distinct elements
// from both arrays in sorted order.
//
// Example:
// a = [1,2,3,4,5], b = [1,2,3,6,7]
// Output: [1,2,3,4,5,6,7]
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Set (Brute Force)
    // Time Complexity  : O((m+n) log(m+n)) - set insertion
    // Space Complexity : O(m+n) - set size
    // ============================================================
    vector<int> findUnionBrute(vector<int>& a, vector<int>& b) {
        set<int> s;
        for (auto i : a) s.insert(i);
        for (auto i : b) s.insert(i);

        vector<int> ans;
        for (auto i : s) ans.push_back(i);
        return ans;
    }

    // ============================================================
    // Approach 2: Two Pointers (Optimal)
    // Time Complexity  : O(m+n) - single pass both arrays
    // Space Complexity : O(m+n) - result array
    //
    // Key Trick:
    // Since arrays are sorted, use two pointers i and j.
    // Compare a[i] and b[j]:
    //   a[i] < b[j] → add a[i], skip duplicates in a
    //   a[i] > b[j] → add b[j], skip duplicates in b
    //   a[i] == b[j] → add once, skip duplicates in both
    // After loop — add remaining elements
    //
    // helper() — skips duplicates by finding next different element
    //
    // Example:
    // a=[1,2,2,3], b=[2,3,4]
    // i=0,j=0: 1<2 → add 1, i→1
    // i=1,j=0: 2==2 → add 2, i→3, j→1
    // i=3,j=1: 3==3 → add 3, i→4, j→2
    // i=4: loop ends, add b[2]=4
    // Output: [1,2,3,4] ✅
    // ============================================================

    // Helper: find next non-duplicate index
    int helper(int index, vector<int>& arr) {
        for (int i = index + 1; i < arr.size(); i++) {
            if (arr[i] != arr[i - 1]) return i;
        }
        return arr.size();
    }

    vector<int> findUnion(vector<int>& a, vector<int>& b) {
        int i = 0, j = 0;
        vector<int> ans;

        while (i < a.size() && j < b.size()) {
            if (a[i] < b[j]) {
                ans.push_back(a[i]);
                i = helper(i, a);       // skip duplicates in a
            } else if (a[i] > b[j]) {
                ans.push_back(b[j]);
                j = helper(j, b);       // skip duplicates in b
            } else {
                ans.push_back(a[i]);
                i = helper(i, a);       // skip duplicates in both
                j = helper(j, b);
            }
        }

        // Remaining elements of a
        while (i < a.size()) {
            ans.push_back(a[i]);
            i = helper(i, a);
        }

        // Remaining elements of b
        while (j < b.size()) {
            ans.push_back(b[j]);
            j = helper(j, b);
        }

        return ans;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> a1 = {1, 2, 3, 4, 5};
    vector<int> b1 = {1, 2, 3, 6, 7};
    vector<int> ans1 = sol.findUnion(a1, b1);
    cout << "Test 1: ";
    for (int x : ans1) cout << x << " ";
    cout << endl;
    // Expected: 1 2 3 4 5 6 7

    vector<int> a2 = {2, 2, 3, 4, 5};
    vector<int> b2 = {1, 1, 2, 3, 4};
    vector<int> ans2 = sol.findUnion(a2, b2);
    cout << "Test 2: ";
    for (int x : ans2) cout << x << " ";
    cout << endl;
    // Expected: 1 2 3 4 5

    vector<int> a3 = {1, 1, 1, 1, 1};
    vector<int> b3 = {2, 2, 2, 2, 2};
    vector<int> ans3 = sol.findUnion(a3, b3);
    cout << "Test 3: ";
    for (int x : ans3) cout << x << " ";
    cout << endl;
    // Expected: 1 2

    return 0;
}