
// 3158. Find the XOR of Numbers Which Appear Twice
// https://leetcode.com/problems/find-the-xor-of-numbers-which-appear-twice/




class Solution {
public:
    int duplicateNumbersXOR(vector<int>& nums) {
        // 1 <= nums[i] <= 50
        int cnt[51]; memset(cnt,0,sizeof cnt);
        for(int x: nums)
            ++cnt[x];

        int ans = 0;

        for(int i = 1; i < 51; ++i)
            if( cnt[i] == 2 )
                ans ^= i;

        return ans;
    }
};
