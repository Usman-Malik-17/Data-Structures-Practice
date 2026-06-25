#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 239. Sliding Window Maximum
// Link     : https://leetcode.com/problems/sliding-window-maximum/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given array nums and window size k, return the maximum of each
// sliding window as it moves from left to right.
//
// Key Trick — Monotonic Decreasing Deque:
// Maintain a deque of indexes in decreasing order of their values.
// Front of deque = index of current window's maximum.
//
// For each index i:
//   1. Remove front if it's outside current window (i - k)
//   2. Remove back while back's value <= current value
//      (smaller elements can never be maximum while current exists)
//   3. If window is complete (i >= k-1), front is the maximum
//   4. Push current index to back
//
// Example: nums = [1,3,-1,-3,5,3,6,7], k = 3
// i=0: dq=[0]
// i=1: pop 0(1<=3), dq=[1]
// i=2: dq=[1,2],        ans=[3]  (nums[1]=3)
// i=3: dq=[1,2,3],      ans=[3]  (nums[1]=3)
// i=4: pop 3,2,1(all<=5), dq=[4], ans=[5]
// i=5: dq=[4,5],        ans=[5]  (nums[4]=5)
// i=6: pop 5,4(<=6), dq=[6],     ans=[6]
// i=7: pop 6(<=7), dq=[7],       ans=[7]
// Output: [3,3,5,5,6,7] ✅
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Brute Force
    // Time Complexity  : O(n * k) - for each window find max
    // Space Complexity : O(1)
    // ============================================================
    vector<int> maxSlidingWindowBrute(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans;

        for (int i = 0; i <= n - k; i++) {
            int maxi = INT_MIN;
            for (int j = i; j < i + k; j++) {
                maxi = max(maxi, nums[j]);
            }
            ans.push_back(maxi);
        }
        return ans;
    }

    // ============================================================
    // Approach 2: Monotonic Decreasing Deque (Optimal)
    // Time Complexity  : O(n) - each element pushed/popped once
    // Space Complexity : O(k) - deque size at most k
    // ============================================================
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;
        vector<int> ans;

        for (int i = 0; i < nums.size(); i++) {
            // Remove front if outside current window
            if (!dq.empty() && dq.front() == i - k) {
                dq.pop_front();
            }

            // Remove smaller elements from back — they can never be max
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }

            // Window complete — front is current maximum
            if (i >= k - 1) {
                int val = dq.empty() ? nums[i] : nums[dq.front()];
                ans.push_back(val);
            }

            dq.push_back(i);
        }
        return ans;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> nums1 = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> ans1 = sol.maxSlidingWindow(nums1, 3);
    cout << "Test 1: ";
    for (int x : ans1) cout << x << " ";
    cout << endl;
    // Expected: 3 3 5 5 6 7

    vector<int> nums2 = {1};
    vector<int> ans2 = sol.maxSlidingWindow(nums2, 1);
    cout << "Test 2: ";
    for (int x : ans2) cout << x << " ";
    cout << endl;
    // Expected: 1

    vector<int> nums3 = {1, -1};
    vector<int> ans3 = sol.maxSlidingWindow(nums3, 1);
    cout << "Test 3: ";
    for (int x : ans3) cout << x << " ";
    cout << endl;
    // Expected: 1 -1

    return 0;
}