#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : Single Number
// Link     : https://leetcode.com/problems/single-number/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given a non-empty array where every element appears exactly
// twice except one element, find that unique element.
//
// Example:
// nums = [4,1,2,1,2]
//
// Frequency:
// 4 -> 1
// 1 -> 2
// 2 -> 2
//
// Answer = 4 ✅
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Brute Force
    // Time Complexity  : O(n²)
    // Space Complexity : O(1)
    //
    // Idea:
    // Count frequency of every element using nested loops.
    // The element whose frequency is 1 is the answer.
    // ============================================================
    int singleNumberBrute(vector<int>& nums) {

        for (auto i : nums) {

            int cnt = 0;

            for (auto j : nums) {

                if (i == j)
                    cnt++;
            }

            if (cnt == 1)
                return i;
        }

        return 0;
    }

    // ============================================================
    // Approach 2: Sorting
    // Time Complexity  : O(n log n)
    // Space Complexity : O(1)
    //
    // Idea:
    // Sort the array.
    // Equal elements become adjacent.
    // Find the element whose group size is 1.
    // ============================================================
    int singleNumberSort(vector<int>& nums) {

        sort(nums.begin(), nums.end());

        int l = 0;
        int r = 0;

        while (r < nums.size()) {

            if (nums[r] != nums[l]) {

                if (r - l == 1)
                    return nums[l];

                l = r;
            }

            r++;
        }

        return nums[l];
    }

    // ============================================================
    // Approach 3: Hash Map
    // Time Complexity  : O(n)
    // Space Complexity : O(n)
    //
    // Idea:
    // Store frequency of every element in a hash map.
    // Return the element whose frequency is 1.
    // ============================================================
    int singleNumberHash(vector<int>& nums) {

        unordered_map<int, int> freq;

        for (auto i : nums)
            freq[i]++;

        for (auto i : freq) {

            if (i.second == 1)
                return i.first;
        }

        return 0;
    }

    // ============================================================
    // Approach 4: XOR (Optimal)
    // Time Complexity  : O(n)
    // Space Complexity : O(1)
    //
    // Key Observation:
    //
    // a ^ a = 0
    // a ^ 0 = a
    //
    // Since every element appears twice,
    // duplicate numbers cancel each other.
    // Only the unique element remains.
    //
    // Example:
    //
    // nums = [4,1,2,1,2]
    //
    // XOR = 4 ^ 1 ^ 2 ^ 1 ^ 2
    //     = 4 ^ (1^1) ^ (2^2)
    //     = 4 ^ 0 ^ 0
    //     = 4 ✅
    // ============================================================
    int singleNumber(vector<int>& nums) {

        int XOR = 0;

        for (auto i : nums)
            XOR ^= i;

        return XOR;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {

    Solution sol;

    vector<int> nums1 = {2,2,1};
    cout << "Test 1: " << sol.singleNumber(nums1) << endl;
    // Expected: 1

    vector<int> nums2 = {4,1,2,1,2};
    cout << "Test 2: " << sol.singleNumber(nums2) << endl;
    // Expected: 4

    vector<int> nums3 = {1};
    cout << "Test 3: " << sol.singleNumber(nums3) << endl;
    // Expected: 1

    return 0;
}