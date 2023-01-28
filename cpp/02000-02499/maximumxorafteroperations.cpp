
// 2317. Maximum XOR After Operations 
// https://leetcode.com/problems/maximum-xor-after-operations/



class Solution {
public:
    int maximumXOR(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return nums[0];


        int bitcnt[31];memset(bitcnt,0,sizeof bitcnt);

        for(int x: nums)
            for(int i = 0; i < 31; ++i)
                if( (x >> i) & 1 )
                    bitcnt[i]++;

        int ans = 0;
        for(int i = 0; i < 31; ++i)
            if( bitcnt[i] != 0 )
                ans |= 1 << i;

        return ans;
    }
};
