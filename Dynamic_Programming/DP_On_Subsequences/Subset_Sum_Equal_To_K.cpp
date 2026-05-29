/*
 * ============================================================
 *  SUBSET SUM EQUAL TO TARGET — Dynamic Programming
 *  (Striver DP Series — DP on Subsequences)
 * ============================================================
 *  Problem:
 *    Given an array arr of n integers and an integer target,
 *    determine if there exists a subset of arr whose sum
 *    equals the target.
 *
 *  Recurrence:
 *    dp(index, target) = dp(index-1, target - arr[index])  // pick
 *                     OR dp(index-1, target)               // not pick
 *
 *  Base Cases:
 *    target == 0        → true  (empty subset has sum 0)
 *    target < 0         → false (overshot)
 *    index == 0         → arr[0] == target
 *
 *  Approaches covered:
 *    1. Pure Recursion     — O(2^n)   time | O(n)   space (stack)
 *    2. Memoization        — O(n*t)   time | O(n*t) space
 *    3. Tabulation         — O(n*t)   time | O(n*t) space
 *    4. Space Optimization — O(n*t)   time | O(t)   space
 *
 *  NOTE on dp type:
 *    Use vector<int> with -1 sentinel for memoization
 *    (not vector<bool>) since bool can't store -1!
 *    Use vector<bool> for tabulation since no sentinel needed.
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {

    // -------------------------------------------------------
    //  1. PURE RECURSION
    //     Try picking or not picking each element
    //     TC: O(2^n)  |  SC: O(n) recursion stack
    // -------------------------------------------------------
    bool sol(vector<int> arr, int index, int target) {
        // Base case: target achieved
        if (target == 0) return true;

        // Base case: overshot
        if (target < 0) return false;

        // Base case: only first element left
        if (index == 0) return arr[0] == target;

        // Pick current element OR skip it
        return sol(arr, index - 1, target - arr[index])
            || sol(arr, index - 1, target);
    }

    // -------------------------------------------------------
    //  2. MEMOIZATION  (Recursion + Caching)
    //     dp[index][target] = can we achieve target using
    //                         elements 0..index?
    //     Sentinel: -1 (use int not bool — bool can't hold -1!)
    //     TC: O(n*t)  |  SC: O(n*t) table + O(n) stack
    // -------------------------------------------------------
    int memSol(vector<int> arr, vector<vector<int>>& dp, int index, int target) {
        // Base cases
        if (target == 0) return 1;
        if (target < 0)  return 0;
        if (index == 0)  return arr[0] == target;

        // Return cached result
        if (dp[index][target] != -1) return dp[index][target];

        // Pick OR not pick
        return dp[index][target] =
            memSol(arr, dp, index - 1, target - arr[index])
         || memSol(arr, dp, index - 1, target);
    }

    // -------------------------------------------------------
    //  3. TABULATION  (Bottom-Up DP)
    //     Convert memoization to iterative:
    //       • target==0      → dp[i][0] = true  (all rows)
    //       • index==0       → dp[0][arr[0]] = true
    //       • Recursion      → loops (i: 1→n, t: 1→target)
    //       • Return         → dp[n-1][target]
    //     TC: O(n*t)  |  SC: O(n*t)
    // -------------------------------------------------------
    bool tabSol(vector<int> arr, vector<vector<bool>>& dp, int target) {
        // Base case 1: target 0 is always achievable
        for (int i = 0; i < (int)arr.size(); i++)
            dp[i][0] = true;

        // Base case 2: first element can only hit one target
        if (arr[0] <= target)
            dp[0][arr[0]] = true;

        // Fill remaining cells
        for (int i = 1; i < (int)arr.size(); i++) {
            for (int t = 1; t <= target; t++) {
                // Pick: use previous row with reduced target
                if (t - arr[i] >= 0)
                    dp[i][t] = dp[i-1][t - arr[i]];

                // Not pick: if pick didn't work, try skipping
                if (!dp[i][t])
                    dp[i][t] = dp[i-1][t];
            }
        }
        return dp[arr.size() - 1][target];
    }

    // -------------------------------------------------------
    //  4. SPACE OPTIMIZATION
    //     Only need previous row to compute current row
    //       dp   = previous row
    //       temp = current row being filled
    //     TC: O(n*t)  |  SC: O(t)
    // -------------------------------------------------------
    bool spaceOptimizationSol(vector<int> arr, int target) {
        vector<bool> dp(target + 1, false);    // previous row
        vector<bool> temp(target + 1, false);  // current row

        // Base case: first element
        dp[0] = true;
        if (arr[0] <= target) dp[arr[0]] = true;

        for (int i = 1; i < (int)arr.size(); i++) {
            for (int t = 1; t <= target; t++) {
                // Pick
                if (t - arr[i] >= 0) temp[t] = dp[t - arr[i]];
                // Not pick
                if (!temp[t]) temp[t] = dp[t];
            }
            dp = temp;
            dp[0] = true;  // target 0 always achievable
        }
        return dp[target];
    }

public:
    // -------------------------------------------------------
    //  DRIVER — change the call to test different approaches
    // -------------------------------------------------------
    bool isSubsetSum(vector<int> arr, int target) {
        int n = arr.size();
        vector<vector<int>>  dpMem(n, vector<int> (target + 1, -1));
        vector<vector<bool>> dpTab(n, vector<bool>(target + 1, false));

        // Uncomment the approach you want to run:
        // return sol(arr, n-1, target);                 // Pure Recursion
        // return memSol(arr, dpMem, n-1, target);       // Memoization
        // return tabSol(arr, dpTab, target);            // Tabulation
        return spaceOptimizationSol(arr, target);        // Space Optimized ✅
    }
};

// -------------------------------------------------------
//  MAIN — test with sample inputs
// -------------------------------------------------------
int main() {
    Solution sol;

    // Test 1: {1,2,3} subset sums to 6 → Expected: true
    cout << "Test 1: " << sol.isSubsetSum({1, 2, 7, 3}, 6) << endl;

    // Test 2: No subset sums to 6 → Expected: false
    cout << "Test 2: " << sol.isSubsetSum({2, 3, 5}, 6) << endl;

    // Test 3: Single element equals target → Expected: true
    cout << "Test 3: " << sol.isSubsetSum({3}, 3) << endl;

    // Test 4: No subset sums to 7 → Expected: false
    cout << "Test 4: " << sol.isSubsetSum({1, 2, 3}, 7) << endl;

    return 0;
}