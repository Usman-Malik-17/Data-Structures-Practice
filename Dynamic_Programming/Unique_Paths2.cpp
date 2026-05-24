/*
 * ============================================================
 *  UNIQUE PATHS II (With Obstacles) — Dynamic Programming
 *  LeetCode #63
 * ============================================================
 *  Problem:
 *    A robot is on an m x n grid at top-left corner (0,0).
 *    It wants to reach bottom-right corner (m-1, n-1).
 *    It can only move RIGHT or DOWN at any point.
 *    Cells with 1 are obstacles — robot cannot step on them.
 *    Return the number of unique paths.
 *
 *  Recurrence:
 *    paths(i, j) = 0                        if obstacle
 *    paths(i, j) = paths(i-1, j)            // came from above
 *                + paths(i, j-1)            // came from left
 *
 *  Base Cases:
 *    (0, 0) → 1   (origin, 1 way to be here)
 *    out of bounds OR obstacle → 0
 *
 *  Approaches covered:
 *    1. Pure Recursion     — O(2^(m+n)) time | O(m+n) space (stack)
 *    2. Memoization        — O(m*n)     time | O(m*n) space
 *    3. Tabulation         — O(m*n)     time | O(m*n) space
 *    4. Space Optimization — O(m*n)     time | O(n)   space
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {

    // -------------------------------------------------------
    //  1. PURE RECURSION
    //     Start from (m-1, n-1), go towards (0, 0)
    //     If cell is obstacle or out of bounds → return 0
    //     TC: O(2^(m+n))  |  SC: O(m+n) recursion stack
    // -------------------------------------------------------
    int sol(vector<vector<int>>& obstacleGrid, int m, int n) {
        // Out of bounds or obstacle — no path
        if (m < 0 || n < 0 || obstacleGrid[m][n] == 1) return 0;

        // Reached origin — 1 valid path
        if (m == 0 && n == 0) return 1;

        // Came from above + came from left
        int left = sol(obstacleGrid, m, n - 1);
        int up   = sol(obstacleGrid, m - 1, n);
        return left + up;
    }

    // -------------------------------------------------------
    //  2. MEMOIZATION  (Recursion + Caching)
    //     Store results in dp[i][j] to avoid recomputation
    //     NOTE: bounds check MUST come before dp access
    //           to avoid out-of-bounds crash
    //     TC: O(m*n)  |  SC: O(m*n) table + O(m+n) stack
    // -------------------------------------------------------
    int memSol(vector<vector<int>>& obstacleGrid, vector<vector<int>>& dp, int m, int n) {
        // Bounds + obstacle check FIRST (before any array access!)
        if (m < 0 || n < 0 || obstacleGrid[m][n] == 1) return 0;

        // Reached origin
        if (m == 0 && n == 0) return 1;

        // Return cached result if already computed
        if (dp[m][n] != 0) return dp[m][n];

        // Came from above + came from left
        int left = memSol(obstacleGrid, dp, m, n - 1);
        int up   = memSol(obstacleGrid, dp, m - 1, n);
        return dp[m][n] = left + up;
    }

    // -------------------------------------------------------
    //  3. TABULATION  (Bottom-Up DP)
    //     Convert memoization to iterative:
    //       • Base case  →  dp[0][0] = 1
    //       • Obstacle   →  dp[i][j] = 0, skip
    //       • Recursion  →  nested loops (i: 0→m, j: 0→n)
    //       • Return     →  dp[m][n]
    //     TC: O(m*n)  |  SC: O(m*n)
    // -------------------------------------------------------
    int tabSol(vector<vector<int>>& obstacleGrid, vector<vector<int>>& dp, int m, int n) {
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                // Obstacle — no path through this cell
                if (obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0;
                    continue;  // skip left+up calculation
                }

                // Base case: origin
                if (i == 0 && j == 0) {
                    dp[i][j] = 1;
                    continue;
                }

                int left = (j > 0) ? dp[i][j-1] : 0;   // from left
                int up   = (i > 0) ? dp[i-1][j] : 0;   // from above
                dp[i][j] = left + up;
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
    int spaceOptimization(vector<vector<int>>& obstacleGrid, int m, int n) {
        vector<int> dp(n + 1, 0);    // previous row
        vector<int> temp(n + 1, 0); // current row

        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                // Obstacle — no path through this cell
                if (obstacleGrid[i][j] == 1) {
                    temp[j] = 0;
                    continue;
                }

                // Base case: origin
                if (i == 0 && j == 0) {
                    temp[j] = 1;
                    continue;
                }

                int left = (j > 0) ? temp[j-1] : 0;  // from left (same row)
                int up   = dp[j];                      // from above (previous row)
                temp[j] = left + up;
            }
            dp = temp;  // current row becomes previous for next iteration
        }
        return dp[n];
    }

public:
    // -------------------------------------------------------
    //  DRIVER — change the call to test different approaches
    // -------------------------------------------------------
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        // Uncomment the approach you want to run:
        // return sol(obstacleGrid, m-1, n-1);              // Pure Recursion
        // return memSol(obstacleGrid, dp, m-1, n-1);       // Memoization
        // return tabSol(obstacleGrid, dp, m-1, n-1);       // Tabulation
        return spaceOptimization(obstacleGrid, m-1, n-1);   // Space Optimized ✅
    }
};

// -------------------------------------------------------
//  MAIN — test with sample inputs
// -------------------------------------------------------
int main() {
    Solution sol;

    // Test 1: obstacle in middle → Expected: 2
    vector<vector<int>> grid1 = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };
    cout << "Test 1: " << sol.uniquePathsWithObstacles(grid1) << endl;

    // Test 2: obstacle at start → Expected: 0
    vector<vector<int>> grid2 = {
        {0, 1},
        {0, 0}
    };
    cout << "Test 2: " << sol.uniquePathsWithObstacles(grid2) << endl;

    // Test 3: no obstacles → Expected: 3
    vector<vector<int>> grid3 = {
        {0, 0, 0},
        {0, 0, 0}
    };
    cout << "Test 3: " << sol.uniquePathsWithObstacles(grid3) << endl;

    return 0;
}