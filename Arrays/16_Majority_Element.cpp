#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : Majority Element
// Link     : https://leetcode.com/problems/majority-element/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given an integer array nums, return the majority element.
//
// The majority element is the element that appears
// more than floor(n/2) times.
//
// It is guaranteed that the majority element always exists.
//
// Example:
// nums = [2,2,1,1,1,2,2]
//
// Frequency:
// 2 -> 4
// 1 -> 3
//
// Answer = 2
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Brute Force
    // Time Complexity  : O(n²)
    // Space Complexity : O(1)
    //
    // Count the frequency of every element using nested loops.
    // If frequency > n/2, return that element.
    // ============================================================
    int majorityElementBrute(vector<int>& nums) {

        int n = nums.size();

        for (int i = 0; i < n; i++) {

            int count = 0;

            for (int j = 0; j < n; j++) {

                if (nums[i] == nums[j])
                    count++;
            }

            if (count > n / 2)
                return nums[i];
        }

        return -1;
    }

    // ============================================================
    // Approach 2: HashMap
    // Time Complexity  : O(n)
    // Space Complexity : O(n)
    //
    // Count the frequency of every element using a HashMap.
    // The element with frequency greater than n/2 is the answer.
    // ============================================================
    int majorityElementHashMap(vector<int>& nums) {

        unordered_map<int, int> freq;

        for (int num : nums)
            freq[num]++;

        for (auto it : freq) {

            if (it.second > nums.size() / 2)
                return it.first;
        }

        return -1;
    }

    // ============================================================
    // Approach 3: Moore's Voting Algorithm (Optimal)
    // Time Complexity  : O(n)
    // Space Complexity : O(1)
    //
    // Key Idea:
    //
    // Maintain:
    // candidate -> possible majority element
    // count     -> vote count
    //
    // Rules:
    //
    // 1. If count becomes 0,
    //    choose current element as new candidate.
    //
    // 2. If current element == candidate,
    //    increment count.
    //
    // 3. Otherwise,
    //    decrement count.
    //
    // Why does it work?
    //
    // Every different element cancels one occurrence
    // of the current candidate.
    //
    // Since the majority element appears more than n/2 times,
    // it can never be completely cancelled.
    //
    // Example:
    //
    // nums = [2,2,1,1,1,2,2]
    //
    // i   num   candidate   count
    // ----------------------------
    // 0    2        2         1
    // 1    2        2         2
    // 2    1        2         1
    // 3    1        2         0
    // 4    1        1         1
    // 5    2        1         0
    // 6    2        2         1
    //
    // Final Candidate = 2
    //
    // Note:
    // Since the problem guarantees a majority element,
    // no verification pass is required.
    // ============================================================
    int majorityElement(vector<int>& nums) {

        int candidate = 0;
        int count = 0;

        for (int num : nums) {

            if (count == 0) {
                candidate = num;
                count = 1;
            }
            else if (num == candidate) {
                count++;
            }
            else {
                count--;
            }
        }

        return candidate;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================

int main() {

    Solution sol;

    vector<int> nums1 = {3,2,3};
    cout << "Test 1: " << sol.majorityElement(nums1) << endl;
    // Expected: 3

    vector<int> nums2 = {2,2,1,1,1,2,2};
    cout << "Test 2: " << sol.majorityElement(nums2) << endl;
    // Expected: 2

    vector<int> nums3 = {5};
    cout << "Test 3: " << sol.majorityElement(nums3) << endl;
    // Expected: 5

    vector<int> nums4 = {6,6,6,7,7};
    cout << "Test 4: " << sol.majorityElement(nums4) << endl;
    // Expected: 6

    return 0;
}