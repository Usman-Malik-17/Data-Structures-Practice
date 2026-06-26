#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 32. Longest Valid Parentheses
// Link     : https://leetcode.com/problems/longest-valid-parentheses/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given a string of '(' and ')', return the length of the longest
// valid (well-formed) parentheses substring.
//
// Key Trick:
// Store indexes instead of characters in stack/deque.
// Unmatched indexes act as boundaries between valid substrings.
// Length = gap between consecutive unmatched indexes - 1
//
// Example: s = ")()())"
// Unmatched indexes: [0, 5]
// With -1 prepended: [-1, 0, 5] and 6 appended at end
// Gaps: 0-(-1)-1=0, 5-0-1=4, 6-5-1=0 → max = 4 ✅
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Approach 1: Deque (Store Unmatched Indexes)
    // Time Complexity  : O(n) - single pass
    // Space Complexity : O(n) - deque size
    //
    // Explanation:
    // Keep deque of unmatched indexes.
    // When ')' matches '(' at back of deque, pop it (valid pair).
    // Otherwise push current index (unmatched boundary).
    // After loop, gaps between consecutive unmatched indexes
    // (with -1 prepended and n appended) give valid lengths.
    // ============================================================
    void check(deque<int>& dq, string& s, int index) {
        if (!dq.empty() && s[index] == ')' && s[dq.back()] == '(') {
            dq.pop_back();
            return;
        }
        dq.push_back(index);
    }

    int longestValidParenthesesDeque(string s) {
        deque<int> dq;

        for (int i = 0; i < s.size(); i++) {
            check(dq, s, i);
        }

        // Add boundaries
        dq.push_front(-1);
        int ans = 0;

        while (!dq.empty()) {
            int p = dq.front();
            dq.pop_front();
            int n = dq.empty() ? s.size() : dq.front();
            ans = max(ans, n - p - 1);
        }
        return ans;
    }

    // ============================================================
    // Approach 2: Stack (Optimal - Clean)
    // Time Complexity  : O(n) - single pass
    // Space Complexity : O(n) - stack size
    //
    // Explanation:
    // Push -1 as base boundary initially.
    // For '(' push index.
    // For ')' pop top:
    //   - If stack empty after pop, push current index as new base
    //   - Else length = current index - new top
    //
    // Example: s = ")()())"
    // st=[-1]
    // i=0 ')': pop -1, empty → push 0,  st=[0]
    // i=1 '(': push 1,               st=[0,1]
    // i=2 ')': pop 1, ans=2-0=2,     st=[0]
    // i=3 '(': push 3,               st=[0,3]
    // i=4 ')': pop 3, ans=4-0=4,     st=[0]
    // i=5 ')': pop 0, empty → push 5, st=[5]
    // ans = 4 ✅
    // ============================================================
    int longestValidParentheses(string s) {
        stack<int> st;
        st.push(-1);
        int ans = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();
                if (st.empty()) {
                    st.push(i); // new base boundary
                } else {
                    ans = max(ans, i - st.top());
                }
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

    cout << "Test 1: " << sol.longestValidParentheses("(()") << endl;
    // Expected: 2

    cout << "Test 2: " << sol.longestValidParentheses(")()())") << endl;
    // Expected: 4

    cout << "Test 3: " << sol.longestValidParentheses("") << endl;
    // Expected: 0

    cout << "Test 4: " << sol.longestValidParentheses("()(()") << endl;
    // Expected: 2

    cout << "Test 5: " << sol.longestValidParentheses("(()()") << endl;
    // Expected: 4

    return 0;
}