
// 2741. Special Permutations
// https://leetcode.com/problems/special-permutations/




class Solution {
private:
    long mod = 1000000007;

    long mem[16384][15]; // 2^14 + 1, 15 as 2 <= nums.length <= 14

    long rec(vector<int>& nums, int n, int last, int mask) {
        // last is the last index in nums that we used,
        // so we need to find all unused indicies in nums, whose values
        // meet the criteria nums[i] % nums[i+1] == 0 or nums[i+1] % nums[i] == 0

        if( mask == pow(2,n)-1 )
            return 1L;

        if( mem[mask][last] != -1 )
            return mem[mask][last];

        long ret = 0;

        for(int i = 0; i < n; ++i) {
            if( !((mask >> i) & 1) &&
                ( nums[last] % nums[i] == 0 || nums[i] % nums[last] == 0 ) ) {

                mask |= 1<<i;     // set the i'th bit
                ret = (ret + rec(nums,n,i,mask)) % mod;
                mask &= ~(1<<i);  // clear the i'th bit
            }
        }

        return mem[mask][last] = ret;
    }

public:
    int specialPerm(vector<int>& nums) {
        int n = nums.size();
        memset(mem,-1,sizeof mem);

        long ans = 0;
        int mask = 0;
        for(int i = 0; i < n; ++i) {
            mask |= 1<<i;     // set the i'th bit
            ans = (ans + rec(nums,n,i,mask)) % mod;
            mask &= ~(1<<i);  // clear the i'th bit
        }

        return ans;
    }
};
