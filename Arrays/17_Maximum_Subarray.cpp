#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : Maximum Subarray
// Link     : https://leetcode.com/problems/maximum-subarray/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given an integer array nums, find the contiguous subarray
// with the largest sum and return its sum.
//
// Example:
// nums = [-2,1,-3,4,-1,2,1,-5,4]
//
// Maximum Sum Subarray:
// [4,-1,2,1]
//
// Answer = 6
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Brute Force
    // Time Complexity  : O(n²)
    // Space Complexity : O(1)
    //
    // Generate every possible subarray and calculate its sum.
    // Update the maximum sum whenever a larger sum is found.
    // ============================================================
    int maxSubArrayBrute(vector<int>& nums) {

        int maxSum = INT_MIN;

        for (int i = 0; i < nums.size(); i++) {

            int sum = 0;

            for (int j = i; j < nums.size(); j++) {

                sum += nums[j];
                maxSum = max(maxSum, sum);
            }
        }

        return maxSum;
    }

    // ============================================================
    // Approach 2: Dynamic Programming (Kadane DP Array)
    // Time Complexity  : O(n)
    // Space Complexity : O(n)
    //
    // dp[i] stores the maximum subarray sum ending at index i.
    //
    // Transition:
    // dp[i] = max(nums[i], dp[i-1] + nums[i])
    //
    // The answer is the maximum value in the dp array.
    // ============================================================
    int maxSubArrayDP(vector<int>& nums) {

        vector<int> dp(nums.size());

        dp[0] = nums[0];
        int maxSum = dp[0];

        for (int i = 1; i < nums.size(); i++) {

            dp[i] = max(nums[i], dp[i - 1] + nums[i]);
            maxSum = max(maxSum, dp[i]);
        }

        return maxSum;
    }

    // ============================================================
    // Approach 3: Kadane's Algorithm (Optimal)
    // Time Complexity  : O(n)
    // Space Complexity : O(1)
    //
    // Key Idea:
    //
    // Maintain:
    // sum    -> Current subarray sum
    // maxSum -> Maximum sum found so far
    //
    // If current sum becomes negative,
    // discard it and start a new subarray.
    //
    // Why?
    // A negative sum can only decrease the sum
    // of any future subarray.
    //
    // Example:
    //
    // nums = [-2,1,-3,4,-1,2,1,-5,4]
    //
    // i   num   sum   maxSum
    // ------------------------
    // 0   -2    -2      -2
    //          reset sum = 0
    //
    // 1    1     1       1
    // 2   -3    -2       1
    //          reset sum = 0
    //
    // 3    4     4       4
    // 4   -1     3       4
    // 5    2     5       5
    // 6    1     6       6
    // 7   -5     1       6
    // 8    4     5       6
    //
    // Final Answer = 6
    // ============================================================
    int maxSubArray(vector<int>& nums) {

        int sum = 0;
        int maxSum = INT_MIN;

        for (int num : nums) {

            sum += num;

            maxSum = max(maxSum, sum);

            if (sum < 0)
                sum = 0;
        }

        return maxSum;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================

int main() {

    Solution sol;

    vector<int> nums1 = {-2,1,-3,4,-1,2,1,-5,4};
    cout << "Test 1: " << sol.maxSubArray(nums1) << endl;
    // Expected: 6

    vector<int> nums2 = {1};
    cout << "Test 2: " << sol.maxSubArray(nums2) << endl;
    // Expected: 1

    vector<int> nums3 = {5,4,-1,7,8};
    cout << "Test 3: " << sol.maxSubArray(nums3) << endl;
    // Expected: 23

    vector<int> nums4 = {-5,-2,-8,-1};
    cout << "Test 4: " << sol.maxSubArray(nums4) << endl;
    // Expected: -1

    return 0;
}