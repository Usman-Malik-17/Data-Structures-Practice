#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : Rearrange Array Elements by Sign
// Link     : https://leetcode.com/problems/rearrange-array-elements-by-sign/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given an array containing an equal number of positive
// and negative integers, rearrange the array such that:
//
// 1. The array starts with a positive number.
// 2. Positive and negative numbers appear alternately.
// 3. Relative order of positive numbers is preserved.
// 4. Relative order of negative numbers is preserved.
//
// Example:
//
// nums = [3,1,-2,-5,2,-4]
//
// Positive = [3,1,2]
// Negative = [-2,-5,-4]
//
// Output:
// [3,-2,1,-5,2,-4]
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Two Temporary Arrays
    // Time Complexity  : O(n)
    // Space Complexity : O(n)
    //
    // Store all positive numbers in one vector
    // and all negative numbers in another.
    //
    // Finally, merge them alternately into the answer.
    // ============================================================
    vector<int> rearrangeArrayBrute(vector<int>& nums) {

        vector<int> positive;
        vector<int> negative;
        vector<int> ans;

        for (int num : nums) {

            if (num > 0)
                positive.push_back(num);
            else
                negative.push_back(num);
        }

        int pos = 0;
        int neg = 0;

        while (pos < positive.size()) {

            ans.push_back(positive[pos++]);
            ans.push_back(negative[neg++]);
        }

        return ans;
    }

    // ============================================================
    // Approach 2: Direct Placement (Optimal)
    // Time Complexity  : O(n)
    // Space Complexity : O(n)
    //
    // Key Idea:
    //
    // Positive numbers always occupy:
    // 0, 2, 4, 6...
    //
    // Negative numbers always occupy:
    // 1, 3, 5, 7...
    //
    // Maintain two indices:
    //
    // pos -> next even index
    // neg -> next odd index
    //
    // Traverse the array once and directly place each
    // element into its correct position.
    //
    // Example:
    //
    // nums = [3,1,-2,-5,2,-4]
    //
    // ans = [_,_,_,_,_,_]
    //
    // 3  -> ans[0]
    // 1  -> ans[2]
    // -2 -> ans[1]
    // -5 -> ans[3]
    // 2  -> ans[4]
    // -4 -> ans[5]
    //
    // Result:
    // [3,-2,1,-5,2,-4]
    // ============================================================
    vector<int> rearrangeArray(vector<int>& nums) {

        vector<int> ans(nums.size());

        int pos = 0;
        int neg = 1;

        for (int num : nums) {

            if (num > 0) {

                ans[pos] = num;
                pos += 2;

            }
            else {

                ans[neg] = num;
                neg += 2;
            }
        }

        return ans;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================

int main() {

    Solution sol;

    vector<int> nums1 = {3,1,-2,-5,2,-4};
    vector<int> ans1 = sol.rearrangeArray(nums1);

    cout << "Test 1: ";
    for (int x : ans1)
        cout << x << " ";
    cout << endl;
    // Expected: 3 -2 1 -5 2 -4

    vector<int> nums2 = {-1,1};
    vector<int> ans2 = sol.rearrangeArray(nums2);

    cout << "Test 2: ";
    for (int x : ans2)
        cout << x << " ";
    cout << endl;
    // Expected: 1 -1

    vector<int> nums3 = {5,-3,4,-2};
    vector<int> ans3 = sol.rearrangeArray(nums3);

    cout << "Test 3: ";
    for (int x : ans3)
        cout << x << " ";
    cout << endl;
    // Expected: 5 -3 4 -2

    return 0;
}