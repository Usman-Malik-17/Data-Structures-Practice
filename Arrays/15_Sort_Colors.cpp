#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : Sort Colors (Dutch National Flag Algorithm)
// Link     : https://leetcode.com/problems/sort-colors/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given an array containing only 0s, 1s, and 2s,
// sort the array in-place without using the built-in sort() function.
//
// Colors Representation:
// 0 -> Red
// 1 -> White
// 2 -> Blue
//
// Example:
// nums = [2,0,2,1,1,0]
//
// Output:
// [0,0,1,1,2,2]
//
// Follow-up:
// Solve it in ONE PASS using CONSTANT extra space.
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Counting Method (Two Pass)
    // Time Complexity  : O(n)
    // Space Complexity : O(1)
    //
    // Count the number of 0s, 1s, and 2s.
    // Overwrite the array according to their frequencies.
    //
    // Note:
    // Although this runs in O(n), it requires two passes.
    // ============================================================
    void sortColorsCounting(vector<int>& nums) {

        int zero = 0, one = 0, two = 0;

        for (int num : nums) {
            if (num == 0)
                zero++;
            else if (num == 1)
                one++;
            else
                two++;
        }

        int index = 0;

        while (zero--) nums[index++] = 0;
        while (one--)  nums[index++] = 1;
        while (two--)  nums[index++] = 2;
    }

    // ============================================================
    // Approach 2: Dutch National Flag Algorithm (Optimal)
    // Time Complexity  : O(n)
    // Space Complexity : O(1)
    //
    // One Pass Algorithm
    //
    // Three pointers:
    //
    // low  -> Next position for 0
    // mid  -> Current element
    // high -> Next position for 2
    //
    // Rules:
    //
    // nums[mid] == 0
    //     swap(low, mid)
    //     low++
    //     mid++
    //
    // nums[mid] == 1
    //     mid++
    //
    // nums[mid] == 2
    //     swap(mid, high)
    //     high--
    //     DON'T increment mid
    //
    // Why not increment mid after swapping with high?
    //
    // Because the element coming from high is unprocessed.
    // It could be 0, 1, or 2, so we must examine it again.
    //
    // Example:
    //
    // nums = [2,0,2,1,1,0]
    //
    // low=0 mid=0 high=5
    //
    // Step 1:
    // swap(mid, high)
    // [0,0,2,1,1,2]
    //
    // high--
    //
    // mid stays at 0 because new element is unprocessed.
    // ============================================================
    void sortColors(vector<int>& nums) {

        int low = 0;
        int mid = 0;
        int high = nums.size() - 1;

        while (mid <= high) {

            if (nums[mid] == 0) {

                swap(nums[low], nums[mid]);
                low++;
                mid++;

            }
            else if (nums[mid] == 1) {

                mid++;

            }
            else {

                swap(nums[mid], nums[high]);
                high--;

            }
        }
    }
};

// ============================================================
// Main - Local Testing
// ============================================================

int main() {

    Solution sol;

    vector<int> nums1 = {2,0,2,1,1,0};
    sol.sortColors(nums1);

    cout << "Test 1: ";
    for (int x : nums1)
        cout << x << " ";
    cout << endl;
    // Expected: 0 0 1 1 2 2

    vector<int> nums2 = {2,0,1};
    sol.sortColors(nums2);

    cout << "Test 2: ";
    for (int x : nums2)
        cout << x << " ";
    cout << endl;
    // Expected: 0 1 2

    vector<int> nums3 = {0};
    sol.sortColors(nums3);

    cout << "Test 3: ";
    for (int x : nums3)
        cout << x << " ";
    cout << endl;
    // Expected: 0

    vector<int> nums4 = {1,2,0};
    sol.sortColors(nums4);

    cout << "Test 4: ";
    for (int x : nums4)
        cout << x << " ";
    cout << endl;
    // Expected: 0 1 2

    return 0;
}