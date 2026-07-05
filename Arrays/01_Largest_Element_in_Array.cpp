#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : Largest Element in Array
// Link     : https://www.geeksforgeeks.org/c-program-find-largest-element-array/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given an array of integers, return the largest element.
//
// Key Trick:
// Track maximum element while traversing array once.
// Initialize with INT_MIN to handle negative numbers.
//
// Example:
// nums = [3, 3, 6, 1]
// m = INT_MIN
// m = max(INT_MIN, 3) = 3
// m = max(3, 3)       = 3
// m = max(3, 6)       = 6
// m = max(6, 1)       = 6
// Answer: 6 ✅
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Brute Force
    // Time Complexity  : O(n^2) - compare every pair
    // Space Complexity : O(1)
    // ============================================================
    int largestElementBrute(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            bool isLargest = true;
            for (int j = 0; j < n; j++) {
                if (nums[j] > nums[i]) {
                    isLargest = false;
                    break;
                }
            }
            if (isLargest) return nums[i];
        }
        return INT_MIN;
    }

    // ============================================================
    // Approach 2: Linear Scan (Optimal)
    // Time Complexity  : O(n) - single pass
    // Space Complexity : O(1) - no extra space
    // ============================================================
    int largestElement(vector<int>& nums) {
        int m = INT_MIN;
        for (auto i : nums) {
            m = max(m, i);
        }
        return m;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> nums1 = {3, 3, 6, 1};
    cout << "Test 1: " << sol.largestElement(nums1) << endl;
    // Expected: 6

    vector<int> nums2 = {3, 3, 0, 99, -40};
    cout << "Test 2: " << sol.largestElement(nums2) << endl;
    // Expected: 99

    vector<int> nums3 = {-5, -3, -1, -10};
    cout << "Test 3: " << sol.largestElement(nums3) << endl;
    // Expected: -1

    vector<int> nums4 = {1};
    cout << "Test 4: " << sol.largestElement(nums4) << endl;
    // Expected: 1

    return 0;
}