#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : Longest Subarray with Sum K
// Link     : https://www.geeksforgeeks.org/longest-sub-array-sum-k/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Find length of longest subarray with sum equal to k.
// Array can contain positive, negative, and zero elements.
//
// Example:
// arr = [10,5,2,7,1,-10], k = 15
// Subarrays with sum 15: [5,2,7,1], [10,5], [10,5,2,7,1,-10]
// Longest = 6 ✅
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Brute Force — Nested Loop
    // Time Complexity  : O(n^2) - check all subarrays
    // Space Complexity : O(1)
    // ============================================================
    int longestSubarrayBrute(vector<int>& arr, int k) {
        int maxLength = 0;
        for (int i = 0; i < arr.size(); i++) {
            int sum = 0;
            for (int j = i; j < arr.size(); j++) {
                sum += arr[j];
                if (sum == k) {
                    maxLength = max(maxLength, j - i + 1);
                }
            }
        }
        return maxLength;
    }

    // ============================================================
    // Approach 2: Sliding Window (Only Positive Arrays)
    // Time Complexity  : O(n) - single pass
    // Space Complexity : O(1)
    //
    // Note: Only works for positive numbers!
    // Negative numbers break the monotonic property of sliding window.
    // ============================================================
    int longestSubarrayPositive(vector<int>& arr, int k) {
        int maxLength = 0;
        int l = 0, sum = 0;

        for (int r = 0; r < arr.size(); r++) {
            sum += arr[r];
            while (sum > k && l <= r) {
                sum -= arr[l++];
            }
            if (sum == k) {
                maxLength = max(maxLength, r - l + 1);
            }
        }
        return maxLength;
    }

    // ============================================================
    // Approach 3: Prefix Sum + HashMap (Optimal)
    // Time Complexity  : O(n) - single pass
    // Space Complexity : O(n) - hashmap
    //
    // Key Trick — Prefix Sum:
    // At index i, if sum == k → subarray [0..i] is valid
    // If sum - k exists in map → subarray [map[sum-k]+1..i] is valid
    // Store FIRST occurrence of each prefix sum to maximize length.
    //
    // Works for positive, negative, and zero elements!
    //
    // Example:
    // arr=[10,5,2,7,1,-10], k=15
    // i=0: sum=10, m={10:0}
    // i=1: sum=15==k → maxLen=2
    // i=2: sum=17, prevS=2, not in m, m={10:0,15:1,17:2}
    // i=3: sum=24, prevS=9, not in m, m={...,24:3}
    // i=4: sum=25, prevS=10, m[10]=0 → len=4-0=4, maxLen=4
    // i=5: sum=15==k → maxLen=max(4,6)=6 ✅
    // ============================================================
    int longestSubarray(vector<int>& arr, int k) {
        unordered_map<int, int> m;
        int sum = 0, maxLen = 0;

        for (int i = 0; i < arr.size(); i++) {
            sum += arr[i];

            // Subarray from index 0 to i
            if (sum == k) {
                maxLen = max(i + 1, maxLen);
            } else {
                // Check if sum-k prefix exists
                int prevS = sum - k;
                if (m.find(prevS) != m.end()) {
                    maxLen = max(i - m[prevS], maxLen);
                }
            }

            // Store first occurrence only — maximize length
            if (m.find(sum) == m.end()) {
                m[sum] = i;
            }
        }
        return maxLen;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> arr1 = {10, 5, 2, 7, 1, -10};
    cout << "Test 1: " << sol.longestSubarray(arr1, 15) << endl;
    // Expected: 6

    vector<int> arr2 = {-5, 8, -14, 2, 4, 12};
    cout << "Test 2: " << sol.longestSubarray(arr2, -5) << endl;
    // Expected: 5

    vector<int> arr3 = {10, -10, 20, 30};
    cout << "Test 3: " << sol.longestSubarray(arr3, 5) << endl;
    // Expected: 0

    vector<int> arr4 = {1, 2, 3, 4, 5};
    cout << "Test 4: " << sol.longestSubarray(arr4, 9) << endl;
    // Expected: 3

    return 0;
}