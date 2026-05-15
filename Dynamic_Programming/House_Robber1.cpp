// Problem: House Robber
// Link: https://leetcode.com/problems/house-robber/
// Time: O(n) | Space: O(n) -> Memoization, Tabulation | O(1) -> Space Optimization

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // Approach 1: Memoization
    int solMemo(vector<int>& nums, int index, vector<int>& dp){
        if(index == 0) return nums[index];
        if(index < 0) return 0;
        if(dp[index] != -1) return dp[index];
        int pick = nums[index] + solMemo(nums, index - 2, dp);
        int notPick = solMemo(nums, index - 1, dp);
        return dp[index] = max(pick, notPick);
    }

    // Approach 2: Tabulation
    int solTab(vector<int>& nums, vector<int>& dp){
        dp[0] = nums[0];
        for(int i = 1; i <= nums.size()-1; i++){
            int pick = i > 1 ? nums[i] + dp[i-2] : nums[i];
            int notPick = dp[i-1];
            dp[i] = max(pick, notPick);
        }
        return dp[nums.size()-1];
    }

    // Approach 3: Space Optimization
    int solSpace(vector<int>& nums){
        if(nums.size() == 1) return nums[0];
        int prev2 = nums[0];
        int prev = max(prev2, nums[1]);
        for(int i = 2; i < nums.size(); i++){
            int curr = max(nums[i] + prev2, prev);
            prev2 = prev;
            prev = curr;
        }
        return prev;
    }

    int rob(vector<int>& nums) {
        vector<int> dp(nums.size(), -1);
        return solSpace(nums); // jo bhi submit karni ho
    }
};