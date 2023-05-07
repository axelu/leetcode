
// 2656. Maximum Sum With Exactly K Elements 
// https://leetcode.com/problems/maximum-sum-with-exactly-k-elements/




class Solution {
public:
    int maximizeSum(vector<int>& nums, int k) {
        int mx = 0;
        for(int x: nums)
            mx = max(mx,x);

        int score = 0;

        for(int i = 0; i < k; ++i) {
            score += mx;
            ++mx;
        }

        return score;
    }
};
