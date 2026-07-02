#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 1423. Maximum Points You Can Obtain from Cards
// Link     : https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Pick exactly k cards from either end of array to maximize score.
//
// Key Trick — Sliding Window:
// Instead of thinking which cards to PICK, think which cards to LEAVE.
// We always pick k cards — so we leave (n-k) cards in the middle.
// Find the minimum sum subarray of size (n-k) — answer = total - min.
//
// But even simpler — sliding window on picked cards:
// Start with first k cards from left.
// Slide window: remove one from left, add one from right.
// Track maximum at each step.
//
// Example: cardPoints = [1,2,3,4,5,6,1], k = 3
// Initial window (left k=3):  [1,2,3] → sum = 6
// Slide 1: remove 3, add 1    [1,2,1] → sum = 4  (wrong — see below)
//
// i=0: sum -= cardPoints[k-0-1=2] = 3 → sum=3, += cardPoints[n-0-1=6]=1 → sum=4
// i=1: sum -= cardPoints[k-1-1=1] = 2 → sum=2, += cardPoints[n-1-1=5]=6 → sum=8
// i=2: sum -= cardPoints[k-2-1=0] = 1 → sum=7, += cardPoints[n-2-1=4]=5 → sum=12 ✅
//
// Time Complexity  : O(k) - single pass
// Space Complexity : O(1) - no extra space
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Brute Force
    // Time Complexity  : O(k^2) - try all combinations
    // Space Complexity : O(1)
    // ============================================================
    int maxScoreBrute(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int maxi = 0;

        for (int left = 0; left <= k; left++) {
            int right = k - left;
            int sum = 0;
            for (int i = 0; i < left; i++) sum += cardPoints[i];
            for (int i = 0; i < right; i++) sum += cardPoints[n - 1 - i];
            maxi = max(maxi, sum);
        }
        return maxi;
    }

    // ============================================================
    // Approach 2: Sliding Window (Optimal)
    // Time Complexity  : O(k) - single pass
    // Space Complexity : O(1)
    //
    // Start with sum of first k cards (all from left).
    // Slide: remove one from left side, add one from right side.
    // Track maximum at each step.
    // ============================================================
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();

        // Initial sum — first k cards from left
        int sum = 0;
        for (int i = 0; i < k; i++) sum += cardPoints[i];
        int maxi = sum;

        // Slide window — remove from left, add from right
        for (int i = 0; i < k; i++) {
            sum -= cardPoints[k - i - 1];   // remove from left
            sum += cardPoints[n - i - 1];   // add from right
            maxi = max(maxi, sum);
        }
        return maxi;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> cp1 = {1, 2, 3, 4, 5, 6, 1};
    cout << "Test 1: " << sol.maxScore(cp1, 3) << endl;
    // Expected: 12

    vector<int> cp2 = {2, 2, 2};
    cout << "Test 2: " << sol.maxScore(cp2, 2) << endl;
    // Expected: 4

    vector<int> cp3 = {9, 7, 7, 9, 7, 7, 9};
    cout << "Test 3: " << sol.maxScore(cp3, 7) << endl;
    // Expected: 55

    return 0;
}