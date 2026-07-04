#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 424. Longest Repeating Character Replacement
// Link     : https://leetcode.com/problems/longest-repeating-character-replacement/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given string s and integer k, replace at most k characters to
// make longest substring with all same characters.
//
// Key Insight:
// For any window [l, r]:
//   replacements needed = window_size - max_frequency
// If replacements <= k → window is valid!
//
// Key Trick — Sliding Window + maxf never decreases:
// maxf tracks the highest frequency seen so far.
// We only care about LARGER windows — so maxf never decreases.
// If window becomes invalid (replace > k) → shrink by one.
// Window only grows when a higher maxf is found.
//
// Why maxf stale value is OK?
// Stale maxf → window stays same size or shrinks.
// Fresh maxf (higher) → window expands.
// We only want maximum window — smaller ones irrelevant!
//
// Example: s = "AABABBA", k = 1
// r=0: m={A:1}, maxf=1, replace=0 ✅ window=1
// r=1: m={A:2}, maxf=2, replace=0 ✅ window=2
// r=2: m={A:2,B:1}, maxf=2, replace=1 ✅ window=3
// r=3: m={A:3,B:1}, maxf=3, replace=1 ✅ window=4
// r=4: m={A:3,B:2}, maxf=3, replace=2 > k=1 → shrink l=1
// r=5: m={A:2,B:3}, maxf=3, replace=2 > k=1 → shrink l=2
// r=6: m={A:2,B:3}, maxf=3, replace=2 > k=1 → shrink l=3
// maxl = 4 ✅
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Brute Force
    // Time Complexity  : O(n^2) - check all substrings
    // Space Complexity : O(26) = O(1)
    // ============================================================
    int characterReplacementBrute(string s, int k) {
        int maxl = 0;
        unordered_map<char, int> m;

        for (int i = 0; i < s.size(); i++) {
            m.clear();
            int maxf = 0;
            for (int j = i; j < s.size(); j++) {
                m[s[j]]++;
                maxf = max(maxf, m[s[j]]);
                int change = (j - i + 1) - maxf;
                if (change <= k) {
                    maxl = max(maxl, j - i + 1);
                } else {
                    break;
                }
            }
        }
        return maxl;
    }

    // ============================================================
    // Approach 2: Sliding Window — While Loop (O(n^2) worst case)
    // Time Complexity  : O(n * 26) = O(n) - recalculate maxf on shrink
    // Space Complexity : O(26) = O(1)
    // ============================================================
    int characterReplacementV2(string s, int k) {
        int maxl = 0, l = 0;
        unordered_map<char, int> m;
        int maxf = 0;

        for (int r = 0; r < s.size(); r++) {
            m[s[r]]++;
            maxf = max(m[s[r]], maxf);
            int replace = r - l + 1 - maxf;

            while (replace > k) {
                m[s[l]]--;
                l++;
                // Recalculate maxf after shrink
                maxf = 0;
                for (auto i : m) maxf = max(i.second, maxf);
                replace = r - l + 1 - maxf;
            }
            maxl = max(maxl, r - l + 1);
        }
        return maxl;
    }

    // ============================================================
    // Approach 3: Sliding Window — maxf Never Decreases (Optimal)
    // Time Complexity  : O(n) - single pass, no maxf recalculation
    // Space Complexity : O(26) = O(1)
    //
    // Key: maxf is never decreased — stale value keeps window
    // same size. Only increases when better frequency found.
    // ============================================================
    int characterReplacement(string s, int k) {
        int maxl = 0, l = 0;
        unordered_map<char, int> m;
        int maxf = 0;

        for (int r = 0; r < s.size(); r++) {
            m[s[r]]++;
            maxf = max(m[s[r]], maxf);
            int replace = r - l + 1 - maxf;

            // Invalid — shrink by one
            if (replace > k) {
                m[s[l]]--;
                l++;
            }

            maxl = max(maxl, r - l + 1);
        }
        return maxl;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    cout << "Test 1: " << sol.characterReplacement("ABAB", 2) << endl;
    // Expected: 4

    cout << "Test 2: " << sol.characterReplacement("AABABBA", 1) << endl;
    // Expected: 4

    cout << "Test 3: " << sol.characterReplacement("AAAA", 2) << endl;
    // Expected: 4

    cout << "Test 4: " << sol.characterReplacement("ABCDE", 1) << endl;
    // Expected: 2

    return 0;
}