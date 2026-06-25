#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 901. Online Stock Span
// Link     : https://leetcode.com/problems/online-stock-span/
// Author   : Usman
// ================================================================

// ----------------------------------------------------------------
// Problem Summary:
// Design a class that returns the span of stock price for today.
// Span = number of consecutive days (including today) where price
// was less than or equal to today's price.
//
// Key Trick — Monotonic Decreasing Stack + Index Tracking:
// Store indexes of prices in a monotonic decreasing stack.
// When today's price comes, pop all smaller/equal prices.
// Span = current index - top of stack (previous greater price index)
//
// Example:
// prices = [100, 80, 60, 70, 60, 75, 85]
// index     0    1   2   3   4   5   6
//
// i=0, price=100: st=[-1,0],  ans = 0-(-1) = 1
// i=1, price=80:  st=[-1,0,1], ans = 1-0   = 1  (100>80, stop)
// i=2, price=60:  st=[-1,0,1,2], ans = 2-1 = 1  (80>60, stop)
// i=3, price=70:  pop 2(60), st=[-1,0,1,3], ans = 3-1 = 2
// i=4, price=60:  st=[-1,0,1,3,4], ans = 4-3    = 1
// i=5, price=75:  pop 4(60),3(70), st=[-1,0,1,5], ans = 5-1 = 4
// i=6, price=85:  pop 5(75),1(80), st=[-1,0,6], ans = 6-0   = 6
// ----------------------------------------------------------------

class StockSpanner {
public:

    // ============================================================
    // Approach: Monotonic Decreasing Stack (Index Based)
    // Time Complexity  : O(1) amortized - each element pushed/popped once
    // Space Complexity : O(n) - stack + prices array
    // ============================================================
    stack<int> st;
    vector<int> arr;
    int index;

    StockSpanner() {
        index = -1;
    }

    int next(int price) {
        arr.push_back(price);
        index++;

        // Pop all prices less than or equal to today's price
        while (!st.empty() && arr[st.top()] <= price) {
            st.pop();
        }

        // Previous greater price index — span starts after it
        int ans = st.empty() ? -1 : st.top();
        st.push(index);

        return index - ans;
    }
};

// ============================================================
// Main - Local Testing
// ============================================================
int main() {
    StockSpanner stockSpanner;

    cout << "Test: ";
    cout << stockSpanner.next(100) << " "; // Expected: 1
    cout << stockSpanner.next(80)  << " "; // Expected: 1
    cout << stockSpanner.next(60)  << " "; // Expected: 1
    cout << stockSpanner.next(70)  << " "; // Expected: 2
    cout << stockSpanner.next(60)  << " "; // Expected: 1
    cout << stockSpanner.next(75)  << " "; // Expected: 4
    cout << stockSpanner.next(85)  << " "; // Expected: 6
    cout << endl;
    // Expected: 1 1 1 2 1 4 6

    return 0;
}