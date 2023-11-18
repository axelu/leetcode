
// 2932. Maximum Strong Pair XOR I
// https://leetcode.com/problems/maximum-strong-pair-xor-i/





class Solution {
public:
    int maximumStrongPairXor(vector<int>& nums) {
        int n = nums.size();

        int ans = 0;

        // brute force
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            for(int j = 0; j < n; ++j) {
                int y = nums[j];
                if( abs(x - y) <= min(x,y) )
                    ans = max(ans, x ^ y);
            }
        }

        return ans;
    }
};
