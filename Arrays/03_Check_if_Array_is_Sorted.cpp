#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : Check if Array is Sorted
// Link     : https://takeuforward.org/data-structure/check-if-an-array-is-sorted/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given an array of integers, return true if array is sorted
// in non-decreasing order, false otherwise.
//
// Key Trick:
// Check every adjacent pair — if any pair is out of order
// return false immediately. If loop completes → sorted!
//
// Example:
// nums = [1, 2, 3, 4, 5]
// All adjacent pairs in order → true ✅
//
// nums = [1, 3, 2, 4]
// i=2: nums[2]=2 < nums[1]=3 → false ✅
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Brute Force — Sort and Compare
    // Time Complexity  : O(n log n) - sorting
    // Space Complexity : O(n) - copy array
    // ============================================================
    bool isSortedBrute(vector<int>& nums) {
        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());
        return sorted == nums;
    }

    // ============================================================
    // Approach 2: Linear Scan (Optimal)
    // Time Complexity  : O(n) - single pass
    // Space Complexity : O(1) - no extra space
    // ============================================================
    bool isSorted(vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < nums[i - 1]) return false;
        }
        return true;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> nums1 = {1, 2, 3, 4, 5};
    cout << "Test 1: " << sol.isSorted(nums1) << endl;
    // Expected: 1 (true)

    vector<int> nums2 = {1, 3, 2, 4};
    cout << "Test 2: " << sol.isSorted(nums2) << endl;
    // Expected: 0 (false)

    vector<int> nums3 = {1, 1, 1, 1};
    cout << "Test 3: " << sol.isSorted(nums3) << endl;
    // Expected: 1 (true)

    vector<int> nums4 = {5, 4, 3, 2, 1};
    cout << "Test 4: " << sol.isSorted(nums4) << endl;
    // Expected: 0 (false)

    return 0;
}