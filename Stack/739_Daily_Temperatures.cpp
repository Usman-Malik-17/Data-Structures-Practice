#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 739. Daily Temperatures
// Link     : https://leetcode.com/problems/daily-temperatures/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given an array of daily temperatures, return an array where
// each element represents how many days to wait for a warmer day.
// If no warmer day exists, return 0 for that day.
//
// Key Trick:
// Instead of storing {value, index} pair in stack, store only
// the index — value can be accessed via temperatures[st.top()].
// This halves the stack space and keeps code cleaner.
//
// Right to left traversal ensures future temperatures are already
// in stack when we process current day.
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach: Monotonic Stack (Index Based)
    // Time Complexity  : O(n) - each element pushed/popped once
    // Space Complexity : O(n) - stack size
    // ============================================================
    int check(stack<int>& st, vector<int>& temp, int i) {
        while (!st.empty() && temp[st.top()] <= temp[i]) {
            st.pop();
        }
        int ans = st.empty() ? 0 : st.top() - i;
        st.push(i);
        return ans;
    }

    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        stack<int> st;
        vector<int> ans(n, 0);

        for (int i = n - 1; i >= 0; i--) {
            ans[i] = check(st, temperatures, i);
        }
        return ans;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> temp1 = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> ans1 = sol.dailyTemperatures(temp1);
    cout << "Test 1: ";
    for (int x : ans1) cout << x << " ";
    cout << endl;
    // Expected: 1 1 4 2 1 1 0 0

    vector<int> temp2 = {30, 40, 50, 60};
    vector<int> ans2 = sol.dailyTemperatures(temp2);
    cout << "Test 2: ";
    for (int x : ans2) cout << x << " ";
    cout << endl;
    // Expected: 1 1 1 0

    vector<int> temp3 = {30, 60, 90};
    vector<int> ans3 = sol.dailyTemperatures(temp3);
    cout << "Test 3: ";
    for (int x : ans3) cout << x << " ";
    cout << endl;
    // Expected: 1 1 0

    return 0;
}