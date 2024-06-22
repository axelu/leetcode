
// 2919. Minimum Increment Operations to Make Array Beautiful
// https://leetcode.com/problems/minimum-increment-operations-to-make-array-beautiful/





/* decimal  binary
 *    0      000
 *    1      001
 *    2      010
 *    3      011
 *    4      100
 *    5      101
 *    6      110
 *    7      111
 */
class Solution {
private:
    long long rec(vector<int>& nums, int n, int pos, int k, long long mem[][8]) {
        if( pos == n-2 )
            return 0;

        int state = 0;
        for(int i = 0; i <= 2; ++i)
            if( nums[pos+i] >= k )
                state |= (1 << i);

        if( mem[pos][state] != -1LL )
            return mem[pos][state];

        // we have a choice
        //    if( nums[pos]  >= k || nums[pos+1]  >= k || nums[pos+2] >= k ) do nothing OR
        //    increase nums[pos] or nums[pos+1] or nums[pos+2] to k for the cost of
        //        k - nums[pos], k - nums[pos+1] or k - nums[pos+2] respectively

        long long ret = 100000000000001;
        if( state > 0 ) {
            ret = rec(nums,n,pos+1,k,mem);
        } else {
            if( nums[pos] < k )
                ret = (k - nums[pos]) + rec(nums,n,pos+1,k,mem);

            for(int i = 1; i <= 2; ++i) {
                if( nums[pos+i] < k ) {
                    int cost = k - nums[pos+i];
                    int org = nums[pos+i];
                    nums[pos+i] = k;
                    ret = min(ret, cost + rec(nums,n,pos+1,k,mem));
                    // backtrack
                    nums[pos+i] = org;
                }
            }
        }

        return mem[pos][state] = ret;
    }

public:
    long long minIncrementOperations(vector<int>& nums, int k) {
        int n = nums.size();

        long long mem[n][8];memset(mem,-1LL,sizeof mem);
        return rec(nums,n,0,k,mem);
    }
};
