#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 53. Maximum Subarray (Kadane's Algorithm)
// Link     : https://leetcode.com/problems/maximum-subarray/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Find the subarray with the largest sum and return its sum.
//
// Key Trick — Kadane's Algorithm:
// Keep running sum. If sum drops below 0 — reset to 0 (discard).
// Track maximum sum seen so far.
//
// Why reset at 0?
// Negative prefix only hurts future subarrays — better to start fresh!
//
// Example:
// nums = [2,3,5,-2,7,-4]
// i=0: sum=2,  maxi=2
// i=1: sum=5,  maxi=5
// i=2: sum=10, maxi=10
// i=3: sum=8,  maxi=10
// i=4: sum=15, maxi=15
// i=5: sum=11, maxi=15
// Answer: 15 ✅
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Brute Force — Nested Loop
    // Time Complexity  : O(n^2) - check all subarrays
    // Space Complexity : O(1)
    // ============================================================
    int maxSubArrayBrute(vector<int>& nums) {
        int maxi = INT_MIN;
        for (int i = 0; i < nums.size(); i++) {
            int sum = 0;
            for (int j = i; j < nums.size(); j++) {
                sum += nums[j];
                maxi = max(maxi, sum);
            }
        }
        return maxi;
    }

    // ============================================================
    // Approach 2: Kadane's Algorithm — Sum Only
    // Time Complexity  : O(n) - single pass
    // Space Complexity : O(1)
    // ============================================================
    int maxSubArraySum(vector<int>& nums) {
        int sum = 0;
        int maxi = INT_MIN;

        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            maxi = max(maxi, sum);
            if (sum < 0) sum = 0;  // reset — negative prefix useless
        }
        return maxi;
    }

    // ============================================================
    // Approach 3: Kadane's Algorithm — Sum + Print Subarray
    // Time Complexity  : O(n) - single pass
    // Space Complexity : O(1)
    //
    // Extra: Track start and end indexes of max subarray.
    // When sum resets to 0 — new start begins at next index.
    // When new max found — update arrStart and arrEnd.
    // ============================================================
    int maxSubArray(vector<int>& nums) {
        int start    = 0;
        int arrStart = 0;
        int arrEnd   = 0;
        int sum      = 0;
        int maxi     = INT_MIN;

        for (int i = 0; i < nums.size(); i++) {
            if (sum == 0) start = i;  // new subarray starts here

            sum += nums[i];

            if (maxi < sum) {
                maxi     = sum;
                arrStart = start;
                arrEnd   = i;
            }

            if (sum < 0) sum = 0;  // reset
        }

        // Print subarray
        cout << "Max Subarray: [";
        for (int i = arrStart; i <= arrEnd; i++) {
            cout << nums[i];
            if (i != arrEnd) cout << ", ";
        }
        cout << "]" << endl;
        cout << "Indexes: [" << arrStart << ", " << arrEnd << "]" << endl;

        return maxi;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> nums1 = {2, 3, 5, -2, 7, -4};
    cout << "Test 1: " << sol.maxSubArray(nums1) << endl;
    // Expected: 15, subarray [2,3,5,-2,7]

    cout << endl;

    vector<int> nums2 = {-2, -3, -7, -2, -10, -4};
    cout << "Test 2: " << sol.maxSubArray(nums2) << endl;
    // Expected: -2

    cout << endl;

    vector<int> nums3 = {-1, 2, 3, -1, 2, -6, 5};
    cout << "Test 3: " << sol.maxSubArray(nums3) << endl;
    // Expected: 6, subarray [2,3,-1,2]

    return 0;
}