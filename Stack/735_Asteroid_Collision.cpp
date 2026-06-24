#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 735. Asteroid Collision
// Link     : https://leetcode.com/problems/asteroid-collision/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given an array of asteroids, positive means moving right,
// negative means moving left. When two asteroids collide, the
// smaller one explodes. If equal size, both explode.
// Two asteroids moving in same direction never collide.
//
// Key Trick:
// Use a stack — push right moving asteroids (+).
// When left moving asteroid (-) comes, compare with stack top.
// Keep popping until no more collisions possible.
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Helper: Handle single asteroid collision with stack
    // ============================================================
    void helper(stack<int>& st, int val) {
        if (val > 0) {
            st.push(val);
            return;
        }
        // val is negative — check collisions with right moving asteroids
        while (!st.empty() && st.top() > 0) {
            if (st.top() < abs(val)) {
                st.pop();        // right asteroid explodes, continue
            } else if (st.top() == abs(val)) {
                st.pop();        // both explode
                return;
            } else {
                return;          // left asteroid explodes
            }
        }
        st.push(val);            // no more collisions
    }

    // ============================================================
    // Helper: Convert stack to vector (bottom to top order)
    // ============================================================
    void stackToVector(stack<int>& st, vector<int>& ans) {
        while (!st.empty()) {
            ans.push_back(st.top());
            st.pop();
        }
        reverse(ans.begin(), ans.end());
    }

    // ============================================================
    // Approach: Monotonic Stack
    // Time Complexity  : O(n) - each asteroid pushed/popped once
    // Space Complexity : O(n) - stack size
    // ============================================================
    vector<int> asteroidCollision(vector<int>& ast) {
        stack<int> st;
        vector<int> ans;

        for (int i = 0; i < ast.size(); i++) {
            helper(st, ast[i]);
        }

        stackToVector(st, ans);
        return ans;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<int> ast1 = {5, 10, -5};
    vector<int> ans1 = sol.asteroidCollision(ast1);
    cout << "Test 1: ";
    for (int x : ans1) cout << x << " ";
    cout << endl;
    // Expected: 5 10

    vector<int> ast2 = {8, -8};
    vector<int> ans2 = sol.asteroidCollision(ast2);
    cout << "Test 2: ";
    for (int x : ans2) cout << x << " ";
    cout << endl;
    // Expected: (empty)

    vector<int> ast3 = {10, 2, -5};
    vector<int> ans3 = sol.asteroidCollision(ast3);
    cout << "Test 3: ";
    for (int x : ans3) cout << x << " ";
    cout << endl;
    // Expected: 10

    vector<int> ast4 = {3, 5, -6, 2, -1, 4};
    vector<int> ans4 = sol.asteroidCollision(ast4);
    cout << "Test 4: ";
    for (int x : ans4) cout << x << " ";
    cout << endl;
    // Expected: -6 2 4

    return 0;
}