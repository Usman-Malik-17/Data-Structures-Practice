#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 93. Restore IP Addresses
// Link     : https://leetcode.com/problems/restore-ip-addresses/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Given a string of digits, return all valid IPv4 addresses
// that can be formed by inserting dots.
//
// Valid IPv4 Rules:
//   - Exactly 4 parts separated by dots
//   - Each part is an integer 0-255
//   - No leading zeros (except "0" itself)
//
// Key Trick — Backtracking:
// Try all possible splits (1, 2, or 3 digits per part).
// Validate each part — if valid, recurse for next part.
// Backtrack by popping last part and trying next split.
//
// Early Termination:
// If remaining chars < partsLeft OR > partsLeft*3 — impossible!
// Prune these branches immediately.
//
// Time Complexity : O(3^4) = O(1) — input bounded, max 81 cases
// Space Complexity: O(1) — max 4 parts, max depth 4
// ----------------------------------------------------------------

class Solution {
public:

    // ============================================================
    // Helper: Validate one IP part (start to end inclusive)
    // Returns value if valid (0-255, no leading zeros), else -1
    // ============================================================
    int valid(string& s, int start, int end) {
        // Leading zero check — "00", "01" invalid, "0" valid
        if (s[start] == '0' && start < end) return -1;

        int val = 0;
        for (int i = start; i <= end; i++) {
            val = (val * 10) + (s[i] - '0');
        }
        return val <= 255 ? val : -1;
    }

    // ============================================================
    // Helper: Convert vector<int> parts to "a.b.c.d" format
    // ============================================================
    string helper(vector<int>& parts) {
        string s;
        for (int i = 0; i < parts.size(); i++) {
            if (i != 0) s += ".";
            s += to_string(parts[i]);
        }
        return s;
    }

    // ============================================================
    // Backtracking: Try all valid splits
    // ============================================================
    void sol(int index, string& s, vector<int>& parts,
             vector<string>& out, int count) {

        // Early termination — remaining chars impossible to fill
        int remaining = s.size() - index;
        int partsLeft = 4 - count;
        if (remaining < partsLeft || remaining > partsLeft * 3) return;

        // Base case — 4 parts filled and string exhausted
        if (count == 4) {
            out.push_back(helper(parts));
            return;
        }

        // Try 1, 2, 3 digit parts
        for (int i = index; i < index + 3 && i < s.size(); i++) {
            int v = valid(s, index, i);
            if (v != -1) {
                parts.push_back(v);
                sol(i + 1, s, parts, out, count + 1);
                parts.pop_back(); // backtrack
            }
        }
    }

    // ============================================================
    // Main Function
    // ============================================================
    vector<string> restoreIpAddresses(string s) {
        vector<string> out;
        vector<int> parts;
        sol(0, s, parts, out, 0);
        return out;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    Solution sol;

    vector<string> ans1 = sol.restoreIpAddresses("25525511135");
    cout << "Test 1: ";
    for (string s : ans1) cout << s << " ";
    cout << endl;
    // Expected: 255.255.11.135 255.255.111.35

    vector<string> ans2 = sol.restoreIpAddresses("0000");
    cout << "Test 2: ";
    for (string s : ans2) cout << s << " ";
    cout << endl;
    // Expected: 0.0.0.0

    vector<string> ans3 = sol.restoreIpAddresses("101023");
    cout << "Test 3: ";
    for (string s : ans3) cout << s << " ";
    cout << endl;
    // Expected: 1.0.10.23 1.0.102.3 10.1.0.23 10.10.2.3 101.0.2.3

    return 0;
}