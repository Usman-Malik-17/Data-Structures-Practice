/*
 * ============================================================
 *  TRIANGLE — Dynamic Programming (LeetCode #120)
 *  Fixed Starting Point, Variable Ending Point
 * ============================================================
 *  Problem:
 *    Given a triangle array, find the minimum path sum from
 *    top (row 0, col 0) to any cell in the bottom row.
 *    At each cell (i, j), you can move to:
 *      - (i+1, j)    → same column (going down)
 *      - (i+1, j+1)  → next column (going diagonal)
 *
 *  Recurrence (Top-Down):
 *    dp(i, j) = triangle[i][j] + min(dp(i-1, j), dp(i-1, j-1))
 *
 *  Base Case:
 *    (0, 0) → triangle[0][0]
 *    out of bounds → INT_MAX (invalid path)
 *
 *  Answer:
 *    min(dp[m][0], dp[m][1], ..., dp[m][n])  ← last row ka minimum
 *
 *  Approaches covered:
 *    1. Pure Recursion     — O(2^n)  time | O(n)   space (stack)
 *    2. Memoization        — O(n^2)  time | O(n^2) space
 *    3. Tabulation         — O(n^2)  time | O(n^2) space
 *    4. Space Optimization — O(n^2)  time | O(n)   space
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {

    // -------------------------------------------------------
    //  1. PURE RECURSION
    //     Start from bottom row, go towards (0,0)
    //     Each cell: came from same col or prev col above
    //     TC: O(2^n)  |  SC: O(n) recursion stack
    // -------------------------------------------------------
    int sol(vector<vector<int>>& triangle, int m, int n) {
        // Out of bounds — invalid path
        if (n < 0 || n >= (int)triangle[m].size()) return INT_MAX;

        // Base case: reached origin
        if (m == 0 && n == 0) return triangle[0][0];

        // Came from same col above + came from prev col above
        int currCol = sol(triangle, m - 1, n);
        int prevCol = sol(triangle, m - 1, n - 1);
        return triangle[m][n] + min(currCol, prevCol);
    }

    // -------------------------------------------------------
    //  2. MEMOIZATION  (Recursion + Caching)
    //     dp[i][j] = minimum path sum to reach cell (i,j)
    //     dp initialized to INT_MIN (sentinel)
    //     NOTE: Use INT_MIN not -1 as sentinel, since
    //           triangle values can be negative!
    //     TC: O(n^2)  |  SC: O(n^2) table + O(n) stack
    // -------------------------------------------------------
    int memSol(vector<vector<int>>& triangle, vector<vector<int>>& dp, int m, int n) {
        // Out of bounds — invalid path
        if (n < 0 || n >= (int)triangle[m].size()) return INT_MAX;

        // Base case: reached origin
        if (m == 0 && n == 0) return dp[m][n] = triangle[0][0];

        // Return cached result if already computed
        if (dp[m][n] != INT_MIN) return dp[m][n];

        // Came from same col above + came from prev col above
        int currCol = memSol(triangle, dp, m - 1, n);
        int prevCol = memSol(triangle, dp, m - 1, n - 1);
        return dp[m][n] = triangle[m][n] + min(currCol, prevCol);
    }

    // -------------------------------------------------------
    //  3. TABULATION  (Bottom-Up DP)
    //     Convert memoization to iterative:
    //       • Base case  →  dp[0][0] = triangle[0][0]
    //       • Recursion  →  nested loops (i: 1→m)
    //       • Answer     →  min of last row
    //     KEY: Last column of each row has no "same col above"
    //          so bounds check on j < prev_row.size() needed!
    //     TC: O(n^2)  |  SC: O(n^2)
    // -------------------------------------------------------
    int tabSol(vector<vector<int>>& triangle, vector<vector<int>>& dp, int m) {
        // Base case
        dp[0][0] = triangle[0][0];

        for (int i = 1; i <= m; i++) {
            for (int j = 0; j < (int)triangle[i].size(); j++) {
                // From same col above (bounds check needed for last col!)
                int currCol = (j < (int)triangle[i-1].size()) ? dp[i-1][j] : INT_MAX;
                // From prev col above
                int prevCol = (j > 0) ? dp[i-1][j-1] : INT_MAX;
                dp[i][j] = triangle[i][j] + min(currCol, prevCol);
            }
        }

        // Answer: minimum of last row
        int mi = INT_MAX;
        for (int j = 0; j < (int)dp[m].size(); j++)
            mi = min(mi, dp[m][j]);
        return mi;
    }

    // -------------------------------------------------------
    //  4. SPACE OPTIMIZATION
    //     Only need previous row to compute current row
    //       dp   = previous row
    //       temp = current row being filled (fresh each time)
    //     TC: O(n^2)  |  SC: O(n)
    // -------------------------------------------------------
    int spaceOptimizationSol(vector<vector<int>>& triangle, int m) {
        vector<int> dp = triangle[0];  // base case: first row

        for (int i = 1; i <= m; i++) {
            vector<int> temp(triangle[i].size());  // fresh row each iteration
            for (int j = 0; j < (int)triangle[i].size(); j++) {
                // From same col above (bounds check for last col!)
                int up     = (j < (int)dp.size()) ? dp[j]   : INT_MAX;
                // From prev col above
                int upLeft = (j > 0)              ? dp[j-1] : INT_MAX;
                temp[j] = triangle[i][j] + min(up, upLeft);
            }
            dp = temp;  // current becomes previous for next iteration
        }

        // Answer: minimum of last row
        int mi = INT_MAX;
        for (int i = 0; i < (int)dp.size(); i++)
            mi = min(mi, dp[i]);
        return mi;
    }

public:
    // -------------------------------------------------------
    //  DRIVER — change the call to test different approaches
    // -------------------------------------------------------
    int minimumTotal(vector<vector<int>>& triangle) {
        int m = triangle.size();

        // Build dp with exact triangle shape (no wasted space)
        vector<vector<int>> dp;
        for (int i = 0; i < m; i++)
            dp.push_back(vector<int>(triangle[i].size(), INT_MIN));

        // Uncomment the approach you want to run:
        // int mi = INT_MAX;
        // for(int j = 0; j < triangle[m-1].size(); j++)
        //     mi = min(mi, sol(triangle, m-1, j));       // Pure Recursion
        // return mi;

        // int mi = INT_MAX;
        // for(int j = 0; j < triangle[m-1].size(); j++)
        //     mi = min(mi, memSol(triangle, dp, m-1, j)); // Memoization
        // return mi;

        // return tabSol(triangle, dp, m-1);              // Tabulation
        return spaceOptimizationSol(triangle, m - 1);     // Space Optimized ✅
    }
};

// -------------------------------------------------------
//  MAIN — test with sample inputs
// -------------------------------------------------------
int main() {
    Solution sol;

    // Test 1: Expected 11  (2→3→5→1)
    vector<vector<int>> t1 = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    cout << "Test 1: " << sol.minimumTotal(t1) << endl;

    // Test 2: Expected -1
    vector<vector<int>> t2 = {{-1}, {2, 3}, {1, -1, -3}};
    cout << "Test 2: " << sol.minimumTotal(t2) << endl;

    // Test 3: Single element → Expected 0
    vector<vector<int>> t3 = {{0}};
    cout << "Test 3: " << sol.minimumTotal(t3) << endl;

    return 0;
}