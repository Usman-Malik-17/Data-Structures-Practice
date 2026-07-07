#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 283. Move Zeroes
// Link     : https://leetcode.com/problems/move-zeroes/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Move all 0s to end while maintaining relative order of
// non-zero elements. Must be done in-place.
//
// Example:
// nums = [0,1,0,3,12]
// Output: [1,3,12,0,0]
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Extra Array
    // Time Complexity  : O(n)
    // Space Complexity : O(n) - extra array
    // ============================================================
    void moveZeroesBrute(vector<int>& nums) {
        vector<int> ans;
        int count = 0;

        // Non-zero elements first
        for (auto i : nums) {
            if (i != 0) ans.push_back(i);
            else count++;
        }
        // Zeroes at end
        for (int i = 0; i < count; i++) ans.push_back(0);

        nums = ans;
    }

    // ============================================================
    // Approach 2: Two Pointers (Optimal)
    // Time Complexity  : O(n) - single pass
    // Space Complexity : O(1) - in-place
    //
    // Key Trick:
    // l = position where next non-zero should go
    // r = current element being checked
    // When non-zero found at r — swap with l, increment l
    // All elements before l are non-zero
    // All elements from l to r are zero
    //
    // Example:
    // nums = [0,1,0,3,12], l=0
    // r=0: 0  → skip
    // r=1: 1  → swap(nums[0],nums[1]) → [1,0,0,3,12], l=1
    // r=2: 0  → skip
    // r=3: 3  → swap(nums[1],nums[3]) → [1,3,0,0,12], l=2
    // r=4: 12 → swap(nums[2],nums[4]) → [1,3,12,0,0], l=3
    // Result: [1,3,12,0,0] ✅
    // ============================================================
    void moveZeroes(vector<int>& nums) {
        int l = 0;
        for (int r = 0; r < nums.size(); r++) {
            if (nums[r] != 0) {
                swap(nums[l], nums[r]);
                l++;
            }
        }
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> nums1 = {0, 1, 0, 3, 12};
    sol.moveZeroes(nums1);
    cout << "Test 1: ";
    for (int x : nums1) cout << x << " ";
    cout << endl;
    // Expected: 1 3 12 0 0

    vector<int> nums2 = {0};
    sol.moveZeroes(nums2);
    cout << "Test 2: ";
    for (int x : nums2) cout << x << " ";
    cout << endl;
    // Expected: 0

    vector<int> nums3 = {1, 2, 3};
    sol.moveZeroes(nums3);
    cout << "Test 3: ";
    for (int x : nums3) cout << x << " ";
    cout << endl;
    // Expected: 1 2 3

    vector<int> nums4 = {0, 0, 1};
    sol.moveZeroes(nums4);
    cout << "Test 4: ";
    for (int x : nums4) cout << x << " ";
    cout << endl;
    // Expected: 1 0 0

    return 0;
}