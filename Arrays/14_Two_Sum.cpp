#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : Two Sum
// Link     : https://leetcode.com/problems/two-sum/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given an integer array nums and an integer target,
// return indices of the two numbers such that they add up to target.
//
// Exactly one valid answer exists.
// Same element cannot be used twice.
//
// Example:
// nums = [2,7,11,15], target = 9
//
// nums[0] + nums[1] = 2 + 7 = 9
//
// Answer = {0,1}
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Brute Force
    // Time Complexity  : O(n²)
    // Space Complexity : O(1)
    //
    // Check every possible pair.
    // If their sum equals target, return their indices.
    // ============================================================
    vector<int> twoSumBrute(vector<int>& nums, int target) {

        vector<int> ans;
        int n = nums.size();

        for (int i = 0; i < n; i++) {

            for (int j = i + 1; j < n; j++) {

                if (nums[i] + nums[j] == target) {

                    ans.push_back(i);
                    ans.push_back(j);

                    return ans;
                }
            }
        }

        return ans;
    }

    // ============================================================
    // Approach 2: HashMap (Optimal)
    // Time Complexity  : O(n)
    // Space Complexity : O(n)
    //
    // Key Trick:
    //
    // complement = target - nums[i]
    //
    // If complement already exists in HashMap,
    // we have found the answer.
    //
    // Otherwise store current number with its index.
    //
    // HashMap stores:
    //
    // number -> index
    //
    // Example:
    //
    // nums = [2,7,11,15]
    // target = 9
    //
    // i=0
    // nums[i]=2
    // complement=7
    // map={}
    // store {2:0}
    //
    // i=1
    // nums[i]=7
    // complement=2
    // map contains 2
    //
    // return {0,1}
    // ============================================================
    vector<int> twoSum(vector<int>& nums, int target) {

        unordered_map<int,int> mp;
        vector<int> ans;

        for (int i = 0; i < nums.size(); i++) {

            int complement = target - nums[i];

            // Complement already exists
            if (mp.find(complement) != mp.end()) {

                ans.push_back(mp[complement]);
                ans.push_back(i);

                return ans;
            }

            // Store current number and its index
            mp[nums[i]] = i;
        }

        return ans;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================

int main() {

    Solution sol;

    vector<int> nums1 = {2,7,11,15};
    vector<int> ans1 = sol.twoSum(nums1,9);

    cout << "Test 1 : ";
    cout << ans1[0] << " " << ans1[1] << endl;
    // Expected : 0 1

    vector<int> nums2 = {3,2,4};
    vector<int> ans2 = sol.twoSum(nums2,6);

    cout << "Test 2 : ";
    cout << ans2[0] << " " << ans2[1] << endl;
    // Expected : 1 2

    vector<int> nums3 = {3,3};
    vector<int> ans3 = sol.twoSum(nums3,6);

    cout << "Test 3 : ";
    cout << ans3[0] << " " << ans3[1] << endl;
    // Expected : 0 1

    return 0;
}