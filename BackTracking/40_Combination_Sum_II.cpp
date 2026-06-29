#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 40. Combination Sum II
// Link     : https://leetcode.com/problems/combination-sum-ii/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given candidates array and target, find all unique combinations
// that sum to target. Each number used only once.
//
// Key Trick — Sort + Skip Duplicates:
// Sort array first — duplicates become adjacent.
// For each element two choices:
//   1. Pick — if cand[index] <= remaining target
//   2. Skip — but skip ALL duplicates to avoid duplicate combos
//
// Example: candidates = [1,1,2,5,6,7,10], target = 8
// index=0, val=1: Pick → recurse with t=7
//                 Skip → skip duplicate 1, try 2
// index=2, val=2: Pick → recurse with t=6
//                 Skip → try 5
// ...
//
// Why sort?
// [1,1,2] and [1,2,1] would be duplicates without sorting+skipping
//
// Time Complexity  : O(2^n * n) - each element pick/skip, n = size
// Space Complexity : O(n) - recursion depth + ans vector
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Backtracking: Pick or Skip with duplicate handling
    // ============================================================
    void solve(vector<int>& cand, int t, vector<int>& ans,
               vector<vector<int>>& out, int index) {

        // Base case — target reached
        if (t == 0) {
            out.push_back(ans);
            return;
        }

        // Base case — no more elements
        if (index == cand.size()) return;

        // Pick current element if it doesn't exceed target
        if (t >= cand[index]) {
            ans.push_back(cand[index]);
            solve(cand, t - cand[index], ans, out, index + 1);
            ans.pop_back(); // backtrack
        }

        // Skip duplicates — avoid duplicate combinations
        while (index + 1 != cand.size() && cand[index] == cand[index + 1]) {
            index++;
        }

        // Not pick — move to next element
        solve(cand, t, ans, out, index + 1);
    }

    // ============================================================
    // Main Function
    // ============================================================
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> ans;
        vector<vector<int>> out;
        sort(candidates.begin(), candidates.end()); // sort for duplicate handling
        solve(candidates, target, ans, out, 0);
        return out;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> cand1 = {10, 1, 2, 7, 6, 1, 5};
    vector<vector<int>> ans1 = sol.combinationSum2(cand1, 8);
    cout << "Test 1:" << endl;
    for (auto& v : ans1) {
        for (int x : v) cout << x << " ";
        cout << endl;
    }
    // Expected: [1,1,6] [1,2,5] [1,7] [2,6]

    vector<int> cand2 = {2, 5, 2, 1, 2};
    vector<vector<int>> ans2 = sol.combinationSum2(cand2, 5);
    cout << "Test 2:" << endl;
    for (auto& v : ans2) {
        for (int x : v) cout << x << " ";
        cout << endl;
    }
    // Expected: [1,2,2] [5]

    return 0;
}