
// 2835. Minimum Operations to Form Subsequence With Target Sum
// https://leetcode.com/problems/minimum-operations-to-form-subsequence-with-target-sum/






// once
unordered_map<int,int> pow2{{1,0},{2,1},{4,2},{8,3},{16,4},{32,5},{64,6},{128,7},{256,8},{512,9},{1024,10},{2048,11},{4096,12},{8192,13},{16384,14},{32768,15},{65536,16},{131072,17},{262144,18},{524288,19},{1048576,20},{2097152,21},{4194304,22},{8388608,23},{16777216,24},{33554432,25},{67108864,26},{134217728,27},{268435456,28},{536870912,29},{1073741824,30},};

class Solution {
public:
    int minOperations(vector<int>& nums, int target) {
        // if sum(nums) < target, then there is no solution
        // otherwise every number can be expressed by the sum of powers of two

        int pow2_cnt[31];memset(pow2_cnt,0,sizeof pow2_cnt);
        long int total = 0;
        for(int x: nums) {
            total += (long)x;
            ++pow2_cnt[pow2[x]];
        }

        if( total < target )
            return -1;

        // we need to have at least one pow2 of the ones we have in target
        // note that each pow2 can be created of other pow2
        //     exmple 8 could be achieved by 4 + 2 + 2
        // so it is optimal to go from right to left aka least significant bit to most significant bit
        // if we can fill the current bit, we will fill it, otherwise we will have to break the next bigger
        // one till we have enough to fill the current bit

        int ans = 0;

        long sum = 0; // running sum up to the current bit minus what we use
        for(int i = 0; i < 31; ++i) {
            long _pow2 = pow(2,i);
            sum += (long)(_pow2 * pow2_cnt[i]);
            if( target & (1<<i) ) {
                if( sum >= _pow2 ) {
                    sum -= _pow2;

                } else {
                    // we must split a 'larger' one
                    int j = i+1;
                    while( pow2_cnt[j] == 0 )
                        ++j;

                    --pow2_cnt[j];
                    int d = j - i;
                    ans += d; // split

                    sum += (long)(pow(2,j) - _pow2);
                }
            }
        }

        return ans;
    }
};
