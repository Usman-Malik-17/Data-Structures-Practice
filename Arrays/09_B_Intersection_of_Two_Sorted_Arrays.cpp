#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : Intersection of Two Sorted Arrays
// Link     : https://www.geeksforgeeks.org/intersection-of-two-sorted-arrays/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given two sorted arrays, return their intersection —
// common distinct elements in sorted order.
//
// Example:
// arr1 = [1,2,2,3,4], arr2 = [2,2,4,6,7,8]
// Output: [2,4]
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Brute Force — Linear Search + Set
    // Time Complexity  : O(m*n) - for each element linear search
    // Space Complexity : O(min(m,n)) - set size
    // ============================================================
    bool check(int elem, vector<int>& nums2) {
        for (int i = 0; i < nums2.size(); i++) {
            if (elem == nums2[i]) return true;
        }
        return false;
    }

    vector<int> intersectionBrute(vector<int>& nums1, vector<int>& nums2) {
        set<int> s;
        vector<int> ans;
        for (int i = 0; i < nums1.size(); i++) {
            if (check(nums1[i], nums2)) {
                s.insert(nums1[i]);
            }
        }
        for (auto i : s) ans.push_back(i);
        return ans;
    }

    // ============================================================
    // Approach 2: Two Pointers (Optimal)
    // Time Complexity  : O(m+n) - single pass both arrays
    // Space Complexity : O(1) - no extra space (excluding result)
    //
    // Key Trick:
    // Since arrays are sorted, use two pointers p1 and p2.
    // Equal   → add to result (if not duplicate), move both
    // p1 < p2 → move p1 forward
    // p1 > p2 → move p2 forward
    //
    // Duplicate check: ans.back() != current element
    //
    // Example:
    // arr1=[1,2,2,3,4], arr2=[2,2,4,6,7,8]
    // p1=0,p2=0: 1<2 → p1++
    // p1=1,p2=0: 2==2 → add 2, p1++, p2++
    // p1=2,p2=1: 2==2 → duplicate skip, p1++, p2++
    // p1=3,p2=2: 3<4 → p1++
    // p1=4,p2=2: 4==4 → add 4, p1++, p2++
    // Result: [2,4] ✅
    // ============================================================
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans;
        int p1 = 0, p2 = 0;

        while (p1 < nums1.size() && p2 < nums2.size()) {
            if (nums1[p1] == nums2[p2]) {
                // Add only if not duplicate
                if (ans.empty() || ans.back() != nums1[p1]) {
                    ans.push_back(nums1[p1]);
                }
                p1++;
                p2++;
            } else if (nums1[p1] < nums2[p2]) {
                p1++;
            } else {
                p2++;
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

    vector<int> arr1 = {1, 2, 3, 4};
    vector<int> arr2 = {2, 4, 6, 7, 8};
    vector<int> ans1 = sol.intersection(arr1, arr2);
    cout << "Test 1: ";
    for (int x : ans1) cout << x << " ";
    cout << endl;
    // Expected: 2 4

    vector<int> arr3 = {1, 2, 2, 3, 4};
    vector<int> arr4 = {2, 2, 4, 6, 7, 8};
    vector<int> ans2 = sol.intersection(arr3, arr4);
    cout << "Test 2: ";
    for (int x : ans2) cout << x << " ";
    cout << endl;
    // Expected: 2 4

    vector<int> arr5 = {1, 2};
    vector<int> arr6 = {3, 4};
    vector<int> ans3 = sol.intersection(arr5, arr6);
    cout << "Test 3: ";
    for (int x : ans3) cout << x << " ";
    cout << endl;
    // Expected: (empty)

    return 0;
}