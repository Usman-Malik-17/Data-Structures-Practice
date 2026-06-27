#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 784. Letter Case Permutation
// Link     : https://leetcode.com/problems/letter-case-permutation/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given a string, transform every letter to lowercase or uppercase
// to create all possible strings. Digits stay the same.
//
// Key Trick — Backtracking:
// For each character:
//   - Digit → only one choice, move forward
//   - Letter → two choices: lowercase OR uppercase
// Backtrack after each choice.
//
// Example: s = "a1b2"
//              ""
//            /    \
//           a      A
//          / \    / \
//        a1  A1  a1  A1
//        /\  /\  /\  /\
//      a1b A1b ...  ...
//      ...
// Output: a1b2 a1B2 A1b2 A1B2
//
// Time Complexity  : O(2^n * n) - n letters, 2 choices each
// Space Complexity : O(n) - recursion depth + ans string
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Backtracking: Try lowercase and uppercase for each letter
    // ============================================================
    void sol(int index, string& s, vector<string>& out, string& ans) {
        // Base case — all characters processed
        if (index == s.size()) {
            out.push_back(ans);
            return;
        }

        // Digit — only one choice
        if (isdigit(s[index])) {
            ans.push_back(s[index]);
            sol(index + 1, s, out, ans);
            ans.pop_back();
            return;
        }

        // Letter — two choices: lowercase and uppercase
        ans.push_back(tolower(s[index]));
        sol(index + 1, s, out, ans);
        ans.pop_back();

        ans.push_back(toupper(s[index]));
        sol(index + 1, s, out, ans);
        ans.pop_back();
    }

    // ============================================================
    // Main Function
    // ============================================================
    vector<string> letterCasePermutation(string s) {
        vector<string> out;
        string ans;
        sol(0, s, out, ans);
        return out;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<string> ans1 = sol.letterCasePermutation("a1b2");
    cout << "Test 1: ";
    for (string s : ans1) cout << s << " ";
    cout << endl;
    // Expected: a1b2 a1B2 A1b2 A1B2

    vector<string> ans2 = sol.letterCasePermutation("3z4");
    cout << "Test 2: ";
    for (string s : ans2) cout << s << " ";
    cout << endl;
    // Expected: 3z4 3Z4

    return 0;
}