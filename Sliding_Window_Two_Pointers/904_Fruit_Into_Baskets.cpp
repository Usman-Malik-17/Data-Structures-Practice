#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 904. Fruit Into Baskets
// Link     : https://leetcode.com/problems/fruit-into-baskets/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given array of fruit types, pick max fruits using only 2 baskets
// (each basket holds one type). Must pick consecutive fruits.
// Essentially: find longest subarray with at most 2 distinct values.
//
// Key Trick — Sliding Window + HashMap:
// Maintain window [l, r] with at most 2 distinct fruit types.
// Expand right — add fruit to basket (increment frequency).
// Shrink left — if more than 2 types, remove from left until valid.
// Track maximum window size.
//
// Example: fruits = [1,2,3,2,2]
// r=0: m={1:1},         window=[1]
// r=1: m={1:1,2:1},     window=[1,2]
// r=2: m={1:1,2:1,3:1} → size>2, shrink!
//      remove 1 → m={2:1,3:1}, l=1, window=[2,3]
// r=3: m={2:2,3:1},     window=[2,3,2]
// r=4: m={2:3,3:1},     window=[2,3,2,2] → maxLen=4 ✅
//
// Time Complexity  : O(n) - r moves n, l never exceeds r
// Space Complexity : O(1) - map has at most 3 entries at any time
// ----------------------------------------------------------------

class Solution
{
public:
    // ============================================================
    // Approach 1: Brute Force
    // Time Complexity  : O(n^2) - check all subarrays
    // Space Complexity : O(1)
    // ============================================================
    int totalFruitBrute(vector<int> &fruits)
    {
        int n = fruits.size();
        int maxCount = 0;

        for (int i = 0; i < n; i++)
        {
            int type1 = -1, type2 = -1;
            for (int j = i; j < n; j++)
            {
                if (fruits[j] != type1 && fruits[j] != type2)
                {
                    if (type1 == -1)
                        type1 = fruits[j];
                    else if (type2 == -1)
                        type2 = fruits[j];
                    else
                        break;
                }
                maxCount = max(maxCount, j - i + 1);
            }
        }
        return maxCount;
    }

    // ============================================================
    // Approach 2: Sliding Window + HashMap (Optimal)
    // Time Complexity  : O(n + n) - single pass
    // Space Complexity : O(1) - at most 3 entries in map
    // ============================================================
    int totalFruit1(vector<int> &fruits)
    {
        unordered_map<int, int> m;
        int l = 0, r = 0;
        int maxLen = 0;

        while (r < fruits.size())
        {
            m[fruits[r]]++;

            // More than 2 types — shrink from left
            while (m.size() > 2)
            {
                m[fruits[l]]--;
                if (m[fruits[l]] == 0)
                {
                    m.erase(fruits[l]);
                }
                l++;
            }

            maxLen = max(maxLen, r - l + 1);
            r++;
        }
        return maxLen;
    }

    // TC O(n)
    int totalFruit(vector<int> &fruits)
    {
        unordered_map<int, int> m;
        int l = 0;
        int r = 0;
        int maxLen = 0;
        while (r < fruits.size())
        {
            m[fruits[r]]++;
            if (m.size() > 2)
            {
                m[fruits[l]]--;
                if (m[fruits[l]] == 0)
                {
                    m.erase(fruits[l]);
                }
                l++;
            }
            maxLen = max(maxLen, r - l + 1);
            r++;
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

    vector<int> f1 = {1, 2, 1};
    cout << "Test 1: " << sol.totalFruit(f1) << endl;
    // Expected: 3

    vector<int> f2 = {0, 1, 2, 2};
    cout << "Test 2: " << sol.totalFruit(f2) << endl;
    // Expected: 3

    vector<int> f3 = {1, 2, 3, 2, 2};
    cout << "Test 3: " << sol.totalFruit(f3) << endl;
    // Expected: 4

    vector<int> f4 = {3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4};
    cout << "Test 4: " << sol.totalFruit(f4) << endl;
    // Expected: 5

    return 0;
}