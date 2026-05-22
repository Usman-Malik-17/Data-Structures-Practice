/*
 * ============================================================
 *  NINJA TRAINING — Dynamic Programming
 * ============================================================
 *  Problem:
 *    A ninja trains over 'n' days. Each day he can do one of
 *    3 activities (0, 1, 2). He CANNOT do the same activity
 *    on two consecutive days. Each activity gives some points.
 *    Maximize total points over all n days.
 *
 *  Approaches covered (bottom-up in complexity):
 *    1. Pure Recursion       — O(2^n)  time | O(n) space (stack)
 *    2. Memoization          — O(n*3*2) time | O(n*4) space
 *    3. Tabulation           — O(n*3*2) time | O(n*4) space
 *    4. Space Optimization   — O(n*3*2) time | O(1)   space
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{

    // -------------------------------------------------------
    //  1. PURE RECURSION
    //     State:  (day, last) — current day, last activity done
    //     Choice: pick any activity i != last
    //     Base:   day == 0, pick best activity != last
    //     TC: O(2^n)  |  SC: O(n) recursion stack
    // -------------------------------------------------------
    int sol(vector<vector<int>> &matrix, vector<vector<int>> &dp, int day, int last)
    {

        // Base case: on day 0, pick the best allowed activity
        if (day == 0)
        {
            int m = INT_MIN;
            for (int i = 0; i <= 2; i++)
            {
                if (i != last)
                    m = max(m, matrix[0][i]);
            }
            return m;
        }

        // Try all activities except 'last', take the maximum
        int m = INT_MIN;
        for (int i = 0; i <= 2; i++)
        {
            if (i != last)
                m = max(m, matrix[day][i] + sol(matrix, dp, day - 1, i));
        }
        return m;
    }

    // -------------------------------------------------------
    //  2. MEMOIZATION  (Recursion + Caching)
    //     Same logic as recursion but store results in dp[][].
    //     dp[day][last] = max points from day 0..day
    //                     when 'last' activity is forbidden.
    //     TC: O(n*3*2)  |  SC: O(n*4) dp table + O(n) stack
    // -------------------------------------------------------
    int memSol(vector<vector<int>> &matrix, vector<vector<int>> &dp, int day, int last)
    {

        // Return cached result if already computed
        if (dp[day][last] != -1)
            return dp[day][last];

        // Base case
        if (day == 0)
        {
            int m = INT_MIN;
            for (int i = 0; i <= 2; i++)
            {
                if (i != last)
                    m = max(m, matrix[0][i]);
            }
            return dp[day][last] = m; // store before returning
        }

        // Recursive case — try all activities except 'last'
        int m = INT_MIN;
        for (int i = 0; i <= 2; i++)
        {
            if (i != last)
                m = max(m, matrix[day][i] + memSol(matrix, dp, day - 1, i));
        }
        return dp[day][last] = m; // store before returning
    }

    // -------------------------------------------------------
    //  3. TABULATION  (Bottom-Up DP)
    //     Convert memoization to iterative:
    //       • Base case  →  dp[0][last] initialization
    //       • Recursion  →  nested for loops (day: 1..n-1)
    //       • Return     →  max(dp[n-1][0..2])
    //     TC: O(n*3*2)  |  SC: O(n*4)
    // -------------------------------------------------------
    int tabSol(vector<vector<int>> &matrix, vector<vector<int>> &dp)
    {

        // Fill base case: day = 0
        for (int last = 0; last <= 2; last++)
        {
            int m = INT_MIN;
            for (int i = 0; i <= 2; i++)
            {
                if (i != last)
                    m = max(m, matrix[0][i]);
            }
            dp[0][last] = m;
        }

        // Fill remaining days bottom-up
        for (int day = 1; day <= (int)matrix.size() - 1; day++)
        {
            for (int last = 0; last <= 2; last++)
            {
                int m = INT_MIN;
                for (int i = 0; i <= 2; i++)
                {
                    if (i != last)
                        // Current activity points + best from previous day
                        m = max(m, matrix[day][i] + dp[day - 1][i]);
                }
                dp[day][last] = m;
            }
        }

        // Answer: last day, no restriction (last = 3 means "no previous")
        int n = matrix.size();
        return max(dp[n - 1][0], max(dp[n - 1][1], dp[n - 1][2]));
    }

    // -------------------------------------------------------
    //  4. SPACE OPTIMIZATION
    //     Observation: tabulation only needs dp[day-1] to
    //     compute dp[day] — store just ONE previous row.
    //       arr  = previous day's results  (replaces dp[day-1])
    //       temp = current day's results   (replaces dp[day])
    //     TC: O(n*3*2)  |  SC: O(1)  (only two 1D arrays)
    // -------------------------------------------------------
    int spaceOptimizationSol(vector<vector<int>> &matrix)
    {

        // arr holds results for day 0 (base case)
        vector<int> arr(3, 0);
        arr[0] = max(matrix[0][1], matrix[0][2]); // last=0 forbidden
        arr[1] = max(matrix[0][0], matrix[0][2]); // last=1 forbidden
        arr[2] = max(matrix[0][0], matrix[0][1]); // last=2 forbidden

        // Process each subsequent day
        for (int day = 1; day <= (int)matrix.size() - 1; day++)
        {
            vector<int> temp(3, 0); // fresh row for current day

            for (int last = 0; last <= 2; last++)
            {
                // Try all activities except 'last'
                for (int i = 0; i <= 2; i++)
                {
                    if (i != last)
                        temp[last] = max(temp[last], matrix[day][i] + arr[i]);
                }
            }

            arr = temp; // current day becomes previous for next iteration
        }

        // Best answer over all last-activity choices
        return max(arr[0], max(arr[1], arr[2]));
    }

public:
    // -------------------------------------------------------
    //  DRIVER — change the call to test different approaches
    // -------------------------------------------------------
    int ninjaTraining(vector<vector<int>> &matrix)
    {
        // Memoization needs a dp table initialised to -1
        vector<vector<int>> dp(matrix.size(), vector<int>(4, -1));

        // Uncomment the approach you want to run:
        // return sol(matrix, dp, matrix.size()-1, 3);          // Pure recursion
        // return memSol(matrix, dp, matrix.size()-1, 3);       // Memoization
        // return tabSol(matrix, dp); // Tabulation
        return spaceOptimizationSol(matrix);                    // Space optimized ✅
    }
};

// -------------------------------------------------------
//  MAIN — test with a sample matrix
//  matrix[i][j] = points for activity j on day i
// -------------------------------------------------------
int main()
{
    // Example:
    //        Act0  Act1  Act2
    // Day 0:  10    40    70
    // Day 1:  20    50    80
    // Day 2:  30    60    90
    vector<vector<int>> matrix = {
        {10, 40, 70},
        {20, 50, 80},
        {30, 60, 90}};

    Solution sol;
    cout << "Max Points: " << sol.ninjaTraining(matrix) << endl;
    // Expected: 210  (70 + 80 + 60)

    return 0;
}