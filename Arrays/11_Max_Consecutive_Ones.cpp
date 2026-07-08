#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : Max Consecutive Ones
// Link     : https://leetcode.com/problems/max-consecutive-ones/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given a binary array nums, return the maximum number of
// consecutive 1's in the array.
//
// Example:
// nums = [1,1,0,1,1,1]
//
// Consecutive Ones:
// [1,1] -> length = 2
// [1,1,1] -> length = 3
//
// Answer = 3 ✅
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Brute Force
    // Time Complexity  : O(n²)
    // Space Complexity : O(1)
    //
    // Idea:
    // For every index containing 1,
    // keep counting consecutive 1's until a 0 appears.
    // ============================================================
    int findMaxConsecutiveOnesBrute(vector<int>& nums) {

        int maxCount = 0;

        for (int i = 0; i < nums.size(); i++) {

            if (nums[i] == 1) {

                int count = 1;

                for (int j = i + 1; j < nums.size(); j++) {

                    if (nums[j] == 1)
                        count++;
                    else
                        break;
                }

                maxCount = max(maxCount, count);
            }
        }

        return maxCount;
    }

    // ============================================================
    // Approach 2: Sliding Window (Optimal)
    // Time Complexity  : O(n)
    // Space Complexity : O(1)
    //
    // Idea:
    // Keep a window containing only consecutive 1's.
    //
    // If nums[r] == 1
    //      -> Expand window.
    //
    // If nums[r] == 0
    //      -> Update answer.
    //      -> Move left pointer after zero.
    //
    // Example:
    //
    // nums = [1,1,0,1,1,1]
    //
    // Window1 = [1,1]
    // length = 2
    //
    // Zero found
    // New window starts after zero
    //
    // Window2 = [1,1,1]
    // length = 3
    //
    // Answer = 3 ✅
    // ============================================================
    int findMaxConsecutiveOnes(vector<int>& nums) {

        int l = 0;
        int r = 0;
        int maxCount = 0;

        while (r < nums.size()) {

            if (nums[r] == 1) {
                r++;
            }
            else {

                maxCount = max(maxCount, r - l);

                l = r + 1;
                r++;
            }
        }

        // Handle last window
        maxCount = max(maxCount, r - l);

        return maxCount;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {

    Solution sol;

    vector<int> nums1 = {1,1,0,1,1,1};
    cout << "Test 1: " << sol.findMaxConsecutiveOnes(nums1) << endl;
    // Expected: 3

    vector<int> nums2 = {1,0,1,1,0,1};
    cout << "Test 2: " << sol.findMaxConsecutiveOnes(nums2) << endl;
    // Expected: 2

    vector<int> nums3 = {1,1,1,1};
    cout << "Test 3: " << sol.findMaxConsecutiveOnes(nums3) << endl;
    // Expected: 4

    vector<int> nums4 = {0,0,0};
    cout << "Test 4: " << sol.findMaxConsecutiveOnes(nums4) << endl;
    // Expected: 0

    return 0;
}