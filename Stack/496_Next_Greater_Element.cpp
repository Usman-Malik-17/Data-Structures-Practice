#include <bits/stdc++.h>
using namespace std;

// ================================================================
// Problem  : 496. Next Greater Element I
// Link     : https://leetcode.com/problems/next-greater-element-i/
// Author   : Usman
// ================================================================

class Solution {
public:

    // ================================================================
    // Approach 1: Brute Force (Nested Loop)
    // Time Complexity  : O(n*m) - n = nums2.size(), m = nums1.size()
    // Space Complexity : O(n) - nge1 array
    // ================================================================

    int findNge(stack<int> &st, int num){
        if(st.empty()){
            st.push(num);
            return -1;
        }
        while(!st.empty() && st.top() <= num){
            st.pop();
        }
        if(st.empty()){
            st.push(num);
            return -1;
        }
        int ans = st.top();
        st.push(num);
        return ans;
    }

    vector<int> nextGreaterElementBrute(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st;
        vector<int> nge1(nums2.size(), -1);
        vector<int> ans(nums1.size(), -1);

        for (int i = nums2.size() - 1; i >= 0; i--) {
            nge1[i] = findNge(st, nums2[i]);
        }

        for (int i = 0; i < nums1.size(); i++) {
            for (int j = 0; j < nums2.size(); j++) {
                if (nums1[i] == nums2[j]) {
                    ans[i] = nge1[j];
                }
            }
        }
        return ans;
    }

    // ================================================================
    // Approach 2: Optimized (Monotonic Stack + HashMap)
    // Time Complexity  : O(n + m) - n = nums2.size(), m = nums1.size()
    // Space Complexity : O(n) - unordered_map + stack
    // ================================================================

    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st;
        unordered_map<int, int> nge;

        for (int i = nums2.size() - 1; i >= 0; i--) {
            nge[nums2[i]] = findNge(st, nums2[i]);
        }

        vector<int> ans(nums1.size());
        for (int i = 0; i < nums1.size(); i++) {
            ans[i] = nge[nums1[i]];
        }
        return ans;
    }
};

int main() {
    Solution sol;
    
    vector<int> nums1 = {4, 1, 2};
    vector<int> nums2 = {1, 3, 4, 2};
    
    vector<int> ans = sol.nextGreaterElement(nums1, nums2);
    
    for (int x : ans) {
        cout << x << " ";
    }
    cout << endl;
    
    return 0;
}