#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 26. Remove Duplicates from Sorted Array
// Link     : https://leetcode.com/problems/remove-duplicates-from-sorted-array/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given sorted array, remove duplicates in-place.
// Return k = number of unique elements.
// First k elements should contain unique elements in order.
//
// Example:
// nums = [1,1,2,3,3]
// Output: k=3, nums=[1,2,3,_,_]
// ----------------------------------------------------------------

class Solution
{
public:
    // ============================================================
    // Approach 1: Set
    // Time Complexity  : O(n log n) - set insertion (Brute Force)
    // Space Complexity : O(n) - set
    // ============================================================
    int removeDuplicatesSet(vector<int> &nums)
    {
        set<int> ans;
        for (int i = 0; i < nums.size(); i++)
        {
            ans.insert(nums[i]);
        }
        int size = 0;
        for (auto i : ans)
        {
            nums[size++] = i;
        }
        return size;
    }



    // ============================================================
    // Approach 2: Extra Array  Better
    // Time Complexity  : O(n)
    // Space Complexity : O(n) - extra array
    // ============================================================
    int removeDuplicatesBrute(vector<int> &nums)
    {
        int k = nums.size();
        vector<int> ans;
        ans.push_back(nums[0]);
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] != nums[i - 1])
            {
                ans.push_back(nums[i]);
            }
            else
            {
                k--;
            }
        }
        nums = ans;
        return k;
    }
    // ============================================================
    // Approach 3: Two Pointers (Optimal)
    // Time Complexity  : O(n) - single pass
    // Space Complexity : O(1) - in-place, no extra space
    //
    // Key Trick:
    // l = last unique element position
    // r = current element being checked
    // When nums[r] != nums[r-1] — new unique found
    // Place it at l+1 and increment l
    //
    // Example:
    // nums = [1,1,2,3,3]
    // l=0
    // r=1: 1==1 → skip
    // r=2: 2!=1 → l=1, nums[1]=2 → [1,2,2,3,3]
    // r=3: 3!=2 → l=2, nums[2]=3 → [1,2,3,3,3]
    // r=4: 3==3 → skip
    // return l+1 = 3 ✅
    // ============================================================
    int removeDuplicates(vector<int> &nums)
    {
        int l = 0;
        for (int r = 1; r < nums.size(); r++)
        {
            if (nums[r] != nums[r - 1])
            {
                l++;
                nums[l] = nums[r];
            }
        }
        return l + 1;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main()
{
    Solution sol;

    vector<int> nums1 = {1, 1, 2};
    cout << "Test 1: " << sol.removeDuplicates(nums1) << endl;
    // Expected: 2

    vector<int> nums2 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    cout << "Test 2: " << sol.removeDuplicates(nums2) << endl;
    // Expected: 5

    vector<int> nums3 = {1, 2, 3, 4, 5};
    cout << "Test 3: " << sol.removeDuplicates(nums3) << endl;
    // Expected: 5

    vector<int> nums4 = {1, 1, 1, 1};
    cout << "Test 4: " << sol.removeDuplicates(nums4) << endl;
    // Expected: 1

    return 0;
}