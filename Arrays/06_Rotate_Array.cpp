#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 189. Rotate Array
// Link     : https://leetcode.com/problems/rotate-array/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Rotate array to the right by k steps.
//
// Example:
// nums = [1,2,3,4,5,6,7], k = 3
// Output: [5,6,7,1,2,3,4]
// ----------------------------------------------------------------

class Solution
{
public:
    // ============================================================
    // Approach 1: Extra Array
    // Time Complexity  : O(n)
    // Space Complexity : O(n) - extra array
    //
    // Key Trick:
    // Last k elements come to front, rest shift to back.
    // ============================================================
    void rotateBrute(vector<int> &nums, int k)
    {
        vector<int> ans;
        int n = nums.size();
        k = k % n;

        // Last k elements first
        for (int i = k; i >= 1; i--)
        {
            ans.push_back(nums[n - i]);
        }
        // Then remaining elements
        for (int i = 0; i <= n - k - 1; i++)
        {
            ans.push_back(nums[i]);
        }
        nums = ans;
    }

    // ============================================================
    // Approach 2: Reverse Algorithm (Optimal)
    // Time Complexity  : O(n) - three reverses = O(3n) = O(n)
    // Space Complexity : O(1) - in-place
    //
    // Key Trick — 3 Step Reverse:
    // Step 1: Reverse first (n-k) elements
    // Step 2: Reverse last k elements
    // Step 3: Reverse entire array
    //
    // Example: nums = [1,2,3,4,5,6,7], k=3
    // n-k = 4
    // Step 1: reverse [1,2,3,4] → [4,3,2,1,5,6,7]
    // Step 2: reverse [5,6,7]   → [4,3,2,1,7,6,5]
    // Step 3: reverse all       → [5,6,7,1,2,3,4] ✅
    // ============================================================
    void rotate(vector<int> &arr, int k)
    {
        int n = arr.size();
        k = k % n; // handle k > n
        reverse(arr.begin(), arr.begin() + n - k);
        reverse(arr.begin() + n - k, arr.end());
        reverse(arr.begin(), arr.end());
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main()
{
    Solution sol;

    vector<int> nums1 = {1, 2, 3, 4, 5, 6, 7};
    sol.rotate(nums1, 3);
    cout << "Test 1: ";
    for (int x : nums1)
        cout << x << " ";
    cout << endl;
    // Expected: 5 6 7 1 2 3 4

    vector<int> nums2 = {-1, -100, 3, 99};
    sol.rotate(nums2, 2);
    cout << "Test 2: ";
    for (int x : nums2)
        cout << x << " ";
    cout << endl;
    // Expected: 3 99 -1 -100

    vector<int> nums3 = {1, 2, 3};
    sol.rotate(nums3, 4);
    cout << "Test 3: ";
    for (int x : nums3)
        cout << x << " ";
    cout << endl;
    // Expected: 3 1 2

    return 0;
}