/*
 * ============================================================
 *  UNIQUE PATHS — Dynamic Programming (LeetCode #62)
 * ============================================================
 *  Problem:
 *    A robot is on an m x n grid at top-left corner (0,0).
 *    It wants to reach bottom-right corner (m-1, n-1).
 *    It can only move RIGHT or DOWN at any point.
 *    Return the number of unique paths.
 *
 *  Recurrence:
 *    paths(i, j) = paths(i-1, j)   // came from above
 *                + paths(i, j-1)   // came from left
 *
 *  Base Cases:
 *    (0, 0) → 1   (origin, 1 way to be here)
 *    (i, j) where i<0 or j<0 → 0   (out of bounds)
 *
 *  Approaches covered:
 *    1. Pure Recursion     — O(2^(m+n)) time | O(m+n)   space (stack)
 *    2. Memoization        — O(m*n)     time | O(m*n)   space
 *    3. Tabulation         — O(m*n)     time | O(m*n)   space
 *    4. Space Optimization — O(m*n)     time | O(n)     space
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {

    // -------------------------------------------------------
    //  1. PURE RECURSION
    //     Start from (m-1, n-1), go towards (0, 0)
    //     At each cell, come from above or from left
    //     TC: O(2^(m+n))  |  SC: O(m+n) recursion stack
    // -------------------------------------------------------
    int sol(int m, int n) {
        // Base case: reached origin — 1 valid path
        if (m == 0 && n == 0) return 1;

        // Base case: out of bounds — 0 paths
        if (m < 0 || n < 0) return 0;

        // Came from above + came from left
        return sol(m - 1, n) + sol(m, n - 1);
    }

    // -------------------------------------------------------
    //  2. MEMOIZATION  (Recursion + Caching)
    //     Store results in dp[i][j] to avoid recomputation
    //     TC: O(m*n)  |  SC: O(m*n) table + O(m+n) stack
    // -------------------------------------------------------
    int memSol(int m, int n, vector<vector<int>>& dp) {
        // Base case: reached origin
        if (m == 0 && n == 0) return 1;

        // Base case: out of bounds
        if (m < 0 || n < 0) return 0;

        // Return cached result if already computed
        if (dp[m][n] != -1) return dp[m][n];

        // Came from above + came from left
        return dp[m][n] = memSol(m - 1, n, dp) + memSol(m, n - 1, dp);
    }

    // -------------------------------------------------------
    //  3. TABULATION  (Bottom-Up DP)
    //     Convert memoization to iterative:
    //       • Base case  →  dp[0][0] = 1
    //       • Recursion  →  nested loops (i: 0→m, j: 0→n)
    //       • Return     →  dp[m-1][n-1]
    //     TC: O(m*n)  |  SC: O(m*n)
    // -------------------------------------------------------
    int tabSol(int m, int n, vector<vector<int>>& dp) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // Base case: origin has exactly 1 path
                if (i == 0 && j == 0) {
                    dp[i][j] = 1;
                    continue;
                }
                int up   = (i > 0) ? dp[i-1][j] : 0;  // from above
                int left = (j > 0) ? dp[i][j-1] : 0;  // from left
                dp[i][j] = up + left;
            }
        }
        return dp[m-1][n-1];
    }

    // -------------------------------------------------------
    //  4. SPACE OPTIMIZATION
    //     Observation: only need previous row (dp[i-1])
    //     to compute current row (dp[i])
    //       prev = previous row
    //       curr = current row being filled
    //     TC: O(m*n)  |  SC: O(n)
    // -------------------------------------------------------
    int spaceOptimization(int m, int n) {
        vector<int> prev(n, 0);  // previous row
        vector<int> curr(n, 0);  // current row

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // Base case: origin
                if (i == 0 && j == 0) {
                    curr[j] = 1;
                    continue;
                }
                int up   = prev[j];                    // from above (previous row)
                int left = (j > 0) ? curr[j-1] : 0;   // from left (same row)
                curr[j] = up + left;
            }
            prev = curr;  // current row becomes previous for next iteration
        }
        return prev[n-1];
    }

public:
    // -------------------------------------------------------
    //  DRIVER — change the call to test different approaches
    // -------------------------------------------------------
    int uniquePaths(int m, int n) {
        // Memoization needs dp table initialised to -1
        vector<vector<int>> dp(m, vector<int>(n, -1));

        // Uncomment the approach you want to run:
        // return sol(m-1, n-1);                  // Pure Recursion
        // return memSol(m-1, n-1, dp);           // Memoization
        // return tabSol(m, n, dp);               // Tabulation
        return spaceOptimization(m, n);           // Space Optimized ✅
    }
};

// -------------------------------------------------------
//  MAIN — test with sample inputs
// -------------------------------------------------------
int main() {
    Solution sol;

    // Test 1: 3x7 grid → Expected: 28
    cout << "3x7: " << sol.uniquePaths(3, 7) << endl;

    // Test 2: 3x2 grid → Expected: 3
    cout << "3x2: " << sol.uniquePaths(3, 2) << endl;

    // Test 3: 1x1 grid → Expected: 1
    cout << "1x1: " << sol.uniquePaths(1, 1) << endl;

    return 0;
}