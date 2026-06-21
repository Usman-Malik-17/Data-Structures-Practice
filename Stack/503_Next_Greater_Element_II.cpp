#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 503. Next Greater Element II
// Link     : https://leetcode.com/problems/next-greater-element-ii/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given a circular integer array, return the next greater element
// for every element. Since array is circular, after the last
// element we wrap back to the first element.
//
// Key Trick — Double Array Simulation:
// Instead of actually doubling the array, we loop 2*n times
// and use (i % n) to simulate circularity. Right to left traversal
// with a monotonic stack gives us NGE in O(n).
//
// Why right to left?
// Future elements (greater ones) are processed first and stored
// in stack — so when we reach current element, stack already has
// candidates for NGE.
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Helper: Find Next Greater Element using Monotonic Stack
    // ============================================================
    int findNge(stack<int>& st, int elem) {
        while (!st.empty() && st.top() <= elem) {
            st.pop();
        }
        int ans = st.empty() ? -1 : st.top();
        st.push(elem);
        return ans;
    }

    // ============================================================
    // Approach: Monotonic Stack + Double Loop Simulation
    // Time Complexity  : O(n) - each element pushed/popped once
    // Space Complexity : O(n) - stack size
    // ============================================================
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        stack<int> st;
        vector<int> ans(n, -1);

        // Loop 2*n times to simulate circular array
        // Second half fills the stack with future candidates
        // First half gets overridden with correct NGE
        for (int i = 2 * n - 1; i >= 0; i--) {
            ans[i % n] = findNge(st, nums[i % n]);
        }

        return ans;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> nums1 = {1, 2, 1};
    vector<int> ans1 = sol.nextGreaterElements(nums1);
    cout << "Test 1: ";
    for (int x : ans1) cout << x << " ";
    cout << endl;
    // Expected: 2 -1 2

    vector<int> nums2 = {1, 2, 3, 4, 3};
    vector<int> ans2 = sol.nextGreaterElements(nums2);
    cout << "Test 2: ";
    for (int x : ans2) cout << x << " ";
    cout << endl;
    // Expected: 2 3 4 -1 4

    return 0;
}