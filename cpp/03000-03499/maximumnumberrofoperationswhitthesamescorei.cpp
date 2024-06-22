
// 3038. Maximum Number of Operations With the Same Score I
// https://leetcode.com/problems/maximum-number-of-operations-with-the-same-score-i/



class Solution {
public:
    int maxOperations(vector<int>& nums) {
        int n = nums.size();
        if( n < 2 )
            return 0;

        int ans = 1;
        int res = nums[0] + nums[1];

        for(int i = 3; i < n; i += 2) {
            if( nums[i-1] + nums[i] == res )
                ++ans;
            else
                break;
        }

        return ans;
    }
};
