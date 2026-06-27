#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 17. Letter Combinations of a Phone Number
// Link     : https://leetcode.com/problems/letter-combinations-of-a-phone-number/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given a string of digits (2-9), return all possible letter
// combinations that the number could represent (like phone keypad).
//
// Key Trick — Backtracking:
// Map each digit to its letters (like phone keypad).
// For each digit, try all its letters recursively.
// Backtrack by popping last character after each recursion.
//
// Example: digits = "23"
// '2' -> abc, '3' -> def
//
//         ""
//       / | \
//      a  b  c
//    /|\ /|\ /|\
//   d e f d e f d e f
//
// Output: ad ae af bd be bf cd ce cf
//
// Time Complexity  : O(4^n * n) - max 4 letters per digit, n digits
// Space Complexity : O(n) - recursion depth + ans string
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Backtracking: Try all letter combinations
    // ============================================================
    void sol(string& digits, int index, vector<string>& m,
             string& ans, vector<string>& out) {

        // Base case — all digits processed
        if (index >= digits.size()) {
            out.push_back(ans);
            return;
        }

        // Try each letter mapped to current digit
        string letters = m[digits[index] - '0'];
        for (int i = 0; i < letters.size(); i++) {
            ans.push_back(letters[i]);          // choose
            sol(digits, index + 1, m, ans, out); // explore
            ans.pop_back();                      // backtrack
        }
    }

    // ============================================================
    // Main Function
    // Time Complexity  : O(4^n * n)
    // Space Complexity : O(n)
    // ============================================================
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};

        vector<string> m = {
            "$", "$",     // 0, 1 — no letters
            "abc",        // 2
            "def",        // 3
            "ghi",        // 4
            "jkl",        // 5
            "mno",        // 6
            "pqrs",       // 7
            "tuv",        // 8
            "wxyz"        // 9
        };

        string ans;
        vector<string> out;
        sol(digits, 0, m, ans, out);
        return out;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<string> ans1 = sol.letterCombinations("23");
    cout << "Test 1: ";
    for (string s : ans1) cout << s << " ";
    cout << endl;
    // Expected: ad ae af bd be bf cd ce cf

    vector<string> ans2 = sol.letterCombinations("2");
    cout << "Test 2: ";
    for (string s : ans2) cout << s << " ";
    cout << endl;
    // Expected: a b c

    vector<string> ans3 = sol.letterCombinations("");
    cout << "Test 3: ";
    for (string s : ans3) cout << s << " ";
    cout << endl;
    // Expected: (empty)

    return 0;
}