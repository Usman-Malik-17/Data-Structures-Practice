#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 85. Maximal Rectangle
// Link     : https://leetcode.com/problems/maximal-rectangle/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given a binary matrix of 0s and 1s, find the largest rectangle
// containing only 1s and return its area.
//
// Key Trick — Reduce to Histogram Problem:
// Treat each row as the base of a histogram.
// For each row, build a heights array where:
//   heights[j] = number of consecutive 1s ending at current row
//   heights[j] = 0 if matrix[i][j] == '0' (reset)
//
// Then apply Largest Rectangle in Histogram on each row's heights.
// Maximum across all rows is the answer.
//
// Example:
// matrix = [["1","0","1","0","0"],
//           ["1","0","1","1","1"],
//           ["1","1","1","1","1"],
//           ["1","0","0","1","0"]]
//
// Row 0 heights: [1,0,1,0,0]
// Row 1 heights: [2,0,2,1,1]
// Row 2 heights: [3,1,3,2,2] → max rect = 6
// Row 3 heights: [4,0,0,3,0]
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Helper: One Pass Monotonic Stack for Histogram
    // ============================================================
    void histHelper(stack<int>& st, int index, vector<int>& arr, int& maxi) {
        while (!st.empty() && arr[st.top()] > arr[index]) {
            int elem = arr[st.top()];
            st.pop();
            int pmi = st.empty() ? -1 : st.top();
            int nmi = index;
            maxi = max(maxi, (nmi - pmi - 1) * elem);
        }
        st.push(index);
    }

    // ============================================================
    // Helper: Largest Rectangle in Histogram
    // Time Complexity  : O(m) - each element pushed/popped once
    // Space Complexity : O(m) - stack size
    // ============================================================
    int maxRectInHist(vector<int>& arr) {
        int maxi = 0;
        stack<int> st;

        for (int i = 0; i < arr.size(); i++) {
            histHelper(st, i, arr, maxi);
        }

        // Remaining bars have no right boundary
        int nmi = arr.size();
        while (!st.empty()) {
            int elem = arr[st.top()];
            st.pop();
            int pmi = st.empty() ? -1 : st.top();
            maxi = max(maxi, (nmi - pmi - 1) * elem);
        }
        return maxi;
    }

    // ============================================================
    // Helper: Build histogram heights row by row
    // '1' -> increment height, '0' -> reset to 0
    // ============================================================
    void initializationHelper(vector<int>& arr, vector<char>& matrix) {
        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[i] != '0') {
                arr[i] += 1;
            } else {
                arr[i] = 0;
            }
        }
    }

    // ============================================================
    // Approach: Row by Row Histogram (Monotonic Stack)
    // Time Complexity  : O(n * m) - n rows, each row O(m)
    // Space Complexity : O(m) - heights array + stack
    // ============================================================
    int maximalRectangle(vector<vector<char>>& matrix) {
        vector<int> arr(matrix[0].size(), 0);
        int maxi = 0;

        for (int i = 0; i < matrix.size(); i++) {
            initializationHelper(arr, matrix[i]);
            maxi = max(maxi, maxRectInHist(arr));
        }
        return maxi;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<vector<char>> matrix1 = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    };
    cout << "Test 1: " << sol.maximalRectangle(matrix1) << endl;
    // Expected: 6

    vector<vector<char>> matrix2 = {{'0'}};
    cout << "Test 2: " << sol.maximalRectangle(matrix2) << endl;
    // Expected: 0

    vector<vector<char>> matrix3 = {{'1'}};
    cout << "Test 3: " << sol.maximalRectangle(matrix3) << endl;
    // Expected: 1

    return 0;
}