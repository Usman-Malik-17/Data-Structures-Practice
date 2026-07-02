#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 3. Longest Substring Without Repeating Characters
// Link     : https://leetcode.com/problems/longest-substring-without-repeating-characters/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Find the length of the longest substring without duplicate chars.
//
// Key Trick — Sliding Window + HashMap:
// Maintain a window [l, i] with no duplicates.
// When duplicate found at i — shrink window from left (l++)
// until duplicate is removed.
// Track maximum window size at each step.
//
// Example: s = "abcabcbb"
// i=0: m={a:1}, window="a",    len=1
// i=1: m={a:1,b:1}, window="ab",   len=2
// i=2: m={a:1,b:1,c:1}, window="abc",  len=3
// i=3: 'a' duplicate! shrink → l=1, window="bca", len=3
// i=4: 'b' duplicate! shrink → l=2, window="cab", len=3
// i=5: 'c' duplicate! shrink → l=3, window="abc", len=3
// i=6: 'b' duplicate! shrink → l=5, window="cb",  len=2
// i=7: 'b' duplicate! shrink → l=6, window="b",   len=1
// Answer: 3 ✅
//
// Time Complexity  : O(n) - each char added/removed once
// Space Complexity : O(min(n, 26)) - map size bounded by charset
// ----------------------------------------------------------------

class Solution
{
public:
    // ============================================================
    // Approach 1: Brute Force
    // Time Complexity  : O(n^2) - check all substrings
    // Space Complexity : O(min(n, 26))
    // ============================================================
    int lengthOfLongestSubstringBrute(string s)
    {
        int n = s.size();
        int maxLen = 0;

        for (int i = 0; i < n; i++)
        {
            unordered_set<char> seen;
            for (int j = i; j < n; j++)
            {
                if (seen.count(s[j]))
                    break;
                seen.insert(s[j]);
                maxLen = max(maxLen, j - i + 1);
            }
        }
        return maxLen;
    }

    // ============================================================
    // Approach 2: Sliding Window + HashMap (Optimal)
    // Time Complexity  : O(n + n) - single pass
    // Space Complexity : O(min(n, 26))
    // ============================================================
    int LengthOfLongestSubstring(string s)
    {
        int n = s.size();
        unordered_map<char, int> m;
        int l = 0;
        int maxLen = 0;

        for (int i = 0; i < n; i++)
        {
            // Duplicate found — shrink window from left
            if (m[s[i]] != 0)
            {
                while (m[s[i]] != 0)
                {
                    m[s[l]] = 0;
                    l++;
                }
            }
            // Update max length
            int len = i - l + 1;
            maxLen = max(len, maxLen);
            m[s[i]] = 1;
        }
        return maxLen;
    }

    // ============================================================
    // Approach 3: Sliding Window + HashMap (Optimal)
    // Time Complexity  : O(n) - single pass
    // Space Complexity : O(min(n, 256))
    // ============================================================

    int lengthOfLongestSubstring(string s)
    {
        int n = s.size();
        int l = 0;
        int maxLen = 0;
        int hashLen = 256;
        int hash[hashLen];
        for (int i = 0; i < hashLen; i++)
        {
            hash[i] = -1;
        }
        for (int r = 0; r < n; r++)
        {
            if (hash[s[r]] != -1)
            {
                l = max(l, hash[s[r]] + 1);
            }
            int len = r - l + 1;
            maxLen = max(len, maxLen);
            hash[s[r]] = r;
        }
        return maxLen;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main()
{
    Solution sol;

    cout << "Test 1: " << sol.lengthOfLongestSubstring("abcabcbb") << endl;
    // Expected: 3

    cout << "Test 2: " << sol.lengthOfLongestSubstring("bbbbb") << endl;
    // Expected: 1

    cout << "Test 3: " << sol.lengthOfLongestSubstring("pwwkew") << endl;
    // Expected: 3

    cout << "Test 4: " << sol.lengthOfLongestSubstring("") << endl;
    // Expected: 0

    return 0;
}