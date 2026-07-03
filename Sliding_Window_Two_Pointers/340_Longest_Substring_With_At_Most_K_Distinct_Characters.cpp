/*
===============================================================================
        Longest Substring With At Most K Distinct Characters
===============================================================================

Difficulty : Medium

Problem:
Given a string s and an integer k, find the length of the longest substring
containing at most k distinct characters.

-------------------------------------------------------------------------------
My Approach:

1. I use the Sliding Window technique with two pointers.
2. Expand the window by moving the right pointer.
3. Store the frequency of each character using a hash map.
4. If the number of distinct characters becomes greater than k,
   shrink the window from the left until it becomes valid again.
5. Keep updating the maximum valid window length.

-------------------------------------------------------------------------------
Why this approach?

Instead of checking every possible substring, the sliding window maintains
a valid substring containing at most k distinct characters. Each character
is added and removed from the window at most once, resulting in an optimal
linear-time solution.

-------------------------------------------------------------------------------
Time Complexity:

O(n)

Each character enters and leaves the sliding window at most once.

-------------------------------------------------------------------------------
Space Complexity:

O(k)

The hash map stores at most k distinct characters inside the current window.

-------------------------------------------------------------------------------
Concepts Used:

✔ Sliding Window
✔ Two Pointers
✔ Hash Map

-------------------------------------------------------------------------------
Author:
Muhammad Usman Malik

===============================================================================
*/

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    int kDistinctChar(string &s, int k)
    {
        int l = 0;
        int r = 0;
        int maxLen = 0;

        unordered_map<char, int> freq;

        while (r < s.size())
        {
            freq[s[r]]++;

            while (freq.size() > k)
            {
                freq[s[l]]--;

                if (freq[s[l]] == 0)
                    freq.erase(s[l]);

                l++;
            }

            maxLen = max(maxLen, r - l + 1);
            r++;
        }

        return maxLen;
    }
};

int main()
{
    Solution obj;

    string s1 = "aababbcaacc";
    int k1 = 2;

    cout << "Input: " << s1 << ", k = " << k1 << endl;
    cout << "Output: " << obj.kDistinctChar(s1, k1) << endl;

    cout << "-----------------------------------" << endl;

    string s2 = "abcddefg";
    int k2 = 3;

    cout << "Input: " << s2 << ", k = " << k2 << endl;
    cout << "Output: " << obj.kDistinctChar(s2, k2) << endl;

    return 0;
}