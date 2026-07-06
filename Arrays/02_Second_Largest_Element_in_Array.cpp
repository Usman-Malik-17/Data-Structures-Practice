#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : Second Largest Element in Array
// Link     : https://takeuforward.org/data-structure/find-second-largest-element-in-an-array/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given an array of integers, return the second largest element.
// If no second largest exists, return -1.
//
// Key Trick — Single Pass:
// Track largest and second largest simultaneously.
// New largest found → old largest becomes second largest.
// Element smaller than largest but larger than second → update sl.
//
// Example:
// nums = [3, 6, 4, 1]
// largest=3, sLargest=-1
// i=1: 6>3  → sLargest=3, largest=6
// i=2: 4<6 && 4>3 → sLargest=4
// i=3: 1<6 && 1<4 → no change
// Answer: 4 ✅
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Sort + Linear Scan
    // Time Complexity  : O(n log n) - sorting dominates
    // Space Complexity : O(1)
    // ============================================================
    int secondLargestElementBrute(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int largest = nums[nums.size() - 1];
        int sLargest = -1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != largest && nums[i] > sLargest) {
                sLargest = nums[i];
            }
        }
        return sLargest;
    }

    // ============================================================
    // Approach 2: Two Pass
    // Time Complexity  : O(2n) = O(n)
    // Space Complexity : O(1)
    // ============================================================
    int secondLargestElementTwoPass(vector<int>& nums) {
        int largest = nums[0];
        for (int i = 0; i < nums.size(); i++) {
            largest = max(largest, nums[i]);
        }
        int sLargest = -1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != largest && nums[i] > sLargest) {
                sLargest = nums[i];
            }
        }
        return sLargest;
    }

    // ============================================================
    // Approach 3: Single Pass (Optimal)
    // Time Complexity  : O(n) - single pass
    // Space Complexity : O(1) - no extra space
    // ============================================================
    int secondLargestElement(vector<int>& nums) {
        int largest  = nums[0];
        int sLargest = -1;

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > largest) {
                sLargest = largest;   // old largest → second largest
                largest  = nums[i];   // new largest
            } else if (nums[i] < largest && nums[i] > sLargest) {
                sLargest = nums[i];   // update second largest
            }
        }
        return sLargest;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> nums1 = {3, 6, 4, 1};
    cout << "Test 1: " << sol.secondLargestElement(nums1) << endl;
    // Expected: 4

    vector<int> nums2 = {3, 3, 0, 99, -40};
    cout << "Test 2: " << sol.secondLargestElement(nums2) << endl;
    // Expected: 3

    vector<int> nums3 = {1, 1, 1};
    cout << "Test 3: " << sol.secondLargestElement(nums3) << endl;
    // Expected: -1

    vector<int> nums4 = {5, 2};
    cout << "Test 4: " << sol.secondLargestElement(nums4) << endl;
    // Expected: 2

    return 0;
}