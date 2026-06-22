#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 42. Trapping Rain Water
// Link     : https://leetcode.com/problems/trapping-rain-water/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given an array of heights representing an elevation map, calculate
// how much rainwater can be trapped after raining.
//
// Water trapped at any index = min(maxLeft, maxRight) - height[i]
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Prefix Max + Suffix Max (Brute Force)
    // Time Complexity  : O(n) - three separate loops
    // Space Complexity : O(n) - two extra arrays
    // ============================================================
    int trapBrute(vector<int>& heights) {
        int n = heights.size();
        vector<int> prefixMax(n);
        vector<int> suffixMax(n);

        prefixMax[0] = heights[0];
        for (int i = 1; i < n; i++) {
            prefixMax[i] = max(prefixMax[i - 1], heights[i]);
        }

        suffixMax[n - 1] = heights[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            suffixMax[i] = max(suffixMax[i + 1], heights[i]);
        }

        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += min(prefixMax[i], suffixMax[i]) - heights[i];
        }
        return sum;
    }

    // ============================================================
    // Approach 2: Two Pointers (Optimal)
    // Time Complexity  : O(n) - single pass
    // Space Complexity : O(1) - no extra space
    //
    // Key Trick:
    // We maintain leftMax and rightMax on the fly using two pointers.
    // When leftMax <= rightMax, water at left pointer is guaranteed
    // by leftMax — right side has a taller wall somewhere.
    // When rightMax < leftMax, same logic applies for right pointer.
    // So we never need to know the exact middle heights!
    // ============================================================
    int trap(vector<int>& heights) {
        int l = 0;
        int r = heights.size() - 1;
        int leftMax = 0;
        int rightMax = 0;
        int sum = 0;

        while (l < r) {
            leftMax = max(heights[l], leftMax);
            rightMax = max(heights[r], rightMax);

            if (leftMax <= rightMax) {
                sum += leftMax - heights[l];
                l++;
            } else {
                sum += rightMax - heights[r];
                r--;
            }
        }
        return sum;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> heights1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "Test 1: " << sol.trap(heights1) << endl;
    // Expected: 6

    vector<int> heights2 = {4, 2, 0, 3, 2, 5};
    cout << "Test 2: " << sol.trap(heights2) << endl;
    // Expected: 9

    return 0;
}