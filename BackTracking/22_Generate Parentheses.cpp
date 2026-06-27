#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 22. Generate Parentheses
// Link     : https://leetcode.com/problems/generate-parentheses/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given n pairs of parentheses, generate all combinations of
// well-formed parentheses.
//
// Key Trick — Backtracking:
// Track open and close counts.
// Add '(' if open < n
// Add ')' if close < open (ensures valid ordering)
// When open == n && close == n — valid combination found!
//
// Example: n=2
//               ""
//            /
//           "("         open=1, close=0
//          /    \
//       "(("    "()"    
//        |       |
//      "(()"   "()(''
//        |       |
//     "(())"  "()()"  ✅ both valid
//
// Time Complexity : O(4^n / sqrt(n)) - Catalan number
// Space Complexity: O(n) - recursion depth + ans string
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Backtracking: Build string character by character
    // ============================================================
    void solve(int open, int close, int n,
               vector<string>& out, string& ans) {

        // Base case — n opening and n closing placed
        if (open == n && close == n) {
            out.push_back(ans);
            return;
        }

        // Add '(' if we still have opening brackets left
        if (open < n) {
            ans.push_back('(');
            solve(open + 1, close, n, out, ans);
            ans.pop_back(); // backtrack
        }

        // Add ')' only if it won't exceed opening brackets
        if (close < n && open > close) {
            ans.push_back(')');
            solve(open, close + 1, n, out, ans);
            ans.pop_back(); // backtrack
        }
    }

    // ============================================================
    // Main Function
    // ============================================================
    vector<string> generateParenthesis(int n) {
        vector<string> out;
        string ans;
        solve(0, 0, n, out, ans);
        return out;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<string> ans1 = sol.generateParenthesis(3);
    cout << "Test 1 (n=3): ";
    for (string s : ans1) cout << s << " ";
    cout << endl;
    // Expected: ((()))  (()())  (())()  ()(())  ()()()

    vector<string> ans2 = sol.generateParenthesis(1);
    cout << "Test 2 (n=1): ";
    for (string s : ans2) cout << s << " ";
    cout << endl;
    // Expected: ()

    vector<string> ans3 = sol.generateParenthesis(2);
    cout << "Test 3 (n=2): ";
    for (string s : ans3) cout << s << " ";
    cout << endl;
    // Expected: (())  ()()

    return 0;
}
