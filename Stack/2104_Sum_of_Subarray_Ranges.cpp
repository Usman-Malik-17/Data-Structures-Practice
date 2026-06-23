#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 2104. Sum of Subarray Ranges
// Link     : https://leetcode.com/problems/sum-of-subarray-ranges/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Return the sum of ranges of all subarrays.
// Range of a subarray = max element - min element
//
// Key Insight:
// Sum of Ranges = Sum of Subarray Maximums - Sum of Subarray Minimums
//
// Contribution Technique:
// For each element, calculate how many subarrays it is the
// minimum/maximum of using Previous and Next smaller/greater indexes.
// Contribution = arr[i] * left_count * right_count
//
// Why <= on one side?
// To avoid double counting when equal elements exist.
// For min: Left uses strict >=, Right uses strict >
// For max: Left uses strict <=, Right uses strict 
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Brute Force
    // Time Complexity  : O(n²) - nested loop
    // Space Complexity : O(1) - no extra space
    // ============================================================
    long long subArrayRangesBrute(vector<int>& nums) {
        int n = nums.size();
        long long sum = 0;

        for (int i = 0; i < n; i++) {
            int minVal = nums[i], maxVal = nums[i];
            for (int j = i; j < n; j++) {
                minVal = min(minVal, nums[j]);
                maxVal = max(maxVal, nums[j]);
                sum += maxVal - minVal;
            }
        }
        return sum;
    }

    // ============================================================
    // Approach 2: Contribution Technique (Optimal)
    // Time Complexity  : O(n) - each element pushed/popped once
    // Space Complexity : O(n) - stack + auxiliary arrays
    // ============================================================

    // ---- Minimum Helpers ----
    int prevMinHelper(stack<int>& st, vector<int>& arr, int index) {
        while (!st.empty() && arr[st.top()] >= arr[index]) {
            st.pop();
        }
        int ans = st.empty() ? -1 : st.top();
        st.push(index);
        return ans;
    }

    void prevMinElementIndex(vector<int>& pme, vector<int>& arr) {
        stack<int> st;
        for (int i = 0; i < arr.size(); i++) {
            pme[i] = prevMinHelper(st, arr, i);
        }
    }

    int nextMinEqualHelper(stack<int>& st, vector<int>& arr, int index) {
        while (!st.empty() && arr[st.top()] > arr[index]) {
            st.pop();
        }
        int ans = st.empty() ? arr.size() : st.top();
        st.push(index);
        return ans;
    }

    void nextMinEqualElementIndex(vector<int>& nmee, vector<int>& arr) {
        stack<int> st;
        for (int i = arr.size() - 1; i >= 0; i--) {
            nmee[i] = nextMinEqualHelper(st, arr, i);
        }
    }

    long long sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        vector<int> pme(n);
        vector<int> nmee(n);
        prevMinElementIndex(pme, arr);
        nextMinEqualElementIndex(nmee, arr);
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            sum += (long long)arr[i] * (i - pme[i]) * (nmee[i] - i);
        }
        return sum;
    }

    // ---- Maximum Helpers ----
    int prevMaxHelper(stack<int>& st, vector<int>& arr, int index) {
        while (!st.empty() && arr[st.top()] <= arr[index]) {
            st.pop();
        }
        int ans = st.empty() ? -1 : st.top();
        st.push(index);
        return ans;
    }

    void prevMaxElementIndex(vector<int>& ple, vector<int>& arr) {
        stack<int> st;
        for (int i = 0; i < arr.size(); i++) {
            ple[i] = prevMaxHelper(st, arr, i);
        }
    }

    int nextMaxEqualHelper(stack<int>& st, vector<int>& arr, int index) {
        while (!st.empty() && arr[st.top()] < arr[index]) {
            st.pop();
        }
        int ans = st.empty() ? arr.size() : st.top();
        st.push(index);
        return ans;
    }

    void nextMaxEqualElementIndex(vector<int>& nlee, vector<int>& arr) {
        stack<int> st;
        for (int i = arr.size() - 1; i >= 0; i--) {
            nlee[i] = nextMaxEqualHelper(st, arr, i);
        }
    }

    long long sumSubarrayMaxs(vector<int>& arr) {
        int n = arr.size();
        vector<int> ple(n);
        vector<int> nlee(n);
        prevMaxElementIndex(ple, arr);
        nextMaxEqualElementIndex(nlee, arr);
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            sum += (long long)arr[i] * (i - ple[i]) * (nlee[i] - i);
        }
        return sum;
    }

    long long subArrayRanges(vector<int>& nums) {
        return sumSubarrayMaxs(nums) - sumSubarrayMins(nums);
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> nums1 = {1, 2, 3};
    cout << "Test 1: " << sol.subArrayRanges(nums1) << endl;
    // Expected: 4

    vector<int> nums2 = {1, 3, 3};
    cout << "Test 2: " << sol.subArrayRanges(nums2) << endl;
    // Expected: 4

    vector<int> nums3 = {4, -2, -3, 4, 1};
    cout << "Test 3: " << sol.subArrayRanges(nums3) << endl;
    // Expected: 59

    return 0;
}