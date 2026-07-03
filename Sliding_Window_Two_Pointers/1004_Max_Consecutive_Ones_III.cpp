#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 1004. Max Consecutive Ones III
// Link     : https://leetcode.com/problems/max-consecutive-ones-iii/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given binary array and k, return max consecutive 1s after
// flipping at most k zeros.
//
// Key Trick — Sliding Window:
// Maintain window [l, r] with at most k zeros.
// Expand right — if zero found, increment zeroCount.
// Shrink left — if zeroCount > k, shrink until valid.
// Track maximum window size.
//
// Example: nums = [1,1,1,0,0,0,1,1,1,1,0], k=2
// Expand until zeroCount > k, then shrink from left.
// Best window = [1,1,1,0,0,1,1,1,1,1,1] → length 6 ✅
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Brute Force
    // Time Complexity  : O(n^2) - check all subarrays
    // Space Complexity : O(1)
    // ============================================================
    int longestOnesBrute(vector<int>& nums, int k) {
        int n = nums.size();
        int maxLen = 0;

        for (int i = 0; i < n; i++) {
            int zeroCount = 0;
            for (int j = i; j < n; j++) {
                if (nums[j] == 0) zeroCount++;
                if (zeroCount > k) break;
                maxLen = max(maxLen, j - i + 1);
            }
        }
        return maxLen;
    }

    // ============================================================
    // Approach 2: Sliding Window — Shrink While Invalid
    // Time Complexity  : O(n + n) = O(n) - r moves n, l moves n
    // Space Complexity : O(1)
    //
    // Explanation:
    // When zeroCount > k — shrink window using while loop
    // until zeroCount <= k again. Both l and r can move n times
    // in worst case — hence O(2n).
    // ============================================================
    int longestOnesV1(vector<int>& nums, int k) {
        int r = 0, l = 0;
        int n = nums.size();
        int maxLen = 0;
        int zeroCount = 0;

        while (r < n) {
            if (nums[r] == 0) {
                zeroCount++;
                // Shrink window until valid
                while (zeroCount > k) {
                    if (nums[l] == 0) zeroCount--;
                    l++;
                }
            }
            maxLen = max(maxLen, r - l + 1);
            r++;
        }
        return maxLen;
    }

    // ============================================================
    // Approach 3: Sliding Window — Shrink By One (Optimal)
    // Time Complexity  : O(n) - r moves n, l never exceeds r
    // Space Complexity : O(1)
    //
    // Explanation:
    // Instead of shrinking until valid (while loop), shrink by
    // exactly one step (if statement). Window never shrinks below
    // max valid size seen so far — so maxLen auto-tracked by
    // window size (r - l + 1) at each step.
    // ============================================================
    int longestOnes(vector<int>& nums, int k) {
        int r = 0, l = 0;
        int n = nums.size();
        int maxLen = 0;
        int zeroCount = 0;

        while (r < n) {
            if (nums[r] == 0) zeroCount++;

            // Shrink by one if invalid
            if (zeroCount > k) {
                if (nums[l] == 0) zeroCount--;
                l++;
            }

            maxLen = max(maxLen, r - l + 1);
            r++;
        }
        return maxLen;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> nums1 = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
    cout << "Test 1: " << sol.longestOnes(nums1, 2) << endl;
    // Expected: 6

    vector<int> nums2 = {0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1};
    cout << "Test 2: " << sol.longestOnes(nums2, 3) << endl;
    // Expected: 10

    vector<int> nums3 = {0, 0, 0};
    cout << "Test 3: " << sol.longestOnes(nums3, 0) << endl;
    // Expected: 0

    vector<int> nums4 = {1, 1, 1};
    cout << "Test 4: " << sol.longestOnes(nums4, 2) << endl;
    // Expected: 3

    return 0;
}