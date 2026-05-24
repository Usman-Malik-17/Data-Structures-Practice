/*
 * ============================================================
 *  MINIMUM PATH SUM — Dynamic Programming (LeetCode #64)
 * ============================================================
 *  Problem:
 *    Given an m x n grid filled with non-negative numbers,
 *    find a path from top-left (0,0) to bottom-right (m-1,n-1)
 *    which minimizes the sum of all numbers along the path.
 *    You can only move RIGHT or DOWN at any point.
 *
 *  Recurrence:
 *    dp(i, j) = grid[i][j] + min(dp(i-1, j), dp(i, j-1))
 *
 *  Base Case:
 *    (0, 0) → grid[0][0]
 *    out of bounds → INT_MAX (invalid path)
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
    //     Each cell adds its own cost to the minimum of
    //     coming from above or from left
    //     TC: O(2^(m+n))  |  SC: O(m+n) recursion stack
    // -------------------------------------------------------
    int sol(vector<vector<int>>& grid, int m, int n) {
        // Out of bounds — invalid path, return INT_MAX
        if (m < 0 || n < 0) return INT_MAX;

        // Base case: reached origin
        if (m == 0 && n == 0) return grid[0][0];

        // Current cell cost + minimum of above and left
        int up   = sol(grid, m - 1, n);
        int left = sol(grid, m, n - 1);
        return grid[m][n] + min(up, left);
    }

    // -------------------------------------------------------
    //  2. MEMOIZATION  (Recursion + Caching)
    //     dp[i][j] = minimum path sum to reach cell (i,j)
    //
    //     KEY LESSON: Do NOT carry 'sum' as a parameter!
    //     If sum is carried, same cell gets cached with one
    //     sum value but reused for a different sum → WRONG!
    //     Instead: each cell stores its own minimum cost.
    //
    //     TC: O(m*n)  |  SC: O(m*n) table + O(m+n) stack
    // -------------------------------------------------------
    int memSol(vector<vector<int>>& grid, vector<vector<int>>& dp, int m, int n) {
        // Out of bounds — invalid path
        if (m < 0 || n < 0) return INT_MAX;

        // Base case: reached origin
        if (m == 0 && n == 0) return dp[m][n] = grid[0][0];

        // Return cached result if already computed
        if (dp[m][n] != -1) return dp[m][n];

        // Current cell cost + minimum of above and left
        int up   = memSol(grid, dp, m - 1, n);
        int left = memSol(grid, dp, m, n - 1);
        return dp[m][n] = grid[m][n] + min(up, left);
    }

    // -------------------------------------------------------
    //  3. TABULATION  (Bottom-Up DP)
    //     Convert memoization to iterative:
    //       • Base case  →  dp[0][0] = grid[0][0]
    //       • Recursion  →  nested loops (i: 0→m, j: 0→n)
    //       • Return     →  dp[m][n]
    //     Out of bounds handled via INT_MAX sentinel
    //     TC: O(m*n)  |  SC: O(m*n)
    // -------------------------------------------------------
    int tabSol(vector<vector<int>>& grid, vector<vector<int>>& dp, int m, int n) {
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                // Base case: origin
                if (i == 0 && j == 0) {
                    dp[i][j] = grid[i][j];
                    continue;
                }

                int up   = (i > 0) ? dp[i-1][j] : INT_MAX;  // from above
                int left = (j > 0) ? dp[i][j-1] : INT_MAX;  // from left
                dp[i][j] = grid[i][j] + min(up, left);
            }
        }
        return dp[m][n];
    }

    // -------------------------------------------------------
    //  4. SPACE OPTIMIZATION
    //     Only need previous row to compute current row
    //       dp   = previous row
    //       temp = current row being filled
    //     TC: O(m*n)  |  SC: O(n)
    // -------------------------------------------------------
    int memoryOptimizationSol(vector<vector<int>>& grid, int m, int n) {
        vector<int> dp(n + 1, 0);    // previous row
        vector<int> temp(n + 1, 0); // current row

        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                // Base case: origin
                if (i == 0 && j == 0) {
                    temp[j] = grid[i][j];
                    continue;
                }

                int up   = (i > 0) ? dp[j]      : INT_MAX;  // from above (previous row)
                int left = (j > 0) ? temp[j - 1] : INT_MAX;  // from left (same row)
                temp[j] = grid[i][j] + min(up, left);
            }
            dp = temp;  // current row becomes previous for next iteration
        }
        return dp[n];
    }

public:
    // -------------------------------------------------------
    //  DRIVER — change the call to test different approaches
    // -------------------------------------------------------
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, -1));

        // Uncomment the approach you want to run:
        // return sol(grid, m-1, n-1);                  // Pure Recursion
        // return memSol(grid, dp, m-1, n-1);           // Memoization
        // return tabSol(grid, dp, m-1, n-1);           // Tabulation
        return memoryOptimizationSol(grid, m-1, n-1);   // Space Optimized ✅
    }
};

// -------------------------------------------------------
//  MAIN — test with sample inputs
// -------------------------------------------------------
int main() {
    Solution sol;

    // Test 1: Expected 7  (1→3→1→1→1)
    vector<vector<int>> grid1 = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };
    cout << "Test 1: " << sol.minPathSum(grid1) << endl;

    // Test 2: Expected 12  (1→2→3→6)
    vector<vector<int>> grid2 = {
        {1, 2, 3},
        {4, 5, 6}
    };
    cout << "Test 2: " << sol.minPathSum(grid2) << endl;

    // Test 3: Single cell → Expected 5
    vector<vector<int>> grid3 = {{5}};
    cout << "Test 3: " << sol.minPathSum(grid3) << endl;

    return 0;
}