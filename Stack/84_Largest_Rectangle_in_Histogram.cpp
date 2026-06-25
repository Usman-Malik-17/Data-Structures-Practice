#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 84. Largest Rectangle in Histogram
// Link     : https://leetcode.com/problems/largest-rectangle-in-histogram/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given an array of heights representing a histogram where each
// bar has width 1, find the largest rectangle that can be formed.
//
// Key Insight:
// For each bar, the largest rectangle it can form extends left
// until a shorter bar is found, and right until a shorter bar
// is found. Area = height * (right_boundary - left_boundary - 1)
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Previous Smallest + Next Smallest Index
    // Time Complexity  : O(n) - three separate passes
    // Space Complexity : O(n) - psi, nsi arrays + stack
    //
    // Explanation:
    // For each bar i, find:
    //   psi[i] = index of previous smaller height (left boundary)
    //   nsi[i] = index of next smaller height (right boundary)
    // Width = nsi[i] - psi[i] - 1
    // Area  = width * heights[i]
    //
    // Why >= on left and > on right?
    // To avoid double counting equal height bars.
    // Last equal element computes full width, others get smaller.
    // ============================================================

    int prevSmallestIndexHelper(stack<int>& st, vector<int>& heights, int index) {
        while (!st.empty() && heights[st.top()] >= heights[index]) {
            st.pop();
        }
        int ans = st.empty() ? -1 : st.top();
        st.push(index);
        return ans;
    }

    void prevSmallestIndex(vector<int>& heights, vector<int>& psi) {
        stack<int> st;
        for (int i = 0; i < heights.size(); i++) {
            psi[i] = prevSmallestIndexHelper(st, heights, i);
        }
    }

    int nextSmallestIndexHelper(stack<int>& st, vector<int>& heights, int index) {
        while (!st.empty() && heights[st.top()] > heights[index]) {
            st.pop();
        }
        int ans = st.empty() ? heights.size() : st.top();
        st.push(index);
        return ans;
    }

    void nextSmallestIndex(vector<int>& heights, vector<int>& nsi) {
        stack<int> st;
        for (int i = heights.size() - 1; i >= 0; i--) {
            nsi[i] = nextSmallestIndexHelper(st, heights, i);
        }
    }

    int largestRectangleAreaBrute(vector<int>& heights) {
        int n = heights.size();
        vector<int> psi(n, -1);
        vector<int> nsi(n, n);
        prevSmallestIndex(heights, psi);
        nextSmallestIndex(heights, nsi);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int sol = (nsi[i] - psi[i] - 1) * heights[i];
            ans = max(sol, ans);
        }
        return ans;
    }

    // ============================================================
    // Approach 2: One Pass Monotonic Stack (Optimal)
    // Time Complexity  : O(n) - single pass
    // Space Complexity : O(n) - stack only, no extra arrays
    //
    // Explanation:
    // Maintain a monotonic increasing stack of indexes.
    // When a smaller bar is found at index i:
    //   - Pop the taller bar (it cant extend further right)
    //   - nse = i (current index is right boundary)
    //   - pse = new stack top (left boundary)
    //   - Compute area immediately
    // After loop, remaining bars in stack have no right boundary
    // so nse = heights.size() for them.
    //
    // Advantage over Approach 1:
    // No need for psi/nsi arrays — boundaries computed on the fly!
    // ============================================================

    void helper(vector<int>& heights, stack<int>& st, int i, int& ans) {
        while (!st.empty() && heights[st.top()] > heights[i]) {
            int val = heights[st.top()];
            st.pop();
            int nse = i;
            int pse = st.empty() ? -1 : st.top();
            ans = max(ans, (nse - pse - 1) * val);
        }
        st.push(i);
    }

    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        int ans = 0;

        for (int i = 0; i < heights.size(); i++) {
            helper(heights, st, i, ans);
        }

        // Remaining bars in stack have no right boundary
        int nse = heights.size();
        while (!st.empty()) {
            int val = heights[st.top()];
            st.pop();
            int pse = st.empty() ? -1 : st.top();
            ans = max(ans, (nse - pse - 1) * val);
        }
        return ans;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> heights1 = {2, 1, 5, 6, 2, 3};
    cout << "Test 1: " << sol.largestRectangleArea(heights1) << endl;
    // Expected: 10

    vector<int> heights2 = {2, 4};
    cout << "Test 2: " << sol.largestRectangleArea(heights2) << endl;
    // Expected: 4

    vector<int> heights3 = {1, 1, 1, 1};
    cout << "Test 3: " << sol.largestRectangleArea(heights3) << endl;
    // Expected: 4

    vector<int> heights4 = {6, 2, 5, 4, 5, 1, 6};
    cout << "Test 4: " << sol.largestRectangleArea(heights4) << endl;
    // Expected: 12

    return 0;
}